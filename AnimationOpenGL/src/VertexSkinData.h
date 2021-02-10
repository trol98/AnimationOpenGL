#pragma once

#include <vector>

class VertexSkinData
{
public:
	std::vector<int> jointIDs;
	std::vector<float> weights;

	VertexSkinData(); // please delete this after SkinDataLoader is complete
	void addJointEffect(int jointID, float weight);
	void limitJointNumber(size_t max);
private:
	void fillEmptyWeights(size_t max);
	float saveTopWeights(float* topWeightsArray, int topWeightsArrayLength);
	void refillWeightList(float* topWeights, int topWeightsLength, float total);
	void removeExcessJointIDs(size_t max);
};