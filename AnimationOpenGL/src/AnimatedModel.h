#pragma once

#include "Joint.h"
#include "Animation.h"

class Animator; // forward declaration to avoid circular inclusion

class AnimatedModel
{
private:
	// unsigned int m_vao;
	// unsigned int m_texture;
	int m_jointCount;
	Joint* m_rootJoint;
	Animator* m_animator;
public:
	AnimatedModel(Joint* joint, int jointCount);

	unsigned int getModel();
	unsigned int getTexture();

	Joint* getRootJoint();

	void doAnimation(Animation* animation);

	void update(float delta);


	std::vector<glm::mat4> getJointTransforms();

	void addJointsToArray(const Joint* rootJoint, std::vector<glm::mat4>& jointMatrices);
};