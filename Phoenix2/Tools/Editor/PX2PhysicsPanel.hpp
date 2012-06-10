/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2PhysicsPanel.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2PHYSICSPANEL_HPP
#define PX2PHYSICSPANEL_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class ModelPhysicsPropertyGrid;

	class PhysicsPanel : public wxPanel
	{
	public:
		PhysicsPanel (wxWindow *parent);
		~PhysicsPanel ();

		void OnButton (wxCommandEvent& event);

		void SetActor (PX2::Actor *actor);

	protected:
		DECLARE_EVENT_TABLE();

		PhysicsPanel ();

		wxButton* mApply;
		ModelPhysicsPropertyGrid *mPropertyGrid;
		PX2::ActorPtr mActor;
	};

}

#endif