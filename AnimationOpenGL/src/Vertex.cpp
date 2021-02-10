#include "Vertex.h"
#include <iostream>

const int Vertex::INVALID_INDEX = -1;

Vertex::Vertex(int index, const glm::vec3& position, const VertexSkinData& weightsData)
	:m_index(index), m_weightsData(weightsData), m_position(position), m_length(glm::length(position)),
	 m_normalIndex(), m_textureIndex(), m_duplicateVertex(nullptr), m_tangents(), m_averagedTangent()
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
			m_averagedTangent = m_averagedTangent +  tangent;
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

std::shared_ptr<Vertex> Vertex::getDuplicateVertex() const
{
	return m_duplicateVertex;
}

void Vertex::setDuplicateVertex(const std::shared_ptr<Vertex>& duplicateVertex)
{
	m_duplicateVertex = duplicateVertex;
}

void Vertex::debugPrint()
{
	std::cout << "{" << m_position.x << ", " << m_position.y << ", " << m_position.z << "}\n";

	std::cout << "IndexT: " << m_textureIndex << "\n";
	std::cout << "IndexN: " << m_textureIndex << "\n";
	std::cout << "Index : " << m_textureIndex << "\n";
	std::cout << "Length: " << m_textureIndex << "\n";
	std::cout << "--------------------------------\n";
}
