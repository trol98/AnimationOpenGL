#pragma once
#include "AnimatedModel.h"
#include "Joint.h"
#include "Animator.h"


AnimatedModel::AnimatedModel(Joint* joint, int jointCount)
	:m_rootJoint(joint), m_jointCount(jointCount), m_animator(new Animator(this))
{
	m_rootJoint->calcInverseBindTransform(glm::mat4(1.0f));
}

AnimatedModel::~AnimatedModel()
{
	delete m_animator;
	delete m_rootJoint;
}

unsigned int AnimatedModel::getModel()
{
	return -1;
}
unsigned int AnimatedModel::getTexture()
{
	return -1;
}

Joint* AnimatedModel::getRootJoint()
{
	return m_rootJoint;
}

void AnimatedModel::doAnimation(Animation* animation)
{
	m_animator->doAnimation(animation);
}

void AnimatedModel::update(float delta)
{
	m_animator->update(delta);
}

std::vector<glm::mat4> AnimatedModel::getJointTransforms()
{
	std::vector<glm::mat4> output(m_jointCount);
	addJointsToArray(m_rootJoint, output);
	return output;
}

void AnimatedModel::addJointsToArray(const Joint* rootJoint, std::vector<glm::mat4>& jointMatrices)
{
	jointMatrices[rootJoint->Index] = rootJoint->getAnimatedTransform();

	for (const Joint* childJoint : rootJoint->Children)
	{
		addJointsToArray(childJoint, jointMatrices);
	}
}
// TODO: Write a destructor for animator