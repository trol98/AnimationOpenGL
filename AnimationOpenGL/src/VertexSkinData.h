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
	float saveTopWeights(std::vector<float>& topWeightsArray);
	void refillWeightList(const std::vector<float>& topWeights, float total);
	void removeExcessJointIds(int max);
};