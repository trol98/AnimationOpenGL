
#include "ColladaLoader.h"

#include "AnimationLoader.h"
#include "GeometryLoader.h"
#include "SkinLoader.h"
#include "SkinningData.h"
#include "SkeletonLoader.h"


#include "XMLNode.h"
#include "XMLParser.h"


#include <memory>
#include <iostream>

AnimatedModelData* ColladaLoader::loadColladaModel(const std::shared_ptr<XMLNode>& root, int maxWeights)
{
	SkinLoader* skinLoader = new SkinLoader(root->getChild("library_controllers"), maxWeights);
	SkinningData* skinningData = skinLoader->extractSkinData();
	delete skinLoader;

	SkeletonLoader* jointsLoader = new SkeletonLoader(root->getChild("library_visual_scenes"), skinningData->jointOrder);
	SkeletonData* jointsData = jointsLoader->extractBoneData();
	delete jointsLoader;

	GeometryLoader* geometryLoader = new GeometryLoader(root->getChild("library_geometries"), skinningData->verticesSkinData);
	MeshData* meshData = geometryLoader->extractModelData();
	delete geometryLoader;
	
	delete skinningData;
	return new AnimatedModelData(meshData, jointsData);
}

AnimationData* ColladaLoader::loadColladaAnimation(const std::shared_ptr<XMLNode>& node)
{
	std::shared_ptr<XMLNode> animationsNode = node->getChild("library_animations");
	std::shared_ptr<XMLNode> jointsNode = node->getChild("library_visual_scenes");
	AnimationLoader* loader = new AnimationLoader(animationsNode, jointsNode);
	AnimationData* animData = loader->extractAnimation();
	delete loader;
	return animData;
}
