#pragma once

#include <string>

#include "vendor/glm/glm/glm.hpp"

class JointTransformData
{
private:
	std::string jointNameID;
	glm::mat4 jointLocalTransform;

public:
	JointTransformData(const std::string& jointName, const glm::mat4& jointTransform);
};