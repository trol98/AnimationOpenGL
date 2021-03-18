#include "SkinLoader.h"

SkinLoader::SkinLoader(const std::shared_ptr<XMLNode>& controllerNode, int maxWeights)
	:m_skinningData(controllerNode->getChild("controller")->getChild("skin")), m_maxWeights(maxWeights)
{
}

SkinningData* SkinLoader::extractSkinData()
{
	// TODO: Pulling out vertex_weights node for the 2 following methods
	std::vector<std::string> jointList = loadJointsList();
	float* weights = loadWeights();

	std::shared_ptr<XMLNode> weightsDataNode = m_skinningData->getChild("vertex_weights");

	std::vector<int> effectorJointCounts = getEffectiveJointsCount(weightsDataNode);

	std::vector<VertexSkinData> vertexWeights = getSkinData(weightsDataNode, effectorJointCounts, weights);

	delete[] weights;
	return new SkinningData(jointList, vertexWeights);
}

std::vector<std::string> SkinLoader::loadJointsList()
{
	std::shared_ptr<XMLNode> inputNode = m_skinningData->getChild("vertex_weights");
	std::string jointDataID = inputNode->getChildWithAttribute("input", "semantic", "JOINT")->getAttribute("source").substr(1);

	std::shared_ptr<XMLNode> jointsNode = m_skinningData->getChildWithAttribute("source", "id", jointDataID)->getChild("Name_array");

	std::vector<std::string> names = StringUtils::split(jointsNode->getData(), ' ');

	// TODO: Consider changing names to std::string []
	return names;
}

float* SkinLoader::loadWeights()
{
	std::shared_ptr<XMLNode> inputNode = m_skinningData->getChild("vertex_weights");
	std::string jointDataID = inputNode->getChildWithAttribute("input", "semantic", "WEIGHT")->getAttribute("source").substr(1);

	std::shared_ptr<XMLNode> weightsNode = m_skinningData->getChildWithAttribute("source", "id", jointDataID)->getChild("float_array");
	std::vector<std::string> rawData = StringUtils::split(weightsNode->getData(), ' ');

	// TODO: Consider changing this to std::shared_ptr ?
	float* weights = new float[rawData.size()];
	for (size_t i = 0; i < rawData.size(); i++)
	{
		weights[i] = std::stof(rawData[i]);
	}

	return weights;
}

std::vector<int> SkinLoader::getEffectiveJointsCount(const std::shared_ptr<XMLNode>& weightsDataNode)
{
	std::vector<std::string> rawData = StringUtils::split(weightsDataNode->getChild("vcount")->getData(), ' ');

	std::vector<int> counts(rawData.size());
	for (size_t i = 0; i < rawData.size(); i++)
	{
		counts[i] = std::stoi(rawData[i]);
	}
	return counts;
}

std::vector<VertexSkinData> SkinLoader::getSkinData(const std::shared_ptr<XMLNode>& weightsDataNode, const std::vector<int>& counts, float* weights)
{
	std::vector<std::string> rawData = StringUtils::split(weightsDataNode->getChild("v")->getData(), ' ');
	// TODO: Changing this to a raw/shared pointer
	std::vector<VertexSkinData> skinningData;
	int pointer = 0;
	for (const auto& count : counts)
	{
		VertexSkinData skinData;
		for (int i = 0; i < count; i++)
		{
			int jointID = std::stoi(rawData[pointer++]);
			int weightID = std::stoi(rawData[pointer++]);
			skinData.addJointEffect(jointID, weights[weightID]);
		}

		skinData.limitJointNumber(m_maxWeights);
		skinningData.emplace_back(skinData);
	}

	return skinningData;
}
