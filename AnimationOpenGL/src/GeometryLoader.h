#pragma once

#include <memory>
#include <vector>

#include "XMLNode.h"
#include "SkinningData.h"
#include "Vertex.h"
#include "MeshData.h"

#include "vendor/glm/glm/glm.hpp"
#include "vendor/glm/glm/gtc/matrix_transform.hpp"

class GeometryLoader
{
private:
	const std::shared_ptr<XMLNode> m_meshData;
	const std::vector<VertexSkinData> m_vertexWeights;

	//TODO: consider changing this to unique_ptr<>
	std::vector<float> m_verticesArray;
	std::vector<float> m_normalsArray;
	std::vector<float> m_texturesArray;
	std::vector<int>   m_indicesArray;
	std::vector<int>   m_jointIDsArray;
	std::vector<float> m_weightsArray;

	std::vector<Vertex>	   m_vertices;
	std::vector<glm::vec2> m_textures;
	std::vector<glm::vec3> m_normals;
	std::vector<int>	   m_indices;

	static const glm::mat4 CORRECTION;
public:
	GeometryLoader(const std::shared_ptr<XMLNode>& geometryNode, const std::vector<VertexSkinData>& vertexWeights);
	MeshData extractModelData();
private:
	void initArrays();
	void readPositions();
	void readNormals();
	void readTextureCoords();
	void assembleVertices();
	void removeUnusedVertices();

	Vertex processVertex(int positionIndex, int normalsIndex, int texureIndex);
	Vertex dealWithAlreadyProcessedVertex(const Vertex& previousVertex, int newTextureIndex, int newNormalIndex);

	int* convertIndicesListToArray();
	float convertDataToArrays();
};
