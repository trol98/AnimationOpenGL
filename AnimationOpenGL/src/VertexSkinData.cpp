#include "VertexSkinData.h"

void VertexSkinData::addJointEffect(int jointID, float weight)
{
	for (int i = 0; i < weights.size(); i++) 
	{
		if (weight > weights[i]) 
		{
			jointIDs.insert(jointIDs.begin() + i, jointID);
			weights.insert(weights.begin() + i, weight);
			return;
		}
	}
	jointIDs.emplace_back(jointID);
	weights.emplace_back(weight);
}
void VertexSkinData::limitJointNumber(int max)
{
	if (jointIDs.size() > max) 
	{
		float* topWeights = new float[max];
		float total = saveTopWeights(topWeights);
		refillWeightList(topWeights, total);
		removeExcessJointIds(max);
	}
	else if (jointIDs.size() < max) 
	{
		fillEmptyWeights(max);
	}
}
void VertexSkinData::fillEmptyWeights(int max)
{}
float VertexSkinData::saveTopWeights(std::vector<float>& topWeightsArray)
{}
void VertexSkinData::refillWeightList(const std::vector<float>& topWeights, float total)
{}
void VertexSkinData::removeExcessJointIds(int max)
{}
