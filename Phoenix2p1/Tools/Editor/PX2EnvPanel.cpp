/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EnvPanel.cpp
*
*/

#include "PX2EnvPanel.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(EvnPanel, wxPanel)
EVT_SLIDER(wxID_ANY, EvnPanel::OnSliderUpdate)
EVT_BUTTON(wxID_ANY, EvnPanel::OnButton)
EVT_TEXT_ENTER(wxID_ANY, EvnPanel::OnTextEnter)
EVT_COLOURPICKER_CHANGED(wxID_ANY, EvnPanel::OnColourChange)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
EvnPanel::EvnPanel (wxWindow *parent)
{
	const bool bSuccess = wxXmlResource::Get()->LoadPanel(this, parent,
		TEXT("Environment") );

	assertion(bSuccess, "Load EvnPanel failed!");
	PX2_UNUSED(bSuccess);

	mName = (wxTextCtrl *)FindWindow(XRCID("mName"));
	assertion(mName!=0, "Window must be find!");

	mHorAngle = (wxTextCtrl*)FindWindow(XRCID("mHorAngle"));
	assertion(mHorAngle!=0, "Window must be find!");

	mHorSlider = (wxSlider*)FindWindow(XRCID("mHorSlider"));
	assertion(mHorSlider!=0, "Window must be find!");

	mVerAngle = (wxTextCtrl*)FindWindow(XRCID("mVerAngle"));
	assertion(mVerAngle!=0, "Window must be find!");

	mVerSlider = (wxSlider*)FindWindow(XRCID("mVerSlider"));
	assertion(mVerSlider!=0, "Window must be find!");

	mDirDiffColor = (wxColourPickerCtrl*)FindWindow(XRCID("mDirDiffColor"));
	assertion(mDirDiffColor!=0, "Window must be find!");

	mLightIntensity = (wxTextCtrl*)FindWindow(XRCID("mLightIntensity"));
	assertion(mLightIntensity!=0, "Window must be find!");

	mUseShadow = (wxCheckBox*)FindWindow(XRCID("mUseShadow"));
	assertion(mUseShadow!=0, "Window must be find!");

	mShadowStrenghtSlider = (wxSlider*)FindWindow(
		XRCID("mShadowStrenghtSlider"));
	assertion(mShadowStrenghtSlider!=0, "Window must be find!");
}
//-----------------------------------------------------------------------------
void EvnPanel::OnSliderUpdate (wxCommandEvent &event)
{
	if (mARActor)
	{
		int horValue = mHorSlider->GetValue();
		float horAngle = 360.0f * horValue/100.0f;
		wxString strHor = wxString::Format("%.2f", horAngle);
		mHorAngle->Clear();
		mHorAngle->WriteText(strHor);
		mARActor->mHorAngle = horAngle;

		int verValue = mVerSlider->GetValue();
		float verAngle = 360.0f * verValue/100.0f;
		mARActor->mVerAngle = verAngle;
		wxString strVer = wxString::Format("%.2f", verAngle);
		mVerAngle->Clear();
		mVerAngle->WriteText(strVer);
		mARActor->mVerAngle = verAngle;
	}
}
//-----------------------------------------------------------------------------
void EvnPanel::OnButton (wxCommandEvent& event)
{
}
//-----------------------------------------------------------------------------
void EvnPanel::OnTextEnter (wxCommandEvent& event)
{
	if (event.GetEventObject() == mLightIntensity)
	{
		float val = (float)wxAtof(event.GetString().GetData());
		mARActor->mDirLightIntensity = val;
	}
}
//-----------------------------------------------------------------------------
void EvnPanel::SetActor (PX2::AmbientRegionActor *actor)
{
	mARActor = actor;

	if (mARActor)
	{
		mName->Clear();
		mName->WriteText(mARActor->GetName());

		float horAngle = mARActor->mHorAngle;
		wxString horStr = wxString::Format("%.2f", horAngle);
		mHorAngle->Clear();
		mHorAngle->WriteText(horStr);
		mHorSlider->SetValue((int)(100*horAngle/360.0f));

		float verAngle = mARActor->mVerAngle;
		wxString verStr = wxString::Format("%.2f", verAngle);
		mVerAngle->Clear();
		mVerAngle->WriteText(verStr);
		mVerSlider->SetValue((int)(100*verAngle/360.0f));

		wxColour dirLightDiffColor = wxColour(
			(unsigned char)(mARActor->mDirLightDiffColor[0]*255),
			(unsigned char)(mARActor->mDirLightDiffColor[1]*255),
			(unsigned char)(mARActor->mDirLightDiffColor[2]*255));
		mDirDiffColor->SetColour(dirLightDiffColor);

		float intensity = mARActor->mDirLightIntensity;
		wxString strIntensity = wxString::Format("%.2f", intensity);
		mLightIntensity->Clear();
		mLightIntensity->WriteText(strIntensity);
	}
}
//-----------------------------------------------------------------------------
void EvnPanel::OnColourChange(wxColourPickerEvent &e)
{
	if (!mARActor)
		return;

	if (mDirDiffColor == e.GetEventObject())
	{
		wxColour dirDiffColor = mDirDiffColor->GetColour();
		mARActor->mDirLightDiffColor = Float4(dirDiffColor.Red()/255.0f,
			dirDiffColor.Green()/255.0f, dirDiffColor.Blue()/255.0f, 1.0f);
	}
}
//-----------------------------------------------------------------------------