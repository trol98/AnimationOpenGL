#include "SkeletonLoader.h"
#include "StringUtils.h"
#include "vendor/glm/glm/ext/matrix_transform.hpp"

const glm::mat4 SkeletonLoader::CORRECTION = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

SkeletonLoader::SkeletonLoader(const std::shared_ptr<XMLNode>& visualSceneNode, std::vector<std::string> boneOrder)
	:m_armatureData(visualSceneNode->getChildWithAttribute("node", "id", "Armature")), m_boneOrder(boneOrder), m_jointCount(0)
{
}

SkeletonData* SkeletonLoader::extractBoneData()
{
	std::shared_ptr<XMLNode> headNode = m_armatureData->getChild("node");
	JointData headJoint = loadJointData(headNode, true);
	return new SkeletonData(headJoint, m_jointCount);
}

JointData SkeletonLoader::loadJointData(const std::shared_ptr<XMLNode>& jointNode, bool isRoot)
{
	JointData joint = extractMainJointData(jointNode, isRoot);
	for (std::shared_ptr<XMLNode> childNode : *jointNode->getChildren("node")) {
		joint.addChild(loadJointData(childNode, false));
	}
	return joint;
}

JointData SkeletonLoader::extractMainJointData(const std::shared_ptr<XMLNode>& jointNode, bool isRoot)
{
	/*
			String nameId = jointNode.getAttribute("id");
		int index = boneOrder.indexOf(nameId);
		String[] matrixData = jointNode.getChild("matrix").getData().split(" ");
		Matrix4f matrix = new Matrix4f();
		matrix.load(convertData(matrixData));
		matrix.transpose();
		if(isRoot){
			//because in Blender z is up, but in our game y is up.
			Matrix4f.mul(CORRECTION, matrix, matrix);
		}
		jointCount++;
		return new JointData(index, nameId, matrix);
	*/

	std::string nameID = jointNode->getAttribute("id");
	int index = std::find(m_boneOrder.begin(), m_boneOrder.end(), nameID) - m_boneOrder.begin();

	std::vector<std::string> matrixData = split(jointNode->getChild("matrix")->getData(), ' ');

	glm::mat4 matrix = convertData(matrixData);

	if (isRoot)
	{
		matrix = CORRECTION * matrix;
	}
	m_jointCount++;

	// a lot of copying right there
	// TODO: think about fixing that
	return JointData(index, nameID, matrix);
}
glm::mat4 SkeletonLoader::convertData(const std::vector<std::string>& rawData)
{
	glm::mat4 output;
	// TODO: Check if this method is working correctly;

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
		for (int j = 0; j < 4; i++)
		{
			output[i][j] = std::stoi(rawData[i * 4 + j]);
		}
	}
	return output;
}
