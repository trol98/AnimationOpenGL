#pragma once

#include "AnimatedModelData.h"
#include "AnimationData.h"

class ColladaLoader
{
public:
	static AnimatedModelData* loadColladaModel(const std::string path, int maxWeights);
	static /*AnimationData*/void loadColladaAnimation(const std::string& path);
};