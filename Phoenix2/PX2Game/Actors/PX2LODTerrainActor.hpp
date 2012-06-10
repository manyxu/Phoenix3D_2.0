/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2LodTerrainActor.hpp
*
* 版本		:	1.0 (2011/02/25)
*
* 作者		：	more
*
*/

#ifndef PX2LODTERRAINACTOR_HPP
#define PX2LODTERRAINACTOR_HPP

#include "PX2Actor.hpp"


namespace PX2
{

	class LODTerrainActor : public Actor
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(LODTerrainActor);

	public:
		LODTerrainActor ();
		virtual ~LODTerrainActor ();

		void SetTerrain (LODTerrain *terrain);
		LODTerrain *GetTerrain ();

		void UseLOD (bool use);
		bool UsingLOD ();

		void SetPixelTolerance (float tolerance);
		float GetPixelTolerance ();

		// 消息处理
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

	protected:
		LODTerrain *mTerrain;
		bool mUsingLOD;
	};

	PX2_REGISTER_STREAM(LODTerrainActor);
	typedef Pointer0<LODTerrainActor> LODTerrainActorPtr;
#include "PX2LodTerrainActor.inl"

}

#endif