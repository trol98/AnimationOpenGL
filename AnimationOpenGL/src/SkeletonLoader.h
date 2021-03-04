#pragma once
#include <memory>
#include <vector>
#include "XMLNode.h"
#include "vendor/glm/glm/glm.hpp"
#include "SkeletonData.h"

class SkeletonLoader
{
	std::shared_ptr<XMLNode> m_armatureData;
	std::vector<std::string> m_boneOrder;
	int m_jointCount;

	static const glm::mat4 CORRECTION;
public:
	SkeletonLoader(const std::shared_ptr<XMLNode>& visualSceneNode, std::vector<std::string> boneOrder);
	SkeletonData* extractBoneData();
private:
	JointData* loadJointData(const std::shared_ptr<XMLNode>& jointNode, bool isRoot);
	JointData* extractMainJointData(const std::shared_ptr<XMLNode>& jointNode, bool isRoot);
	glm::mat4 convertData(const std::vector<std::string>& rawData);
};
