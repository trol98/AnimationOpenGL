#include "SkeletonLoader.h"
#include "StringUtils.h"
#include "vendor/glm/glm/ext/matrix_transform.hpp"

#include <iostream>

const glm::mat4 SkeletonLoader::CORRECTION = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

SkeletonLoader::SkeletonLoader(const std::shared_ptr<XMLNode>& visualSceneNode, std::vector<std::string> boneOrder)
	:m_armatureData(visualSceneNode->getChild("visual_scene")->getChildWithAttribute("node", "id", "Armature")), m_boneOrder(boneOrder), m_jointCount(0)
{
}

SkeletonData* SkeletonLoader::extractBoneData()
{
	std::shared_ptr<XMLNode> headNode = m_armatureData->getChild("node");
	JointData* headJoint = loadJointData(headNode, true);
	return new SkeletonData(headJoint, m_jointCount);
}

JointData* SkeletonLoader::loadJointData(const std::shared_ptr<XMLNode>& jointNode, bool isRoot)
{
	JointData* joint = extractMainJointData(jointNode, isRoot);
	for (std::shared_ptr<XMLNode> childNode : *jointNode->getChildren("node")) {
		joint->addChild(loadJointData(childNode, false));
	}
	return joint;
}

JointData* SkeletonLoader::extractMainJointData(const std::shared_ptr<XMLNode>& jointNode, bool isRoot)
{
	std::string nameID = jointNode->getAttribute("id");

	int index = std::find(m_boneOrder.begin(), m_boneOrder.end(), nameID) - m_boneOrder.begin();
	assert(index >= 0);

	std::vector<std::string> matrixData = StringUtils::split(jointNode->getChild("matrix")->getData(), ' ');
	glm::mat4 matrix = convertData(matrixData);

	// COLLADA files are row-major and GLSL preffers coloumn-major order
	matrix = glm::transpose(matrix);

	if (isRoot)
	{
		matrix = CORRECTION * matrix;
	}
	m_jointCount++;

	// a lot of copying right there
	// TODO: think about fixing that
	return new JointData(index, nameID, matrix);
}
glm::mat4 SkeletonLoader::convertData(const std::vector<std::string>& rawData)
{
	glm::mat4 output;

	// rawData is a matrix written in row-major order so 
	// <matrix> 
	// 1  2  3  4
	// 5  6  7  8
	// 9  10 11 12
	// 13 14 15 16
	// </matrix>
	// is represented as 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
	// if i'm wrong than this will be a killer error
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			output[i][j] = std::stoi(rawData[i * 4 + j]);
		}
	}
	return output;
}
