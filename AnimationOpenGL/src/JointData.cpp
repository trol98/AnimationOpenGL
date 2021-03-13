#include "JointData.h"

JointData::JointData(int index, const std::string& nameID, const glm::mat4& bindLocalTransform)
	:index(index), nameID(nameID), bindLocalTransform(bindLocalTransform), children()
{
}

void JointData::addChild(JointData* child)
{
	children.emplace_back(child);
}

JointData::~JointData()
{
	for (int i = 0; i < children.size(); i++)
	{
		delete children[i];
	}
}
