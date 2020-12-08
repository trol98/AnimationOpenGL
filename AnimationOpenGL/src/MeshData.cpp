#include "MeshData.h"

MeshData::MeshData(const std::vector<float>& v, const std::vector<float>& t, const std::vector<float>& n,
	const std::vector<int>& i, const std::vector<int>& IDs, const std::vector<float>& w)
	:m_vertices(v), m_textureCoords(t), m_normals(n), m_indices(i), m_jointIDs(IDs), m_vertexWeights(w)
{
}
std::vector <float> MeshData::getVertices()
{
	return m_vertices;
}
std::vector <int> MeshData::getIndices()
{
	return m_indices;
}
std::vector <float> MeshData::getNormals()
{
	return m_normals;
}
std::vector <float> MeshData::getTextureCoords()
{
	return m_textureCoords;
}
std::vector <float> MeshData::getVertexWeights()
{
	return m_vertexWeights;
}
std::vector <int> MeshData::getJointIds()
{
	return m_jointIDs;
}
int MeshData::getVertexCount()
{
	return m_vertices.size() / 3;
}