/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2LightActor.hpp
*
* 版本		:	1.0 (2011/02/25)
*
* 作者		：	more
*
*/

#ifndef PX2LIGHTACTOR_HPP
#define PX2LIGHTACTOR_HPP

#include "PX2Actor.hpp"

namespace PX2
{

	class LightActor : public Actor
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(LightActor);

	public:
		LightActor (PX2::Light *light=0);
		~LightActor ();

		void SetLight (PX2::Light *light);
		PX2::Light *GetLight ();

		PX2::LightNode *GetLightNode ();

		// 消息处理
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

	protected:
		PX2::LightNodePtr mLightNode;
		PX2::LightPtr mLight;
	};

	PX2_REGISTER_STREAM(LightActor);
	typedef Pointer0<LightActor> LightActorPtr;
#include "PX2LightActor.inl"

}

#endif