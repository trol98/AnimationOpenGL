#pragma once
#include "vendor/glm/glm/glm.hpp"

#include "vendor/glm/glm/gtc/quaternion.hpp"
#include "vendor/glm/glm/gtx/quaternion.hpp"

#include "vendor/glm/glm/gtc/matrix_transform.hpp"

class JointTransform
{
private:
	glm::vec3 m_position;
	glm::quat m_rotation;
public:
	JointTransform(glm::vec3 position, glm::quat rotation)
		:m_position(position), m_rotation(rotation)
	{}
	glm::mat4 getLocalTransform()
	{
		glm::mat4 matrix(1.0f);
		glm::translate(matrix, m_position);
		return matrix * glm::toMat4(m_rotation);
	}
};
