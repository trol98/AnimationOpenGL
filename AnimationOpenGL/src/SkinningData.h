#pragma once

#include <string>
#include <vector>

#include "VertexSkinData.h"

class SkinningData
{
public:
	const std::vector<std::string> jointOrder;
	const std::vector<VertexSkinData> verticesSkinData;

	SkinningData(const std::vector<std::string>& jointOrder, const std::vector<VertexSkinData>& verticesSkinData)
		:jointOrder(jointOrder), verticesSkinData(verticesSkinData)
	{
	}
};