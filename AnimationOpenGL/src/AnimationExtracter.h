#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "Animation.h"
#include "AnimationData.h"
#include "KeyFrame.h"
#include "KeyFrameData.h"
#include "JointTransform.h"
#include "JointTransformData.h"

#include "ColladaLoader.h"

#include "vendor/glm/glm/glm.hpp"
#include "vendor/glm/glm/gtc/matrix_transform.hpp"

class AnimationExtracter
{
	static Animation* loadAnimation(const std::string& path)
	{
		AnimationData* animationData = ColladaLoader::loadColladaAnimation(path);

		float lengthSeconds = animationData->lengthSeconds;
		std::vector<KeyFrame*> frames(animationData->keyFrames.size());
		for (int i = 0; i < frames.size(); i++)
		{
			frames[i] = createKeyFrame(animationData->keyFrames[i]);
		}
		
		delete animationData;
		return new Animation(lengthSeconds, frames);
	}
	static KeyFrame* createKeyFrame(const KeyFrameData* data)
	{
		std::unordered_map<std::string, JointTransform*> map;
		for (const JointTransformData* jointData : data->jointTransforms)
		{
			const JointTransform* jointTransform = createTransform(jointData);
			map.emplace(jointData->jointNameID, jointTransform);
		}
		return new KeyFrame(data->time, map);
	}
	static JointTransform* createTransform(const JointTransformData* data)
	{
		glm::mat4 mat = data->jointLocalTransform;
		// glm::vec3 translation(mat[3]);
		glm::vec3 translation(mat[3][0], mat[3][1], mat[3][2]);
		glm::quat rotation(mat);
		return new JointTransform(translation, rotation);
	}
};