#pragma once
#include "Joint.h"


Joint::Joint(int index, const std::string& name, glm::mat4 localBindTransform)
	: Index(index), Name(name), m_localBindTransform(localBindTransform),
	m_animatedTransform(), m_inverseBindTransform()
{}

void Joint::addJoint(const Joint& joint)
{
	Children.emplace_back(joint);
}

void Joint::setAnimatedTransform(glm::mat4 animatedTransform) noexcept
{
	m_animatedTransform = animatedTransform;
}

glm::mat4 Joint::getAnimatedTransform() const noexcept
{
	return m_animatedTransform;
}

glm::mat4 Joint::getinverseBindTransform() const noexcept
{
	return m_inverseBindTransform;
}


void Joint::calcInverseBindTransform(glm::mat4 parentBindTransform) noexcept
{
	glm::mat4 bindTransform = parentBindTransform * m_localBindTransform;
	m_inverseBindTransform = glm::inverse(bindTransform);
	for (auto& child : Children)
	{
		child.calcInverseBindTransform(bindTransform);
	}
}
