#pragma once

#include <vector>
#include <memory>

class MeshData
{
private:
	const std::shared_ptr<float[]> m_vertices;
	const std::shared_ptr<float[]> m_textureCoords;
	const std::shared_ptr<float[]> m_normals;
	const std::shared_ptr<uint32_t[]>   m_indices;
	const std::shared_ptr<int[]>   m_jointIDs;
	const std::shared_ptr<float[]> m_vertexWeights;

	const size_t m_vertexCount;
	const size_t m_indicesCount;
public:
	MeshData(const std::vector<float>& v, const std::vector<float>& t, const std::vector<float>& n,
		const std::vector<int>& i, const std::vector<int>& IDs, const std::vector<float>& w);

	std::shared_ptr <float[]> getVertices();
	std::shared_ptr <uint32_t[]> getIndices ();
	std::shared_ptr <float[]> getNormals ();
	std::shared_ptr <float[]> getTextureCoords ();
	std::shared_ptr <float[]> getVertexWeights ();
	std::shared_ptr <int[]> getJointIds();

	size_t getVertexCount();
	size_t getIndicesCount();

};