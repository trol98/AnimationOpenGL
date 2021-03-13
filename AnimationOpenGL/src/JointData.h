#pragma once
#include <string>
#include <vector>

#include "vendor/glm/glm/glm.hpp"

class JointData
{
public:
	const int index;
	const std::string nameID;
	const glm::mat4 bindLocalTransform;

	std::vector<JointData*> children;

	JointData(int index, const std::string& nameID, const glm::mat4& bindLocalTransform);

	void addChild(JointData* child);

	~JointData();
};