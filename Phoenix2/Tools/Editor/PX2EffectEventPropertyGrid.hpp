/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EffectEventPropertyGrid.hpp
*
* 版本		:	1.0 (2012/01/29)
*
* 作者		：	more
*
*/

#ifndef PX2EFFECTEVENTPROPERTYGRID_HPP
#define PX2EFFECTEVENTPROPERTYGRID_HPP

#include "PX2ObjectPropertyGrid.hpp"

namespace PX2Editor
{

	class EffectEventPropertyGrid : public ObjectPropertyGrid
	{
	public:
		EffectEventPropertyGrid (wxWindow *parent);
		~EffectEventPropertyGrid ();

		DECLARE_DYNAMIC_CLASS(EffectEventPropertyGrid)

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

		EffectEventPropertyGrid ();
		void RefreshOnEffectEvent ();

		bool mIsFade;
		float mSpeedMin;
		float mSpeedMax;
		PX2::Float3 mSpeedDirMin;
		PX2::Float3 mSpeedDirMax;
		float mSizeUMin;
		float mSizeUMax;
		float mSizeRMin;
		float mSizeRMax;
		PX2::Float3 mColorMin;
		PX2::Float3 mColorMax;
		float mAlphaMin;
		float mAlphaMax;
	};

}

#endif