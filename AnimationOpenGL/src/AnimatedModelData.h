#pragma once

#include "SkeletonData.h"
#include "MeshData.h"

class AnimatedModelData
{
private:
	const SkeletonData m_joints;
	const MeshData m_mesh;
public:
	AnimatedModelData(const SkeletonData& m_joints, const MeshData& m_mesh)
		:m_joints(m_joints), m_mesh(m_mesh)
	{
	}
	SkeletonData getJointsData() const
	{
		return m_joints;
	}

	MeshData getMeshData() const
	{
		return m_mesh;
	}
};