#pragma once

#include <string>
#include <vector>

#include "vendor/glm/glm/glm.hpp"
#include "vendor/glm/glm/gtc/matrix_transform.hpp"


class Joint
{
public:
	int Index;
	std::string Name;
	std::vector<Joint> Children;
private:
	glm::mat4 m_animatedTransform;
	glm::mat4 m_localBindTransform;
	glm::mat4 m_inverseBindTransform;
public:
	Joint(int index, const std::string& name, glm::mat4 localBindTransform);

	void addJoint(const Joint& joint);
	void setAnimatedTransform(glm::mat4 animatedTransform) noexcept;

	glm::mat4 getAnimatedTransform() const noexcept;
	glm::mat4 getinverseBindTransform() const noexcept;
private:
	void calcInverseBindTransform(glm::mat4 parentBindTransform) noexcept;
};