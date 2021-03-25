#pragma once

#include <unordered_map>
#include <string>
#include "JointTransform.h"

class KeyFrame
{
private:
	const float m_timeStamp;
	std::unordered_map<std::string, JointTransform*> m_pose;
public:
	KeyFrame(float timeStamp, const std::unordered_map<std::string, JointTransform*>& jointKeyFrames)
		:m_timeStamp(timeStamp), m_pose(jointKeyFrames)
	{}
	float getTimeStamp() const
	{
		return m_timeStamp;
	}
	std::unordered_map<std::string, JointTransform*> getJointKeyFrames() 
	{
		return m_pose;
	}
	~KeyFrame()
	{
		for (const auto& elem : m_pose)
		{
			delete elem.second;
		}
	}
};
