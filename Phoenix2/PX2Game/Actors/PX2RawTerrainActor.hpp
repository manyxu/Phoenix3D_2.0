/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2RawTerrainActor.hpp
*
* 版本		:	1.0 (2011/05/14)
*
* 作者		：	more
*
*/

#ifndef PX2RAWTERRAINACTOR_HPP
#define PX2RAWTERRAINACTOR_HPP

#include "PX2Actor.hpp"

namespace PX2
{

	class RawTerrainActor : public Actor
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(RawTerrainActor);

	public:
		RawTerrainActor ();
		virtual ~RawTerrainActor ();

		void SetTerrain (RawTerrain *terrain);
		RawTerrain *GetTerrain ();

		virtual void EnablePhysics (bool enable);

		// 消息处理
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

	protected:
		void _EnablePhysics ();
		void _DisablePhysics ();

		RawTerrainPtr mTerrain;
	};

	PX2_REGISTER_STREAM(RawTerrainActor);
	typedef Pointer0<RawTerrainActor> RawTerrainActorPtr;
#include "PX2RawTerrainActor.inl"

}

#endif