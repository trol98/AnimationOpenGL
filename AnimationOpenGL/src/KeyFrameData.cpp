#include "KeyFrameData.h"

KeyFrameData::KeyFrameData(float time)
	:jointTransforms(), time(time)
{
}

void KeyFrameData::addJointTransform(const JointTransformData& transform)
{
	jointTransforms.emplace_back(transform);
}
