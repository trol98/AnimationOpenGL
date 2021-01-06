#pragma once

#include <memory>
#include <vector>

#include "XMLNode.h"
#include "SkinningData.h"
#include "Vertex.h"

#include "vendor/glm/glm/glm.hpp"
#include "vendor/glm/glm/gtc/matrix_transform.hpp"

class GeometryLoader
{
private:
	const std::shared_ptr<XMLNode> meshData;
	const std::vector<VertexSkinData> vertexWeights;

	float* verticesArray;
	float* normalsArray;
	float* texturesArray;
	int* indicesArray;
	int* jointIDsArray;
	float* weightsArray;

	std::vector<Vertex> vertices;

	static const glm::mat4 CORRECTION;

};
