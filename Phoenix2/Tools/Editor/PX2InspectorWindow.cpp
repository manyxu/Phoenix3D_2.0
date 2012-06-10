/*
*
* ÎÄ¼þÃû³Æ	£º	PX2InspectorWindow.cpp
*
*/

#include "PX2InspectorWindow.hpp"
#include "PX2TerrainInspector.hpp"
#include "PX2ModelInspector.hpp"
#include "PX2TextureConvertPanel.hpp"
#include "PX2TextureInspector.hpp"
#include "PX2EffectInspector.hpp"
#include "PX2LightInspector.hpp"
#include "PX2EnvironmentPanel.hpp"
#include "PX2SoundPanel.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(InspectorWindow, wxWindow)
EVT_SIZE(InspectorWindow::OnSize)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
InspectorWindow::InspectorWindow (wxWindow *parent)
:
wxWindow(parent, wxID_ANY),
mCurrentWindow(0)
{
	mTerInspec = new TerrainInspector(this);
	mTerInspec->Show(false);
	EventWorld::GetSingleton().ComeIn(mTerInspec);
	mWindows[IWT_TERRAIN] = mTerInspec;

	mModelInspec = new ModelInspector(this);
	mModelInspec->Show(false);
	mWindows[IWT_MODELACTOR] = mModelInspec;
	PX2::EventWorld::GetSingleton().ComeIn(mModelInspec);

	mTexConInspec = new TextureConvertPane(this);
	mTexConInspec->Show(false);
	mWindows[IWT_TEXCONVERT] = mTexConInspec;

	mTextureInspec = new TexturePropertyGrid(this);
	mTextureInspec->Show(false);
	mWindows[IWT_TEXTURE] = mTextureInspec;
	PX2::EventWorld::GetSingleton().ComeIn(mTextureInspec);

	mEffectInspec = new EffectInspector(this);
	mEffectInspec->Show(false);
	mWindows[IWT_EFFECT] = mEffectInspec;
	PX2::EventWorld::GetSingleton().ComeIn(mEffectInspec);

	mLightInspec = new LightInspector(this);
	mLightInspec->Show(false);
	mWindows[IWT_LIGHT] = mLightInspec;
	PX2::EventWorld::GetSingleton().ComeIn(mLightInspec);

	mEnviInspec = new EnvironmentPanel(this);
	mEnviInspec->Show(false);
	mWindows[IWT_ENVIRONMENT] = mEnviInspec;
	PX2::EventWorld::GetSingleton().ComeIn(mEnviInspec);

	mSoundInspec = new SoundPanel(this);
	mSoundInspec->Show(false);
	mWindows[IWT_SOUND] = mSoundInspec;
	PX2::EventWorld::GetSingleton().ComeIn(mSoundInspec);
}
//----------------------------------------------------------------------------
InspectorWindow::~InspectorWindow ()
{

}
//----------------------------------------------------------------------------
void InspectorWindow::SetObject (PX2::Object *object)
{
	if (mObject != object)
	{
		mObject = object;

		OnSetObject(object);
	}
}
//----------------------------------------------------------------------------
void InspectorWindow::SwitchToWindow (InspecWinType type)
{
	HideAllWindow();

	mCurrentWindow = mWindows[type];
	mWindows[type]->Show(true);

	wxSize size = GetClientSize();
	mCurrentWindow->SetSize(size);
}
//----------------------------------------------------------------------------
void InspectorWindow::HideAllWindow ()
{
	std::map<InspecWinType, wxWindow*>::iterator it = mWindows.begin();
	for (; it!=mWindows.end(); it++)
	{
		it->second->Show(false);
	}
}
//----------------------------------------------------------------------------
void InspectorWindow::OnSize(wxSizeEvent& e)
{
	wxSize size = GetClientSize();

	if (mCurrentWindow)
		mCurrentWindow->SetSize(size);
}
//----------------------------------------------------------------------------
void InspectorWindow::DoEnter ()
{

}
//----------------------------------------------------------------------------
void InspectorWindow::DoUpdate ()
{

}
//----------------------------------------------------------------------------
void InspectorWindow::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::AddSelectActor))
	{
		int selectQuantity = ActorSelection::GetSingleton().GetActorQuantity();
		if (selectQuantity == 1)
		{
			Actor *actor = event->GetData<Actor*>();

			SetObject(actor);
		}
		else
		{
			SetObject(0);
		}
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::ClearSelectActor))
	{
		SetObject(0);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::SetEditMode))
	{
		PX2Editor::EditSystem::EditMode mode = 
			event->GetData<PX2Editor::EditSystem::EditMode>();
		if (mode == PX2Editor::EditSystem::EM_TEXTURECONVERT)
		{
			SetObject(0);
			SwitchToWindow(IWT_TEXCONVERT);
		}
		else if (mode == PX2Editor::EditSystem::EM_EFFECT)
		{
			SetObject(0);
			SwitchToWindow(IWT_EFFECT);
		}
	}
	//else if (EditorEventSpace::IsEqual(event, EditorEventSpace::SetPreViewObject) &&
	//	EditSystem::EM_TERRAIN_HEIGHT != EditSystem::GetSingleton().GetEditMode() &&
	//	EditSystem::EM_TERRAIN_TEXTURE != EditSystem::GetSingleton().GetEditMode())
	//{
	//	PX2::Object *object = event->GetData<PX2::Object*>();
	//	SetObject(object);
	//}

	if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::RemoveActor))
	{
		Actor *actor = event->GetData<Actor*>();

		if (actor == mObject)
			OnSetObject(0);
	}
}
//----------------------------------------------------------------------------
void InspectorWindow::DoLeave ()
{

}
//----------------------------------------------------------------------------
void InspectorWindow::OnSetObject (PX2::Object *object)
{
	if (!object)
	{
		HideAllWindow();
		return;
	}

	if (object->IsExactly(RawTerrainActor::TYPE))
	{
		SwitchToWindow(IWT_TERRAIN);
	}
	else if (object->IsDerived(Texture::TYPE))
	{
		SwitchToWindow(IWT_TEXTURE);
	}
	else if (object->IsDerived(LightActor::TYPE))
	{
		SwitchToWindow(IWT_LIGHT);
	}
	else if (object->IsDerived(AmbientRegionActor::TYPE))
	{
		SwitchToWindow(IWT_ENVIRONMENT);
	}
	else if (object->IsDerived(SoundActor::TYPE))
	{
		SwitchToWindow(IWT_SOUND);
	}
	else
	{
		SwitchToWindow(IWT_MODELACTOR);
	}

	if (mCurrentWindow)
	{
		wxSize size = GetClientSize();

		mCurrentWindow->SetSize(size);	
	}
}
//----------------------------------------------------------------------------