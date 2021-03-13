#pragma once

#include <memory>

#include "XMLNode.h"
#include "AnimationData.h"

class AnimationLoader
{
private:
	const static glm::mat4 CORRECTION;

	std::shared_ptr<XMLNode> m_animationData;
	std::shared_ptr<XMLNode> m_jointHierarchy;

public:
	AnimationLoader(const std::shared_ptr<XMLNode>& animationData, const std::shared_ptr<XMLNode>& jointHierarchy);
	AnimationData* extractAnimation();
	// TODO: Add const to these functions
private:
	std::vector<float> getKeyTimes(); 
	std::vector<KeyFrameData*> initKeyFrames(const std::vector<float>& times);
	void loadJointTransforms(std::vector<KeyFrameData*>& frames, const std::shared_ptr<XMLNode>& jointData, const std::string& rootNodeID);
	std::string getDataID(const std::shared_ptr<XMLNode>& jointData);
	std::string getJointName(const std::shared_ptr<XMLNode>& jointData);
	void processTransforms(const std::string& jointName, const std::string& rawData, std::vector<KeyFrameData*>& keyFrames, bool root);
	std::string findRootJointName();

};