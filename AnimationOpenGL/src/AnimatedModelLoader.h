#pragma once

#include <string>

#include "AnimatedModel.h"
#include "AnimatedModelData.h"
#include "ColladaLoader.h"

class AnimatedModelLoader
{
public:
	static AnimatedModel* loadEntity(const std::string& path)
	{
		AnimatedModelData* entityData = ColladaLoader::loadColladaModel(path, 3);
		// VAO model = createVAO(entityData->getMeshData());
		// Texture texture = loadTexture(texturePath);
		const SkeletonData* skeletonData = entityData->getJointsData();
		int jointCount = skeletonData->jointCount;
		Joint* headJoint = createJoints(skeletonData->headJoint);
		delete entityData;

		return new AnimatedModel(headJoint, jointCount);
	}
private:
	static Joint* createJoints(const JointData* data)
	{
		Joint* joint = new Joint(data->index, data->nameID, data->bindLocalTransform);
		for (const JointData* child : data->children)
		{
			joint->addJoint(createJoints(child));
		}
		return joint;
	}
};