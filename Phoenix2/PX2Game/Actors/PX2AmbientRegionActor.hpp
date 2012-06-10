/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2AmbientActor.hpp
*
* 版本		:	1.0 (2011/02/25)
*
* 作者		：	more
*
*/

#ifndef PX2AMBIENTACTOR_HPP
#define PX2AMBIENTACTOR_HPP

#include "PX2TriggerActor.hpp"

namespace PX2
{

	class AmbientRegionActor : public TriggerActor
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(AmbientRegionActor);

	public:
		AmbientRegionActor ();
		~AmbientRegionActor ();

		void SetLight (Light *light);
		Light *GetLight ();

		Float4 mAmbientColor;
		Float4 mDirLightDiffColor;
		Float4 mDirLightSpecColor;
		float mHorAngle; // (0-360)
		float mVerAngle; // (0-90)

		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

	private:
		LightPtr mLight;
	};

	PX2_REGISTER_STREAM(AmbientRegionActor);
	typedef Pointer0<AmbientRegionActor> AmbientRigionActorPtr;
#include "PX2AmbientRegionActor.inl"

}

#endif