/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2LODTerrainVertex.hpp
*
* 版本		:	1.0 (2011/03/03)
*
* 作者		：	more
*
*/

#ifndef PX2LODTERRAINVERTEX_HPP
#define PX2LODTERRAINVERTEX_HPP

#include "PX2TerrainPrerequisites.hpp"
#include "PX2Assert.hpp"

namespace PX2
{
	/// LOD地形顶点类
	class PX2_TERRAIN_ENTRY LODTerrainVertex
	{
	public:
		LODTerrainVertex ();

		void SetDependent (int i, LODTerrainVertex *pkDependent);
		LODTerrainVertex *GetDependent (int i);
		bool IsEnabled () const;
		void Enable ();
		void Disable ();

	protected:
		LODTerrainVertex *mDependent[2];
		bool mEnabled; //< 该顶点是否参与网格世界
	};

#include "PX2LODTerrainVertex.inl"
}

#endif