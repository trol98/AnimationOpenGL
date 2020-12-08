#pragma once

#include "JointData.h"

class SkeletonData
{
	JointData headJoint;
	int jointCount;

	SkeletonData(const JointData& headJoint, int jointCount);
};