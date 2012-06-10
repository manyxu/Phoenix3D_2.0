/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2SoundPanel.hpp
*
* 版本		:	1.0 (2011/04/11)
*
* 作者		：	more
*
*/

#ifndef PX2SOUNDPANEL_HPP
#define PX2SOUNDPANEL_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class SoundPanel : public wxPanel, public PX2::EventHandler
	{
	public:
		SoundPanel (wxWindow *parent);

		void OnSliderUpdate (wxCommandEvent &event);
		void OnRadio (wxCommandEvent &event);
		void OnCheckbox (wxCommandEvent& event);
		void OnButton (wxCommandEvent& event);
		void OnSize(wxSizeEvent& e);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		SoundPanel ();

		void SetActor (PX2::Actor *actor);
		PX2::SoundActorPtr mSoundActor;

		wxTextCtrl *mName;
		wxTextCtrl *mFilename;

		wxTextCtrl *mVolume;
		wxSlider *mVolumeSlider;
		wxTextCtrl *mRangeIn;
		wxSlider *mRangeInSlider;
		wxTextCtrl *mRangeOut;
		wxSlider *mRangeOutSlider;

		wxRadioButton *mLoop;
		wxRadioButton *mOnce;
		wxRadioButton *mOEOP;
		wxCheckBox *mIs3d;
		wxButton *mTestPlay;

		DECLARE_EVENT_TABLE();
	};

}

#endif