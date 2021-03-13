#include "AnimationLoader.h"

#include "vendor/glm/glm/glm.hpp"
#include "vendor/glm/glm/ext/matrix_transform.hpp"

#include "StringUtils.h"

const glm::mat4 AnimationLoader::CORRECTION = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

AnimationLoader::AnimationLoader(const std::shared_ptr<XMLNode>& animationData, const std::shared_ptr<XMLNode>& jointHierarchy)
	:m_animationData(animationData), m_jointHierarchy(jointHierarchy)
{
}

AnimationData* AnimationLoader::extractAnimation()
{
	std::vector<float> times = getKeyTimes();
	float animationDuration = times.back();
	std::vector<KeyFrameData*> keyFrames = initKeyFrames(times);

	std::string rootNodeName = findRootJointName();
	auto animationNodes = m_animationData->getChildren("animation");
	for (const auto& jointNode : *animationNodes)
	{
		loadJointTransforms(keyFrames, jointNode, rootNodeName);
	}
	
	return new AnimationData(animationDuration, keyFrames);
}

std::vector<float> AnimationLoader::getKeyTimes()
{
	std::shared_ptr<XMLNode> timeData = m_animationData->getChild("animation")->getChild("source")->getChild("float_array");
	// TODO: Optimize split
	std::vector<std::string> rawTimesList = split(timeData->getData(), ' ');
	int listCount = rawTimesList.size();

	std::vector<float> timesList(listCount);
	for (int i = 0; i < listCount; i++)
	{
		timesList[i] = std::stof(rawTimesList[i]);
	}

	return timesList;
}

std::vector<KeyFrameData*> AnimationLoader::initKeyFrames(const std::vector<float>& times)
{
	int framesCount = times.size();
	std::vector<KeyFrameData*> frames(framesCount);

	for (int i = 0; i < framesCount; i++)
	{
		frames[i] = new KeyFrameData(times[i]);
	}
	return frames;
}

void AnimationLoader::loadJointTransforms(std::vector<KeyFrameData*>& frames, const std::shared_ptr<XMLNode>& jointData, const std::string& rootNodeID)
{
	std::string jointNameID = getJointName(jointData);
	std::string dataID = getDataID(jointData);

	std::shared_ptr<XMLNode> transforData = jointData->getChildWithAttribute("source", "id", dataID);
	std::string rawData = transforData->getChild("float_array")->getData();
	processTransforms(jointNameID, rawData, frames, jointNameID == rootNodeID);
}

std::string AnimationLoader::getDataID(const std::shared_ptr<XMLNode>& jointData)
{
	return jointData->getChild("sampler")->getChildWithAttribute("input", "semantic", "OUTPUT")
		->getAttribute("source").substr(1);
}

std::string AnimationLoader::getJointName(const std::shared_ptr<XMLNode>& jointData)
{
	// TODO: Optimize split
	return split(jointData->getChild("channel")->getAttribute("target"),'/')[0];
}

void AnimationLoader::processTransforms(const std::string& jointName, const std::string& rawData, std::vector<KeyFrameData*>& keyFrames, bool root)
{
	// TODO: Optimize split
	std::vector<std::string> rawSplitedData = split(rawData, ' ');
	glm::mat4 output;
	for (size_t i = 0; i < keyFrames.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				output[j][k] = std::stof(rawSplitedData[i * 16 + j * 4 + k]);
			}
		}

		output = glm::transpose(output);
		if (root)
		{
			output = CORRECTION * output;
		}

		keyFrames[i]->addJointTransform(new JointTransformData(jointName, output));
	}
}

std::string AnimationLoader::findRootJointName()
{
	return m_jointHierarchy->getChild("visual_scene")->getChildWithAttribute("node", "id", "Armature")
		->getChild("node")->getAttribute("id");
}
