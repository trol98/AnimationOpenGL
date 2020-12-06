#include "JointTransform.h"

JointTransform::JointTransform(glm::vec3 position, glm::quat rotation)
	:m_position(position), m_rotation(rotation)
{}
glm::mat4 JointTransform::getLocalTransform()
{
	glm::mat4 matrix(1.0f);
	glm::translate(matrix, m_position);
	return matrix * glm::toMat4(m_rotation);
}
