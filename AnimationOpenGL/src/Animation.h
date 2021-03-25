#pragma once

#include <vector>
#include "KeyFrame.h"

class Animation
{
private:
	const float m_length;
	const std::vector<KeyFrame*> m_keyFrames;
public:
	Animation(float lengthInSeconds, const std::vector<KeyFrame*>& frames)
		:m_length(lengthInSeconds), m_keyFrames(frames)
	{}

	float getLength() const 
	{
		return m_length;
	}

	std::vector<KeyFrame*> getKeyFrames() const 
	{
		return m_keyFrames;
	}

	~Animation()
	{
		for (size_t i = 0; i < m_keyFrames.size(); i++)
		{
			delete m_keyFrames[i];
		}
	}
};
