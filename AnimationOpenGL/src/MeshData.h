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
	const size_t m_jointIDsCount;
	const size_t m_vertexWeightsCount;
public:
	MeshData(const std::vector<float>& v, const std::vector<float>& t, const std::vector<float>& n,
		const std::vector<int>& i, const std::vector<int>& IDs, const std::vector<float>& w);

	std::shared_ptr <float[]> getVertices() const;
	std::shared_ptr <uint32_t[]> getIndices() const;
	std::shared_ptr <float[]> getNormals() const;
	std::shared_ptr <float[]> getTextureCoords() const;
	std::shared_ptr <float[]> getVertexWeights() const;
	std::shared_ptr <int[]> getJointIds() const;

	size_t getVertexCount() const;
	size_t getIndicesCount() const;
	size_t getjointIDsCount() const;
	size_t getvertexWeightsCount() const;

};