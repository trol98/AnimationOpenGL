#include "ColladaLoader.h"

#include "AnimationLoader.h"
#include "GeometryLoader.h"
#include "SkinLoader.h"
#include "SkinningData.h"
#include "SkeletonLoader.h"


#include "XMLNode.h"
#include "XMLParser.h"


#include <memory>

AnimatedModelData ColladaLoader::loadColladaModel(const std::string path, int maxWeights)
{
	std::shared_ptr<XMLNode> root = XMLParser::loadXMLFile(path);

	SkinLoader* skinLoader = new SkinLoader(root->getChild("library_controllers"), maxWeights);
	SkinningData* skinningData = skinLoader.extractSkinData();

	SkeletonLoader* jointsLoader = new SkeletonLoader(root->getChild("library_visual_scenes"), skinningData.jointOrder);
	SkeletonData* jointsData = jointsLoader.extractBoneData();

	GeometryLoader* g = new GeometryLoader(root->getChild("library_geometries"), skinningData.verticesSkinData);
	MeshData meshData = g->extractModelData();

	delete g;

	return new AnimatedModelData(meshData, jointsData);
}

AnimationData ColladaLoader::loadColladaAnimation(const std::string path)
{
	std::shared_ptr<XMLNode> node = XMLParser::loadXMLFile(path);
	std::shared_ptr<XMLNode> animationsNode = node->getChild("library_animations");
	std::shared_ptr<XMLNode> jointsNode = node->getChild("library_visual_scenes");
	AnimationLoader loader = new AnimationLoader(animationsNode, jointsNode);
	AnimationData animData = loader.extractAnimation();
	return animData;
}
