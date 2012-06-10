/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EnvironmentPanel.cpp
*
*/

#include "PX2EnvironmentPanel.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(EnvironmentPanel, wxPanel)
	EVT_SLIDER(wxID_ANY, EnvironmentPanel::OnSliderUpdate)
	EVT_BUTTON(wxID_ANY, EnvironmentPanel::OnButton)
	EVT_COLOURPICKER_CHANGED(wxID_ANY, EnvironmentPanel::OnColourChange)
	EVT_SIZE(EnvironmentPanel::OnSize)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
EnvironmentPanel::EnvironmentPanel (wxWindow *parent)
{
	const bool bSuccess = wxXmlResource::Get()->LoadPanel(this, parent,
		TEXT("Environment") );

	assertion(bSuccess, "Load EnvironmentPanel failed!");
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

	mUseShadow = (wxCheckBox*)FindWindow(XRCID("mUseShadow"));
	assertion(mUseShadow!=0, "Window must be find!");

	mShadowStrenghtSlider = (wxSlider*)FindWindow(
		XRCID("mShadowStrenghtSlider"));
	assertion(mShadowStrenghtSlider!=0, "Window must be find!");
}
//-----------------------------------------------------------------------------
void EnvironmentPanel::OnSliderUpdate (wxCommandEvent &event)
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
		float verAngle = 90.0f * verValue/100.0f;
		mARActor->mVerAngle = verAngle;
		wxString strVer = wxString::Format("%.2f", verAngle);
		mVerAngle->Clear();
		mVerAngle->WriteText(strVer);
		mARActor->mVerAngle = verAngle;
	}
}
//-----------------------------------------------------------------------------
void EnvironmentPanel::OnButton (wxCommandEvent& event)
{
}
//-----------------------------------------------------------------------------
void EnvironmentPanel::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void EnvironmentPanel::DoUpdate ()
{

}
//-----------------------------------------------------------------------------
void EnvironmentPanel::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::AddSelectActor))
	{
		int selectQuantity = ActorSelection::GetSingleton().GetActorQuantity();
		if (selectQuantity == 1)
		{
			Actor *actor = event->GetData<Actor*>();

			SetActor(actor);
		}
		else
		{
			SetActor(0);
		}
	}
	else if (EditorEventSpace::IsEqual(event, 
		EditorEventSpace::ClearSelectActor))
	{
		SetActor(0);
	}

	if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::RemoveActor))
	{
		Actor *actor = event->GetData<Actor*>();

		if (actor == mARActor)
			SetActor(0);
	}
}
//-----------------------------------------------------------------------------
void EnvironmentPanel::DoLeave ()
{

}
//-----------------------------------------------------------------------------
void EnvironmentPanel::OnSize (wxSizeEvent& e)
{
	wxPanel::OnSize(e);
}
//-----------------------------------------------------------------------------
void EnvironmentPanel::OnColourChange(wxColourPickerEvent &e)
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
void EnvironmentPanel::SetActor (PX2::Actor *actor)
{
	mARActor = DynamicCast<AmbientRegionActor>(actor);
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
		mVerSlider->SetValue((int)(100*verAngle/90.0f));

		wxColour dirLightDiffColor = wxColour(
			(unsigned char)(mARActor->mDirLightDiffColor[0]*255),
			(unsigned char)(mARActor->mDirLightDiffColor[1]*255),
			(unsigned char)(mARActor->mDirLightDiffColor[2]*255));
		mDirDiffColor->SetColour(dirLightDiffColor);
	}
}
//-----------------------------------------------------------------------------