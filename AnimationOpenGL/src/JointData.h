#pragma once
#include <string>
#include <vector>

#include "vendor/glm/glm/glm.hpp"

class JointData
{
public:
	int index;
	std::string nameID;
	glm::mat4 bindLocalTransform;

	std::vector<JointData> children;

	JointData(int index, const std::string& nameID, const glm::mat4& bindLocalTransform);

	void addChild(const JointData& child);
};