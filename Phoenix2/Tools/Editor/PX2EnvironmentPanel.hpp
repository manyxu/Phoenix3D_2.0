/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EnvironmentPanel.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2ENVIRONMENTPANEL_HPP
#define PX2ENVIRONMENTPANEL_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2AmbientRegionActor.hpp"

namespace PX2Editor
{

	class EnvironmentPanel : public wxPanel, public PX2::EventHandler
	{
	public:
		EnvironmentPanel (wxWindow *parent);

		void OnSliderUpdate (wxCommandEvent &event);
		void OnButton (wxCommandEvent& event);
		void OnSize(wxSizeEvent& e);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		EnvironmentPanel ();
		void OnColourChange(wxColourPickerEvent &e);
		void SetActor (PX2::Actor *actor);

		wxTextCtrl *mName;
		wxTextCtrl *mHorAngle;
		wxSlider *mHorSlider;
		wxTextCtrl *mVerAngle;
		wxSlider *mVerSlider;
		wxColourPickerCtrl *mDirDiffColor;
		wxCheckBox *mUseShadow;
		wxSlider *mShadowStrenghtSlider;
		PX2::AmbientRigionActorPtr mARActor;

		DECLARE_EVENT_TABLE();
	};

}

#endif