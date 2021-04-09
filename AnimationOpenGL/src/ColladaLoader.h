#pragma once

#include "AnimatedModelData.h"
#include "AnimationData.h"
#include "XMLNode.h"

class ColladaLoader
{
public:
	static AnimatedModelData* loadColladaModel(const std::shared_ptr<XMLNode>& root, int maxWeights);
	static AnimationData* loadColladaAnimation(const std::shared_ptr<XMLNode>& root);
};