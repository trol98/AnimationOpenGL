#pragma once

#include <vector>

class MeshData
{
private:
	std::vector<float> m_vertices;
	std::vector<float> m_textureCoords;
	std::vector<float> m_normals;
	std::vector<int>   m_indices;
	std::vector<int>   m_jointIDs;
	std::vector<float> m_vertexWeights;
public:
	MeshData(const std::vector<float>& v, const std::vector<float>& t, const std::vector<float>& n,
		const std::vector<int>& i, const std::vector<int>& IDs, const std::vector<float>& w);

	std::vector <float> getVertices();
	std::vector <int> getIndices ();
	std::vector <float> getNormals ();
	std::vector <float> getTextureCoords ();
	
	std::vector <float> getVertexWeights ();
	std::vector <int> getJointIds();

	int getVertexCount();
};