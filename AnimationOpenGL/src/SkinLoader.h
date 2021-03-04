#pragma once

#include <vector>

#include "XMLNode.h"
#include "SkinningData.h"
#include "StringUtils.h"

class SkinLoader
{
	const std::shared_ptr<XMLNode> m_skinningData;
	const int m_maxWeights;

public:
	SkinLoader(const std::shared_ptr<XMLNode>& controllerNode, int maxWeights);
	SkinningData* extractSkinData();
private:
	float* loadWeights();

	std::vector<std::string> loadJointsList();
	std::vector<int> getEffectiveJointsCount(const std::shared_ptr<XMLNode>& weightsDataNode);
	std::vector<VertexSkinData> getSkinData(const std::shared_ptr<XMLNode>& weightsDataNode, const std::vector<int>& counts, float* weights);
};
