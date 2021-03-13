#pragma once

#include <vector>

#include "KeyFrameData.h"

class AnimationData
{
public:
	const float lengthSeconds;
	const std::vector<KeyFrameData*> keyFrames;

	AnimationData(float lengthSeconds, const std::vector<KeyFrameData*>& keyFrames)
		:lengthSeconds(lengthSeconds), keyFrames(keyFrames)
	{
	}

	~AnimationData()
	{
		for (int i = 0; i < keyFrames.size(); i++)
		{
			delete keyFrames[i];
		}
	}
};