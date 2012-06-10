/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	LightActorPropertyGrid.hpp
*
* 版本		:	1.0 (2012/03/18)
*
* 作者		：	more
*
*/

#ifndef PX2LIGHTACTORPROPERTYGRID_HPP
#define PX2LIGHTACTORPROPERTYGRID_HPP

#include "PX2ObjectPropertyGrid.hpp"
#include "PX2LightActor.hpp"

namespace PX2Editor
{

	class LightActorPropertyGrid : public ObjectPropertyGrid
	{
	public:
		LightActorPropertyGrid (wxWindow *parent);
		~LightActorPropertyGrid ();

		DECLARE_DYNAMIC_CLASS(LightActorPropertyGrid)

		virtual void OnSetObject(PX2::Object *object);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()

		LightActorPropertyGrid ();
		void RefreshOnLightActor ();

		std::string mName;
		PX2::Float3 mPosition;
		PX2::Float3 mDirection;
		float mAngle;
		PX2::Float3 mAmbientColor;
		PX2::Float3 mDiffuseColor;
		PX2::Float3 mSpecularColor;

		float mConstant;   //< default: 1
		float mLinear;     //< default: 0
		float mQuadratic;  //< default: 0
		float mIntensity;  //< default: 1
	};

}

#endif