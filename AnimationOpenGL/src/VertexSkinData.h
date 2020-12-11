#pragma once

#include <vector>

class VertexSkinData
{
public:
	std::vector<int> jointIDs;
	std::vector<float> weights;

	void addJointEffect(int jointID, float weight);
	void limitJointNumber(int max);
private:
	void fillEmptyWeights(int max);
	float saveTopWeights(float* topWeightsArray, int topWeightsArrayLength);
	void refillWeightList(float* topWeights, int topWeightsLength, float total);
	void removeExcessJointIDs(int max);
};