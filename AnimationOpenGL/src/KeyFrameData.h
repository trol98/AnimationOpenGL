#pragma once

#include <vector>

#include "JointTransformData.h"

class KeyFrameData
{
	float time;
	std::vector<JointTransformData> jointTransforms;

	KeyFrameData(float time);

	void addJointTransform(const JointTransformData& transform);
};