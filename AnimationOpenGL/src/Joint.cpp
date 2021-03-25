#pragma once
#include "Joint.h"


Joint::Joint(int index, const std::string& name, const glm::mat4& localBindTransform)
	: Index(index), Name(name), m_localBindTransform(localBindTransform),
	m_animatedTransform(), m_inverseBindTransform(), Children()
{}

void Joint::addJoint(Joint* joint)
{
	Children.emplace_back(joint);
}

void Joint::setAnimatedTransform(const glm::mat4& animatedTransform)
{
	m_animatedTransform = animatedTransform;
}

glm::mat4 Joint::getAnimatedTransform() const 
{
	return m_animatedTransform;
}

glm::mat4 Joint::getinverseBindTransform() const
{
	return m_inverseBindTransform;
}

void Joint::calcInverseBindTransform(const glm::mat4& parentBindTransform)
{
	glm::mat4 bindTransform = parentBindTransform * m_localBindTransform;
	m_inverseBindTransform = glm::inverse(bindTransform);
	for (Joint* child : Children)
	{
		child->calcInverseBindTransform(bindTransform);
	}
}

Joint::~Joint()
{
	for (const Joint* child : Children)
	{
		delete child;
	}
}
