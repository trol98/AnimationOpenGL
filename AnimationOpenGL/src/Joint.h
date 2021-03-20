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
	Joint(int index, const std::string& name, const glm::mat4& localBindTransform);

	void addJoint(const Joint& joint);
	void setAnimatedTransform(const glm::mat4& animatedTransform);

	glm::mat4 getAnimatedTransform() const;
	glm::mat4 getinverseBindTransform() const;
	void calcInverseBindTransform(const glm::mat4& parentBindTransform);
};