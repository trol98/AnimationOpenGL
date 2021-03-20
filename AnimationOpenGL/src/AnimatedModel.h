#pragma once

#include "Joint.h"

class AnimatedModel
{
private:
	// unsigned int m_vao;
	// unsigned int m_texture;
	Joint m_rootJoint;
	int m_jointCount;
	Animator* m_animator;
public:
	AnimatedModel(const Joint& joint, int jointCount)
		:m_rootJoint(joint), m_jointCount(jointCount), m_animator(new Animator(this))
	{
		m_rootJoint.calcInverseBindTransform(glm::mat4(1.0f));
	}

	unsigned int getModel()
	{
		return -1;
	}
	unsigned int getTexture()
	{
		return -1;
	}

	Joint getRootJoint()
	{
		return m_rootJoint;
	}

	void doAnimation(Animation* animation)
	{
		m_animator->doAnimation(animation);
	}

	void update(float delta)
	{
		m_animator->update(delta);
	}

	std::vector<glm::mat4> getJointTransforms()
	{
		std::vector<glm::mat4> output(m_jointCount);
		addJointsToArray(m_rootJoint, output);
		return output;
	}

	void addJointsToArray(const Joint& rootJoint, std::vector<glm::mat4>& jointMatrices)
	{
		jointMatrices[rootJoint.Index] = rootJoint.getAnimatedTransform();
		for (const Joint& childJoint : rootJoint.Children)
		{
			addJointsToArray(childJoint, jointMatrices);
		}
	}
};