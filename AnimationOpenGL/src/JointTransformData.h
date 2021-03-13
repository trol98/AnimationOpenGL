#pragma once

#include <string>
#include "vendor/glm/glm/glm.hpp"

class JointTransformData
{
public: // just DEBUG
	std::string jointNameID;
	glm::mat4 jointLocalTransform;
public:
	JointTransformData::JointTransformData(const std::string& jointName, const glm::mat4& jointTransform)
		:jointNameID(jointName), jointLocalTransform(jointTransform)
	{}
};