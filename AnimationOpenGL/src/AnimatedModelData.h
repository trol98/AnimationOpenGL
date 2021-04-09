#pragma once
#include <iostream>
#include "SkeletonData.h"
#include "MeshData.h"

class AnimatedModelData
{
private:
	const SkeletonData* m_joints;
	const MeshData* m_mesh;
public:
	AnimatedModelData(const MeshData* m_mesh, const SkeletonData* m_joints)
		:m_joints(m_joints), m_mesh(m_mesh)
	{
	}
	const SkeletonData* getJointsData() const
	{
		return m_joints;
	}

	const MeshData* getMeshData() const
	{
		return m_mesh;
	}

	~AnimatedModelData()
	{
		delete m_joints;
		delete m_mesh;
		m_joints = nullptr;
		m_mesh = nullptr;
	}
};