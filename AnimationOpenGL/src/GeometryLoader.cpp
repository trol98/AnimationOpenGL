#include "GeometryLoader.h"

#include <iostream> // NOTE: Debug only


#include "vendor/glm/glm/glm.hpp"
#include "vendor/glm/glm/gtc/matrix_transform.hpp"

const glm::mat4 GeometryLoader::CORRECTION = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

GeometryLoader::GeometryLoader(const std::shared_ptr<XMLNode>& geometryNode, const std::vector<VertexSkinData>& vertexWeights)
	:m_meshData(geometryNode->getChild("geometry")->getChild("mesh")), m_vertexWeights(vertexWeights)
{
}

MeshData GeometryLoader::extractModelData()
{
	// Raw data

	readPositions();
	readNormals();
	readTextureCoords();

	// Transforming data

	assembleVertices();
	removeUnusedVertices();
	initArrays();
	convertDataToArrays();
	convertIndicesListToArray();

	return MeshData(m_verticesArray, m_texturesArray, m_normalsArray, m_indicesArray, m_jointIDsArray, m_weightsArray);
}

void GeometryLoader::readPositions()
{
	std::string positionsID = m_meshData->getChild("vertices")->getChild("input")->getAttribute("source").substr(1);
	std::shared_ptr<XMLNode> positionsData = m_meshData->getChildWithAttribute("source", "id", positionsID)->getChild("float_array");

	int count = std::stoi(positionsData->getAttribute("count"));

	std::vector<std::string> posData = split(positionsData->getData(), ' ');

	// count will be always divisible by 3
	for (int i = 0; i < count / 3; i++)
	{
		float x = std::stof(posData[i * 3 + 0]);
		float y = std::stof(posData[i * 3 + 1]);
		float z = std::stof(posData[i * 3 + 2]);

		glm::vec4 position(x, y, z, 1.0f);
		glm::vec4 result = CORRECTION * position;

		size_t index = m_vertices.size();
		m_vertices.emplace_back(std::make_shared<Vertex>(index, glm::vec3(position), m_vertexWeights.at(index)));
	}
}

void GeometryLoader::readNormals()
{
	std::string normalsId = m_meshData->getChild("polylist")->getChildWithAttribute("input", "semantic", "NORMAL")->getAttribute("source").substr(1);
	std::shared_ptr<XMLNode> normalsData = m_meshData->getChildWithAttribute("source", "id", normalsId)->getChild("float_array");

	int count = std::stoi(normalsData->getAttribute("count"));
	std::vector<std::string> normData = split(normalsData->getData(), ' ');

	// count will be always divisible by 3
	for (int i = 0; i < count / 3; i++)
	{
		float x = std::stof(normData[i * 3 + 0]);
		float y = std::stof(normData[i * 3 + 1]);
		float z = std::stof(normData[i * 3 + 2]);

		glm::vec4 normal(x, y, z, 0.0f);
		normal = CORRECTION * normal;

		m_normals.emplace_back(glm::vec3(normal));
	}
}

void GeometryLoader::readTextureCoords()
{

	std::string texCoordsId = m_meshData->getChild("polylist")->getChildWithAttribute("input", "semantic", "TEXCOORD")->getAttribute("source").substr(1);
	std::shared_ptr<XMLNode> texCoordsData = m_meshData->getChildWithAttribute("source", "id", texCoordsId)->getChild("float_array");

	int count = std::stoi(texCoordsData->getAttribute("count"));
	std::vector<std::string> textureData = split(texCoordsData->getData(), ' ');

	// count will be always divisible by 2
	for (int i = 0; i < count / 2; i++)
	{
		float s = std::stof(textureData[i * 2 + 0]);
		float t = std::stof(textureData[i * 2 + 1]);

		m_textures.emplace_back(glm::vec2(s, t));
	}
}

void GeometryLoader::assembleVertices()
{
	std::shared_ptr<XMLNode> poly = m_meshData->getChild("polylist");

	int typeCount = poly->getChildren("input")->size();
	std::vector<std::string> indexData = split(poly->getChild("p")->getData(), ' ');

	//for (const auto& vertex : m_vertices)
	//{
	//	vertex->debugPrint();
	//}

	for (size_t i = 0; i < indexData.size() / typeCount; i++) {
		int positionIndex = std::stoi(indexData[i * typeCount + 0]);
		int normalIndex   =	std::stoi(indexData[i * typeCount + 1]);
		int texCoordIndex = std::stoi(indexData[i * typeCount + 2]);
		processVertex(positionIndex, normalIndex, texCoordIndex);
	}
}

std::shared_ptr<Vertex> GeometryLoader::processVertex(int positionIndex, int normalsIndex, int texureIndex)
{
	std::shared_ptr<Vertex> currentVertex = m_vertices.at(positionIndex);
	if (!currentVertex->isSet()) 
	{
		currentVertex->setTextureIndex(texureIndex);
		currentVertex->setNormalIndex(normalsIndex);
		m_indices.emplace_back(positionIndex);
		return currentVertex;
	}
	return dealWithAlreadyProcessedVertex(currentVertex, texureIndex, normalsIndex);
}

std::shared_ptr<Vertex> GeometryLoader::dealWithAlreadyProcessedVertex(std::shared_ptr<Vertex>& previousVertex, int newTextureIndex, int newNormalIndex)
{
	if (previousVertex->hasSameTextureAndNormal(newTextureIndex, newNormalIndex))
	{
		m_indices.emplace_back(previousVertex->getIndex());
		return previousVertex;
	}
	else 
	{
		std::shared_ptr<Vertex> anotherVertex = previousVertex->getDuplicateVertex();
		if (anotherVertex != nullptr)
		{
			return dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex);
		}
		else
		{
			std::shared_ptr<Vertex> duplicateVertex = std::make_shared<Vertex>(m_vertices.size(), previousVertex->getPosition(), previousVertex->getWeightsData());
			duplicateVertex->setTextureIndex(newTextureIndex);
			duplicateVertex->setNormalIndex(newNormalIndex);
			previousVertex->setDuplicateVertex(duplicateVertex);
			m_vertices.emplace_back(duplicateVertex);
			m_indices.emplace_back(duplicateVertex->getIndex());
			return duplicateVertex;
		}
	}
}

void GeometryLoader::removeUnusedVertices()
{
	for (auto& vertex : m_vertices) {
		vertex->averageTangents();
		if (!vertex->isSet()) {
			vertex->setTextureIndex(0);
			vertex->setNormalIndex(0);
		}
	}
}

void GeometryLoader::initArrays()
{
	m_verticesArray.resize(m_vertices.size() * 3);
	m_texturesArray.resize(m_vertices.size() * 2);
	m_normalsArray .resize(m_vertices.size() * 3);
	m_jointIDsArray.resize(m_vertices.size() * 3);
	m_weightsArray .resize(m_vertices.size() * 3);
}

float GeometryLoader::convertDataToArrays()
{
	float furthestPoint = 0;
	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		std::shared_ptr<Vertex> currentVertex = m_vertices.at(i);
		if (currentVertex->getLength() > furthestPoint)
		{
			furthestPoint = currentVertex->getLength();
		}
		glm::vec3 position = currentVertex->getPosition();
		glm::vec2 textureCoord = m_textures[currentVertex->getTextureIndex()];
		glm::vec3 normalVector = m_normals[currentVertex->getNormalIndex()];

		m_verticesArray[i * 3 + 0] = position.x;
		m_verticesArray[i * 3 + 1] = position.y;
		m_verticesArray[i * 3 + 2] = position.z;

		m_texturesArray[i * 2 + 0] = textureCoord.x;
		m_texturesArray[i * 2 + 1] = 1 - textureCoord.y; // reversed

		m_normalsArray[i * 3 + 0] = normalVector.x;
		m_normalsArray[i * 3 + 1] = normalVector.y;
		m_normalsArray[i * 3 + 2] = normalVector.z;

		VertexSkinData weights = currentVertex->getWeightsData();
		m_jointIDsArray[i * 3 + 0] = weights.jointIDs[0];
		m_jointIDsArray[i * 3 + 1] = weights.jointIDs[1];
		m_jointIDsArray[i * 3 + 2] = weights.jointIDs[2];

		m_weightsArray[i * 3 + 0] = weights.weights[0];
		m_weightsArray[i * 3 + 1] = weights.weights[1];
		m_weightsArray[i * 3 + 2] = weights.weights[2];
	}
	return furthestPoint;
}

std::vector<int> GeometryLoader::convertIndicesListToArray()
{
	m_indicesArray.resize(m_indices.size());
	for (size_t i = 0; i < m_indicesArray.size(); i++)
	{
		m_indicesArray[i] = m_indices[i];
	}
	return m_indicesArray;
}