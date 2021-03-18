#pragma once

#include <unordered_map>
#include <string>

#include "Animation.h"
#include "AnimatedModel.h"
#include "Joint.h"

class Animator
{
private:
	AnimatedModel* m_entity;
	Animation* m_currentAnimation;
	float m_currentAnimationTime;
public:
	Animator(AnimatedModel* entity);
	void update(float delta);
private:
	void doAnimation(Animation* animation);
	void increaseAnimationTime(float delta);
	void applyPoseToJoints(const std::unordered_map<std::string, glm::mat4>& currentPose, Joint& joint, const glm::mat4& parentTransform);
	float calculateProgression(const KeyFrame& previousFrame, const KeyFrame& nextFrame);

	std::vector<KeyFrame> getPreviousAndNextFrames();
	std::unordered_map<std::string, glm::mat4> calculateCurrentAnimationPos();
	std::unordered_map<std::string, glm::mat4> interpolatePoses(const KeyFrame& previousFrame, const KeyFrame& nextFrame, float progression);
};
