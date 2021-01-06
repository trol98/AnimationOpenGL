#pragma once

#include <vector>

#include "VertexSkinData.h"

#include "vendor/glm/glm/glm.hpp"

class Vertex
{
private:
	static const int INVALID_INDEX;

	glm::vec3 m_position;

	int m_textureIndex;
	int m_normalIndex;
	int m_index;
	float m_length;

	Vertex* m_duplicateVertex;
	VertexSkinData m_weightsData;

	std::vector<glm::vec3> m_tangents;
	glm::vec3 m_averagedTangent;
public:
	Vertex(int index, const glm::vec3& position, const VertexSkinData& weightsData);

	VertexSkinData getWeightsData() const;

	void addTangent(const glm::vec3& tangent);
	void averageTangents();
	glm::vec3 getAverageTangent() const;

	int getIndex() const;
	float getLength() const;
	bool isSet() const;
	bool hasSameTextureAndNormal(int otherTextureIndex, int otherNormalIndex) const;

	void setTextureIndex(int textureIndex);
	void setNormalIndex(int normalIndex);
	int getTextureIndex() const;
	int getNormalIndex() const;

	glm::vec3 getPosition() const;

	Vertex* getDuplicateVertex() const;
	void setDuplicateVertex(Vertex* duplicateVertex);

};
