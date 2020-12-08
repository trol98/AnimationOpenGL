#include "JointTransformData.h"

JointTransformData::JointTransformData(const std::string& jointName, const glm::mat4& jointTransform)
	:jointNameID(jointName), jointLocalTransform(jointTransform)
{
}
