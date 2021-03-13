#pragma once

#include "AnimatedModelData.h"
#include "AnimationData.h"

class ColladaLoader
{
public:
	static AnimatedModelData* loadColladaModel(const std::string path, int maxWeights);
	static AnimationData* loadColladaAnimation(const std::string& path);
};