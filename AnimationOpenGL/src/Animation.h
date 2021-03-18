#pragma once

#include <vector>
#include "KeyFrame.h"

class Animation
{
private:
	float m_length;
	std::vector<KeyFrame> m_keyFrames;
public:
	Animation(float lengthInSeconds, const std::vector<KeyFrame>& frames)
		:m_length(lengthInSeconds), m_keyFrames(frames)
	{}

	float getLength()
	{
		return m_length;
	}

	std::vector<KeyFrame> getKeyFrames()
	{
		return m_keyFrames;
	}
};
