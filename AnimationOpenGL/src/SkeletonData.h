#pragma once

#include "JointData.h"

class SkeletonData
{
public:
	const JointData* headJoint;
	const int jointCount;

	SkeletonData(const JointData* headJoint, int jointCount)
		:headJoint(headJoint), jointCount(jointCount)
	{
	}

	~SkeletonData()
	{
		delete headJoint;
	}
};