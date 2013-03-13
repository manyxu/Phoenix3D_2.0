/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EnvPanel.hpp
*
*/

#ifndef PX2ENVPANEL_HPP
#define PX2ENVPANEL_HPP

#include "PX2EditorPre.hpp"
#include "PX2AmbientRegionActor.hpp"

namespace PX2Editor
{

	class EvnPanel : public wxPanel
	{
	public:
		EvnPanel (wxWindow *parent);

		void OnSliderUpdate (wxCommandEvent &event);
		void OnButton (wxCommandEvent& event);
		void OnTextEnter (wxCommandEvent& event);

		void SetActor (PX2::AmbientRegionActor *actor);

	protected:
		DECLARE_EVENT_TABLE();

		EvnPanel ();
		void OnColourChange(wxColourPickerEvent &e);

		wxTextCtrl *mName;
		wxTextCtrl *mHorAngle;
		wxSlider *mHorSlider;
		wxTextCtrl *mVerAngle;
		wxSlider *mVerSlider;
		wxColourPickerCtrl *mDirDiffColor;
		wxTextCtrl *mLightIntensity;
		wxCheckBox *mUseShadow;
		wxSlider *mShadowStrenghtSlider;
		PX2::AmbientRigionActorPtr mARActor;
	};

}

#endif