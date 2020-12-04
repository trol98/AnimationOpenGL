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
	Joint(int index, const std::string& name, glm::mat4 localBindTransform)
		: Index(index), Name(name), m_localBindTransform(localBindTransform),
		m_animatedTransform(), m_inverseBindTransform()
	{}

	void addJoint(const Joint& joint)
	{
		Children.emplace_back(joint);
	}

	void setAnimatedTransform(glm::mat4 animatedTransform) noexcept
	{
		m_animatedTransform = animatedTransform;
	}

	glm::mat4 getAnimatedTransform() const noexcept
	{
		return m_animatedTransform;
	}

	glm::mat4 getinverseBindTransform() const noexcept
	{
		return m_inverseBindTransform;
	}
private:

	void calcInverseBindTransform(glm::mat4 parentBindTransform) noexcept
	{
		glm::mat4 bindTransform = parentBindTransform * m_localBindTransform;
		m_inverseBindTransform = glm::inverse(bindTransform);
		for (auto& child : Children)
		{
			child.calcInverseBindTransform(bindTransform);
		}
	}
};