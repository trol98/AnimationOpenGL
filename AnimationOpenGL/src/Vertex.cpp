#include "Vertex.h"

const int Vertex::INVALID_INDEX = -1;

Vertex::Vertex(int index, const glm::vec3& position, const VertexSkinData& weightsData)
{
}

VertexSkinData Vertex::getWeightsData() const
{
	return m_weightsData;
}

void Vertex::addTangent(const glm::vec3& tangent)
{
	m_tangents.emplace_back(tangent);
}

void Vertex::averageTangents()
{
	if (!m_tangents.empty())
	{
		for (const auto& tangent : m_tangents)
		{
			m_averagedTangent += tangent;
		}
		m_averagedTangent = glm::normalize(m_averagedTangent);
	}
}

glm::vec3 Vertex::getAverageTangent() const
{
	return m_averagedTangent;
}

int Vertex::getIndex() const
{
	return m_index;
}

float Vertex::getLength() const
{
	return m_length;
}

bool Vertex::isSet() const
{
	return ((m_textureIndex != INVALID_INDEX) && (m_normalIndex != INVALID_INDEX));
}

bool Vertex::hasSameTextureAndNormal(int otherTextureIndex, int otherNormalIndex) const
{
	return ((otherTextureIndex == m_textureIndex) && (otherNormalIndex == m_normalIndex));
}

void Vertex::setTextureIndex(int textureIndex)
{
	m_textureIndex = textureIndex;
}

void Vertex::setNormalIndex(int normalIndex)
{
	m_normalIndex = normalIndex;
}

int Vertex::getTextureIndex() const
{
	return m_textureIndex;
}

int Vertex::getNormalIndex() const
{
	return m_normalIndex;
}

glm::vec3 Vertex::getPosition() const
{
	return m_position;
}

Vertex* Vertex::getDuplicateVertex() const
{
	return m_duplicateVertex;
}

void Vertex::setDuplicateVertex(Vertex* duplicateVertex)
{
	m_duplicateVertex = duplicateVertex;
}
