/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ObjectPropertyGrid.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2OBJECTPROPERTYGRID_HPP
#define PX2OBJECTPROPERTYGRID_HPP

#include "PX2PropertyGrid.hpp"

namespace PX2Editor
{

	class ObjectPropertyGrid : public PropertyGrid
	{
	public:
		ObjectPropertyGrid (wxWindow *parent);
		virtual ~ObjectPropertyGrid ();

		DECLARE_DYNAMIC_CLASS(ObjectPropertyGrid)

		void SetObject (PX2::Object *actor);
		virtual void OnSetObject (PX2::Object *actor);
		PX2::Object *GetObject ();

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		void OnSize(wxSizeEvent &e);
		void OnMove(wxMoveEvent &e);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		ObjectPropertyGrid ();
		void Refresh ();
		
		DECLARE_EVENT_TABLE()

		PX2::ObjectPtr mObject;
		bool mObjectVisible;

		// Terrain
		bool mUseLOD;
		float mPixelTolerance;
	};
}

#endif