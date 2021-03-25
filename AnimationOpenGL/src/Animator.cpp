#include "Animator.h"

Animator::Animator(AnimatedModel* entity)
	:m_entity(entity), m_currentAnimation(nullptr), m_currentAnimationTime(0.0f)
{}

void Animator::doAnimation(Animation* animation)
{
	m_currentAnimation = animation;
	m_currentAnimationTime = 0.0f;
}

void Animator::update(float delta)
{
	if (m_currentAnimation)
	{
		increaseAnimationTime(delta);
		std::unordered_map<std::string, glm::mat4> currentPose = calculateCurrentAnimationPos();
		applyPoseToJoints(currentPose, m_entity->getRootJoint(), glm::mat4(1.0f));
	}
}


void Animator::increaseAnimationTime(float delta)
{
	m_currentAnimationTime += delta;
	if (m_currentAnimationTime > m_currentAnimation->getLength())
	{
		// this was originaly %= but c++ doesn't support modulo operator for float's
		// but for this specific case this workaround should work.
		m_currentAnimationTime = m_currentAnimationTime - m_currentAnimation->getLength();
	}
}

void Animator::applyPoseToJoints(const std::unordered_map<std::string, glm::mat4>& currentPose, Joint* joint, const glm::mat4& parentTransform)
{
	glm::mat4 currentLocalTransform = currentPose.at(joint->Name);
	glm::mat4 currentTransform = parentTransform * currentLocalTransform;
	for (auto& childJoint : joint->Children)
	{
		applyPoseToJoints(currentPose, childJoint, currentTransform);
	}
	currentTransform = currentTransform * joint->getinverseBindTransform();
	joint->setAnimatedTransform(currentTransform);
}

float Animator::calculateProgression(const KeyFrame* previousFrame, const KeyFrame* nextFrame)
{
	float totalTime = nextFrame->getTimeStamp() - previousFrame->getTimeStamp();
	float currentTime = m_currentAnimationTime - previousFrame->getTimeStamp();
	return currentTime / totalTime;
}

std::vector<KeyFrame*> Animator::getPreviousAndNextFrames()
{
	std::vector<KeyFrame*> allFrames = m_currentAnimation->getKeyFrames();
	KeyFrame* previousFrame = allFrames[0];
	KeyFrame* nextFrame = allFrames[0];
	for (size_t i = 1; i < allFrames.size(); i++)
	{
		nextFrame = allFrames[i];
		if (nextFrame->getTimeStamp() > m_currentAnimationTime)
		{
			break;
		}
		previousFrame = allFrames[i];
	}

	return std::vector<KeyFrame*> { previousFrame, nextFrame };
}

std::unordered_map<std::string, glm::mat4> Animator::calculateCurrentAnimationPos()
{
	std::vector<KeyFrame*> frames = getPreviousAndNextFrames();
	float progression = calculateProgression(frames[0], frames[1]);
	return interpolatePoses(frames[0], frames[1], progression);
}

std::unordered_map<std::string, glm::mat4> Animator::interpolatePoses(KeyFrame* previousFrame, KeyFrame* nextFrame, float progression)
{
	std::unordered_map<std::string, glm::mat4> currentPose;
	for (const std::pair<std::string, JointTransform*>& pair : previousFrame->getJointKeyFrames())
	{
		JointTransform* previousTransform = pair.second;
		JointTransform* nextTransform = nextFrame->getJointKeyFrames()[pair.first];
		// TODO: Maybe a small memeory optimization in form of passing an output JointTransform
		// To the interpolate method
		JointTransform* currentTransform = JointTransform::interpolate(previousTransform, nextTransform, progression);
		currentPose.emplace(std::pair(pair.first, currentTransform->getLocalTransform()));
		delete currentTransform;
	}
	return currentPose;
}
