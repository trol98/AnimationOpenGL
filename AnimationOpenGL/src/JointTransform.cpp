#include "JointTransform.h"

JointTransform::JointTransform(glm::vec3 position, glm::quat rotation)
	:m_position(position), m_rotation(rotation)
{}
glm::mat4 JointTransform::getLocalTransform() const
{
	glm::mat4 matrix(1.0f);
	return glm::translate(matrix, m_position) * glm::toMat4(m_rotation);
}

JointTransform* JointTransform::interpolate(const JointTransform* frameA, const JointTransform* frameB, float progression)
{
	glm::vec3 position = interpolate(frameA->m_position, frameB->m_position, progression);
	glm::quat rotation = glm::lerp(frameA->m_rotation, frameB->m_rotation, progression); 
	return new JointTransform(position, rotation);
}

glm::vec3 JointTransform::interpolate(const glm::vec3 start, const glm::vec3 end, float progression)
{
	float x = start.x + (end.x - start.x) * progression;
	float y = start.y + (end.y - start.y) * progression;
	float z = start.z + (end.z - start.z) * progression;
	return glm::vec3(x, y, z);
}
