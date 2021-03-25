#include "MeshData.h"
#include <memory>

MeshData::MeshData(const std::vector<float>& v, const std::vector<float>& t, const std::vector<float>& n,
	const std::vector<int>& in, const std::vector<int>& IDs, const std::vector<float>& w)
	:m_vertexCount(v.size()),
	 m_indicesCount(in.size()),
	 m_jointIDsCount(IDs.size()),
	 m_vertexWeightsCount(w.size()),
	 m_vertices(new float[v.size()]),
	 m_textureCoords(new float[t.size()]),
	 m_normals(new float[n.size()]),
	 m_indices(new unsigned int[in.size()]),
	 m_jointIDs(new int[IDs.size()]),
	 m_vertexWeights(new float[w.size()])						
{
	for (int i = 0; i < v.size(); i++)
	{
		m_vertices[i] = v[i]; 
	}
	for (int i = 0; i < t.size(); i++)
	{
		m_textureCoords[i] = t[i];
	}
	for (int i = 0; i < n.size(); i++)
	{
		m_normals[i] = n[i];
	}
	for (int i = 0; i < in.size(); i++)
	{
		m_indices[i] = in[i];
	}
	for (int i = 0; i < IDs.size(); i++)
	{
		m_jointIDs[i] = IDs[i];
	}
	for (int i = 0; i < w.size(); i++)
	{
		m_vertexWeights[i] = w[i];
	}

}
std::shared_ptr<float[]> MeshData::getVertices() const
{
	return m_vertices;
}
std::shared_ptr <uint32_t[]> MeshData::getIndices() const
{
	return m_indices;
}
std::shared_ptr <float[]> MeshData::getNormals() const
{
	return m_normals;
}
std::shared_ptr <float[]> MeshData::getTextureCoords() const
{
	return m_textureCoords;
}
std::shared_ptr <float[]> MeshData::getVertexWeights() const
{
	return m_vertexWeights;
}
std::shared_ptr <int[]> MeshData::getJointIds() const
{
	return m_jointIDs;
}
size_t MeshData::getVertexCount() const
{
	return m_vertexCount / 3;
}
size_t MeshData::getIndicesCount() const
{
	return m_indicesCount;
}

size_t MeshData::getjointIDsCount() const
{
	return m_jointIDsCount;
}

size_t MeshData::getvertexWeightsCount() const
{
	return m_vertexWeightsCount;
}
