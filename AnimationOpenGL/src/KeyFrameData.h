#pragma once

#include <vector>

#include "JointTransformData.h"

class KeyFrameData
{
public:
	float time;
	std::vector<JointTransformData*> jointTransforms;

	KeyFrameData()
		:time(-1.0f), jointTransforms()
	{}
	KeyFrameData::KeyFrameData(float time)
		:jointTransforms(), time(time)
	{}

	void KeyFrameData::addJointTransform(JointTransformData* transform)
	{
		jointTransforms.emplace_back(transform);
	}

	~KeyFrameData()
	{
		for (size_t i = 0; i < jointTransforms.size(); i++)
			delete jointTransforms[i];
	}
};