#include "MeshData.h"
#include <memory>

MeshData::MeshData(const std::vector<float>& v, const std::vector<float>& t, const std::vector<float>& n,
	const std::vector<int>& i, const std::vector<int>& IDs, const std::vector<float>& w)
	:m_count(v.size()), 
	 m_vertices(new float[v.size()]),
	 m_textureCoords(new float[t.size()]),
	 m_normals(new float[n.size()]),
	 m_indices(new int[i.size()]),
	 m_jointIDs(new int[IDs.size()]),
	 m_vertexWeights(new float[w.size()])						
{
}
std::shared_ptr<float[]> MeshData::getVertices()
{
	return m_vertices;
}
std::shared_ptr <int[]> MeshData::getIndices()
{
	return m_indices;
}
std::shared_ptr <float[]> MeshData::getNormals()
{
	return m_normals;
}
std::shared_ptr <float[]> MeshData::getTextureCoords()
{
	return m_textureCoords;
}
std::shared_ptr <float[]> MeshData::getVertexWeights()
{
	return m_vertexWeights;
}
std::shared_ptr <int[]> MeshData::getJointIds()
{
	return m_jointIDs;
}
int MeshData::getVertexCount()
{
	return m_count / 3;
}