#include "VertexSkinData.h"

#include <algorithm> 

//VertexSkinData::VertexSkinData()
//{
//	jointIDs.resize(3);// DEBUG ONLY
//	weights.resize(3); // DEBUG ONLY
//}

void VertexSkinData::addJointEffect(int jointID, float weight)
{
	for (size_t i = 0; i < weights.size(); i++) 
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
void VertexSkinData::limitJointNumber(size_t max)
{
	if (jointIDs.size() > max) 
	{
		float* topWeights = new float[max];
		float total = saveTopWeights(topWeights, max);
		refillWeightList(topWeights, max, total);
		removeExcessJointIDs(max);
		delete[] topWeights;
	}
	else if (jointIDs.size() < max) 
	{
		fillEmptyWeights(max);
	}
}
void VertexSkinData::fillEmptyWeights(size_t max)
{
	while (jointIDs.size() < max) 
	{
		jointIDs.emplace_back(0);
		weights.emplace_back(0.0f);
	}
}
float VertexSkinData::saveTopWeights(float* topWeightsArray, int maxLength)
{
	float total = 0;
	for (int i = 0; i < maxLength; i++) 
	{
		topWeightsArray[i] = weights[i];
		total += topWeightsArray[i];
	}
	return total;
}
void VertexSkinData::refillWeightList(float* topWeights, int maxLength, float total)
{
	weights.clear();
	for (int i = 0; i < maxLength; i++) 
	{
		weights.emplace_back(std::min(topWeights[i] / total, 1.0f));
	}
}
void VertexSkinData::removeExcessJointIDs(size_t max)
{
	while (jointIDs.size() > max) 
	{
		jointIDs.pop_back();
	}
}
