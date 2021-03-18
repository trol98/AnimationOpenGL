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
	JointTransform(glm::vec3 position, glm::quat rotation);
	glm::mat4 getLocalTransform() const;
	static JointTransform interpolate(const JointTransform& frameA, const JointTransform& frameB, float progression);
private:
	static glm::vec3 interpolate(const glm::vec3 start, const glm::vec3 end, float progression);
};
