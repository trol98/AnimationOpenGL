#pragma once

#include <memory>
#include <vector>

#include "XMLNode.h"
#include "SkinningData.h"
#include "Vertex.h"
#include "MeshData.h"
#include "StringUtils.h"

#include "vendor/glm/glm/glm.hpp"
#include "vendor/glm/glm/gtc/matrix_transform.hpp"

class GeometryLoader
{
private:
	const std::shared_ptr<XMLNode> m_meshData;
	const std::vector<VertexSkinData> m_vertexWeights;

	//TODO: improve storing of data
	std::vector<float> m_verticesArray;
	std::vector<float> m_normalsArray;
	std::vector<float> m_texturesArray;
	std::vector<int>   m_indicesArray;
	std::vector<int>   m_jointIDsArray;
	std::vector<float> m_weightsArray;

	std::vector<std::shared_ptr<Vertex>> m_vertices;
	std::vector<glm::vec2>				 m_textures;
	std::vector<glm::vec3>				 m_normals;
	std::vector<int>					 m_indices;

	static const glm::mat4 CORRECTION;
public:
	GeometryLoader(const std::shared_ptr<XMLNode>& geometryNode, const std::vector<VertexSkinData>& vertexWeights);
	MeshData extractModelData();
private:
	void readPositions();
	void readNormals();
	void readTextureCoords();

	void assembleVertices();
	void removeUnusedVertices();

	void initArrays();
	void convertDataToArrays();
	void convertIndicesListToArray();

	std::shared_ptr<Vertex> processVertex(int positionIndex, int normalsIndex, int texureIndex);
	std::shared_ptr<Vertex> dealWithAlreadyProcessedVertex(std::shared_ptr<Vertex>& previousVertex, int newTextureIndex, int newNormalIndex);
};
