/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2SceneSettingPropertyGrid.hpp
*
* 版本		:	1.0 (2011/02/29)
*
* 作者		：	more
*
*/

#ifndef PX2SCENESETTINGPROPERTYGRID_HPP
#define PX2SCENESETTINGPROPERTYGRID_HPP

#include "PX2ObjectPropertyGrid.hpp"

namespace PX2Editor
{

	class SceneSettingPropertyGrid : public ObjectPropertyGrid
	{
	public:
		SceneSettingPropertyGrid (wxWindow *parent);
		~SceneSettingPropertyGrid ();

		DECLARE_DYNAMIC_CLASS(SceneSettingPropertyGrid)

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

		SceneSettingPropertyGrid ();

		bool mDrawTerrain;
		bool mDrawWater;
		bool mDrawPhysics;
	};

}

#endif