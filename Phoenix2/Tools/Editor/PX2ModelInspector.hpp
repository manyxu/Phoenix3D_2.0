/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2TerrainInspector.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2MODELINSPECTOR_HPP
#define PX2MODELINSPECTOR_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2MaterialPane.hpp"
#include "PX2EventHandler.hpp"

namespace PX2Editor
{

	class ModelActorPropertyGrid;
	class PhysicsPanel;

	class ModelInspector : public wxScrolledWindow, public PX2::EventHandler
	{
	public:
		ModelInspector (wxWindow *parent);
		~ModelInspector ();

		void OnSize(wxSizeEvent& e);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()

		ModelInspector ();
		void SetActor (PX2::Actor *actor);

		PX2::ActorPtr mActor;
		wxFoldPanelBar *mFoldPaneBar;
		ModelActorPropertyGrid *mModelActorPropGrid;
		PhysicsPanel *mPhysicsPanel;
		MaterialPanel *mMaterialPanel;
	};
}

#endif