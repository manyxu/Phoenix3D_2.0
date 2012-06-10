/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SoundPanel.cpp
*
*/

#include "PX2SoundPanel.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(SoundPanel, wxPanel)
	EVT_SLIDER(wxID_ANY, SoundPanel::OnSliderUpdate)
	EVT_BUTTON(wxID_ANY, SoundPanel::OnButton)
	EVT_SIZE(SoundPanel::OnSize)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
SoundPanel::SoundPanel (wxWindow *parent)
{
	const bool bSuccess = wxXmlResource::Get()->LoadPanel(this, parent,
		TEXT("Sound") );

	assertion(bSuccess, "Load SoundPanel failed!");
	PX2_UNUSED(bSuccess);

	mName = (wxTextCtrl*)FindWindow(XRCID("mName"));
	assertion(mName!=0, "Window must be find!");

	mFilename = (wxTextCtrl*)FindWindow(XRCID("mFilename"));
	assertion(mFilename!=0, "Window must be find!");

	mVolume = (wxTextCtrl*)FindWindow(XRCID("mVolume"));
	assertion(mVolume!=0, "Window must be find!");

	mVolumeSlider = (wxSlider*)FindWindow(XRCID("mVolumeSlider"));
	assertion(mVolumeSlider!=0, "Window must be find!");

	mRangeIn = (wxTextCtrl*)FindWindow(XRCID("mRangeIn"));
	assertion(mRangeIn!=0, "Window must be find!");

	mRangeInSlider = (wxSlider*)FindWindow(XRCID("mRangeInSlider"));
	assertion(mRangeInSlider!=0, "Window must be find!");

	mRangeOut = (wxTextCtrl*)FindWindow(XRCID("mRangeOut"));
	assertion(mRangeOut!=0, "Window must be find!");

	mRangeOutSlider = (wxSlider*)FindWindow(XRCID("mRangeOutSlider"));
	assertion(mRangeOutSlider!=0, "Window must be find!");

	mLoop = (wxRadioButton*)FindWindow(XRCID("mRadioLoop"));
	assertion(mLoop!=0, "Window must be find!");

	mOnce = (wxRadioButton*)FindWindow(XRCID("mRadioOnce"));
	assertion(mOnce!=0, "Window must be find!");

	mOEOP = 0;

	mIs3d = (wxCheckBox*)FindWindow(XRCID("mIs3d"));
	assertion(mIs3d!=0, "Window must be find!");

	mTestPlay = (wxButton*)FindWindow(XRCID("mButtonTestPlay"));
	assertion(mTestPlay!=0, "Window must be find!");
}
//-----------------------------------------------------------------------------
void SoundPanel::OnSliderUpdate (wxCommandEvent &event)
{
	PX2::Soundable *soundable = 0;
	if (mSoundActor)
	{
		soundable = mSoundActor->GetSoundable();
		if (!soundable)
			return;
	}

	float minDistance = soundable->GetMinDistance();
	float maxDistance = soundable->GetMaxDistance();
	PX2_UNUSED(minDistance);
	PX2_UNUSED(maxDistance);

	soundable->SetDistance(10.0f, 30.0f);

	//if (event.GetEventObject() == mVolumeSlider)
	//{
	//	int value = mVolumeSlider->GetValue();
	//	if (value > 0)
	//	{
	//		float volume = (float)value/100.0f;
	//		soundable->SetVolume(volume);

	//		wxString volumeStr = wxString::Format(wxT("%.2f"), volume);
	//		mVolume->Clear();
	//		mVolume->WriteText(volumeStr);
	//	}
	//}
	//else if (event.GetEventObject() == mRangeInSlider)
	//{
	//	int value = mRangeInSlider->GetValue();
	//	float inRange = (float)(value/100.0f)*10.0f;
	//	soundable->SetMinDistance(inRange);

	//	if (inRange > maxDistance)
	//	{
	//		maxDistance = inRange;
	//		soundable->SetMaxDistance(maxDistance);
	//		mRangeOutSlider->SetValue((int)(100*maxDistance/10.0f));

	//		wxString minStr = wxString::Format(wxT("%.2f"), inRange);
	//		mRangeIn->Clear();
	//		mRangeIn->WriteText(minStr);
	//		wxString maxStr = wxString::Format(wxT("%.2f"), maxDistance);
	//		mRangeOut->Clear();
	//		mRangeOut->WriteText(maxStr);
	//	}
	//}
	//else if (event.GetEventObject() == mRangeOutSlider)
	//{
	//	int value = mRangeOutSlider->GetValue();
	//	float outRange = (float)(value/100.0f)*10.0f;
	//	soundable->SetMaxDistance(outRange);

	//	if (outRange < minDistance)
	//	{
	//		minDistance = outRange;
	//		soundable->SetMinDistance(minDistance);
	//		mRangeInSlider->SetValue((int)(100*minDistance/10.0f));

	//		wxString minStr = wxString::Format(wxT("%.2f"), minDistance);
	//		mRangeIn->Clear();
	//		mRangeIn->WriteText(minStr);
	//		wxString maxStr = wxString::Format(wxT("%.2f"), outRange);
	//		mRangeOut->Clear();
	//		mRangeOut->WriteText(maxStr);
	//	}
	//}
}
//-----------------------------------------------------------------------------
void SoundPanel::OnRadio (wxCommandEvent &event)
{

}
//-----------------------------------------------------------------------------
void SoundPanel::OnCheckbox (wxCommandEvent& event)
{

}
//-----------------------------------------------------------------------------
void SoundPanel::OnButton (wxCommandEvent& event)
{
	if (event.GetEventObject() == mTestPlay)
	{
		if (mSoundActor)
		{
			PX2::Soundable *soundable = mSoundActor->GetSoundable();
			if (soundable)
			{
				if (!soundable->IsPlaying())
					soundable->Play();
				else
					soundable->Stop();

			}
		}
	}
}
//-----------------------------------------------------------------------------
void SoundPanel::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void SoundPanel::DoUpdate ()
{

}
//-----------------------------------------------------------------------------
void SoundPanel::DoExecute (PX2::Event *event)
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

		if (actor == mSoundActor)
			SetActor(0);
	}
}
//-----------------------------------------------------------------------------
void SoundPanel::DoLeave ()
{

}
//-----------------------------------------------------------------------------
void SoundPanel::SetActor (PX2::Actor *actor)
{
	mSoundActor = DynamicCast<SoundActor>(actor);

	if (mSoundActor)
	{
		PX2::Soundable *soundable = mSoundActor->GetSoundable();
		std::string name = soundable->GetName();
		std::string resPath = soundable->GetResourcePath();
		float minRange = soundable->GetMinDistance();
		float maxRange = soundable->GetMaxDistance();
		float volume = soundable->GetVolume();
		bool loop = soundable->IsLoop();
		bool is3d = !soundable->Is2d();

		mName->Clear();
		mName->WriteText(name.c_str());
		mFilename->Clear();
		mFilename->WriteText(resPath.c_str());

		wxString volumeStr = wxString::Format(wxT("%.2f"), volume);
		mVolume->Clear();
		mVolume->WriteText(volumeStr);
		mVolumeSlider->SetValue((int)(100*volume));

		wxString minStr = wxString::Format(wxT("%.2f"), minRange);
		mRangeIn->Clear();
		mRangeIn->WriteText(minStr);
		mRangeInSlider->SetValue((int)(100*minRange/10.0f));

		wxString maxStr = wxString::Format(wxT("%.2f"), maxRange);
		mRangeOut->Clear();
		mRangeOut->WriteText(maxStr);
		mRangeOutSlider->SetValue((int)(100*maxRange/10.0f));

		if (is3d)
		{
			mIs3d->Set3StateValue(wxCHK_CHECKED);
		}
		else
		{
			mIs3d->Set3StateValue(wxCHK_UNCHECKED);
		}
		if (loop)
		{
			mLoop->SetValue(true);
			mOnce->SetValue(false);
		}
		else
		{
			mLoop->SetValue(false);
			mOnce->SetValue(true);
		}
	}
}
//-----------------------------------------------------------------------------
void SoundPanel::OnSize (wxSizeEvent& e)
{
	wxPanel::OnSize(e);
}
//-----------------------------------------------------------------------------