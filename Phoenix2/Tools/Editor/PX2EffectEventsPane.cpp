/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectEventsPane.cpp
*
*/

#include "PX2EffectEventsPane.hpp"
#include "PX2EffectEventPropertyGrid.hpp"

#pragma warning(disable : 4312)

using namespace PX2Editor;
using namespace PX2;

#define ID_EE_EMITRATE wxID_HIGHEST + 1000
#define ID_EE_PARTICLESPEED wxID_HIGHEST + 1001
#define ID_EE_PARTICLESPEEDDIR wxID_HIGHEST + 1002
#define ID_EE_PARTICLESIZE wxID_HIGHEST + 1003
#define ID_EE_PARTICLECOLOR wxID_HIGHEST + 1004
#define ID_EE_PARTICLEALPHA wxID_HIGHEST + 1005

#define  ID_EFFECTLIST wxID_HIGHEST + 1100

IMPLEMENT_DYNAMIC_CLASS(PX2Editor::EffectEventsPanel, wxPanel)
BEGIN_EVENT_TABLE(EffectEventsPanel, wxPanel)
	EVT_SIZE(EffectEventsPanel::OnSize)
	EVT_BUTTON(wxID_ANY, EffectEventsPanel::OnButton)
	EVT_RIGHT_DOWN(EffectEventsPanel::OnRightDown)
	EVT_MENU(ID_EE_EMITRATE, EffectEventsPanel::OnEE_EmitRate)
	EVT_MENU(ID_EE_PARTICLESPEED, EffectEventsPanel::OnEE_ParticleSpeed)
	EVT_MENU(ID_EE_PARTICLESPEEDDIR, EffectEventsPanel::OnEE_ParticleSpeedDir)
	EVT_MENU(ID_EE_PARTICLESIZE, EffectEventsPanel::OnEE_ParticleSize)
	EVT_MENU(ID_EE_PARTICLECOLOR, EffectEventsPanel::OnEE_ParticleColor)
	EVT_MENU(ID_EE_PARTICLEALPHA, EffectEventsPanel::OnEE_ParticleAlpha)
	EVT_LIST_ITEM_SELECTED(ID_EFFECTLIST, EffectEventsPanel::OnListCtrlItemSelected)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
EffectEventsPanel::EffectEventsPanel (wxWindow *parent)
:
wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize( 243,580 ))
{
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxHORIZONTAL );

	mNewButton = new wxButton( this, wxID_ANY, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer30->Add( mNewButton, 0, wxALL, 5 );

	mDeleteButton = new wxButton( this, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer30->Add( mDeleteButton, 0, wxALL, 5 );

	bSizer24->Add( bSizer30, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );

	mListCtrl = new wxListCtrl( this, ID_EFFECTLIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	bSizer29->Add( mListCtrl, 1, wxALL|wxEXPAND, 5 );

	bSizer24->Add( bSizer29, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxVERTICAL );
	bSizer33->SetMinSize( wxSize( -1,200 ) ); 

	// propertygrid
	mPropGrid = new EffectEventPropertyGrid(this);
	PX2::EventWorld::GetSingleton().ComeIn(mPropGrid);
	bSizer33->Add( mPropGrid, 1, wxALL|wxEXPAND, 5 );

	bSizer24->Add( bSizer33, 1, wxEXPAND, 5 );

	this->SetSizer( bSizer24 );

	// list
	wxListItem itemCol;
	itemCol.SetText(_T("Time"));
	mListCtrl->InsertColumn(0, itemCol);
	mListCtrl->SetColumnWidth(0, 50);

	itemCol.SetText(_T("Type"));
	mListCtrl->InsertColumn(1, itemCol);
	mListCtrl->SetColumnWidth(1, 100);

	itemCol.SetText(_T("Value"));
	mListCtrl->InsertColumn(2, itemCol);

	this->Layout();

	// menu
	mEventCreateMenu.Append(ID_EE_EMITRATE,_("EmitRate"));
	mEventCreateMenu.AppendSeparator();
	mEventCreateMenu.Append(ID_EE_PARTICLESPEED,_("Speed"));
	mEventCreateMenu.Append(ID_EE_PARTICLESPEEDDIR,_("SpeedDir"));
	mEventCreateMenu.Append(ID_EE_PARTICLESIZE,_("Size"));
	mEventCreateMenu.Append(ID_EE_PARTICLECOLOR,_("Color"));
	mEventCreateMenu.Append(ID_EE_PARTICLEALPHA,_("Alpha"));

}
//-----------------------------------------------------------------------------
EffectEventsPanel::~EffectEventsPanel ()
{

}
//-----------------------------------------------------------------------------
EffectEventsPanel::EffectEventsPanel ()
{

}
//-----------------------------------------------------------------------------
void EffectEventsPanel::UpdateEventsOnEffect (PX2::Movable *obj)
{
	mListCtrl->DeleteAllItems();

	PX2::ParticleEmitter *emitter = DynamicCast<PX2::ParticleEmitter>(obj);
	if (emitter)
	{
		int numEvents = emitter->GetParticleEmitterControl()->GetNumEvents();
		for (int i=0; i<numEvents; i++)
		{
			EffectEvent *ent = emitter->GetParticleEmitterControl()
				->GetEffectEvent(i);
			float activeTime = ent->GetActivateTime();

			mListCtrl->InsertItem(i, wxString().Format("%.2f", activeTime));
			mListCtrl->SetItem(i, 1, wxString(ent->GetRttiType().GetName()));
			mListCtrl->SetItemPtrData(i, (wxUIntPtr)ent);
		}
	}
}
//-----------------------------------------------------------------------------
void EffectEventsPanel::OnRightDown (wxMouseEvent& e)
{
}
//-----------------------------------------------------------------------------
void EffectEventsPanel::OnButton (wxCommandEvent& event)
{
	if (event.GetEventObject() == mNewButton)
	{
		wxPoint popupPos = wxGetMousePosition();
		popupPos = ScreenToClient(popupPos);
		this->PopupMenu(&mEventCreateMenu, popupPos.x, popupPos.y);
	}
	else if (event.GetEventObject() == mDeleteButton)
	{

	}
}
//-----------------------------------------------------------------------------
void EffectEventsPanel::OnSize(wxSizeEvent& e)
{
	wxPanel::OnSize(e);
}
//----------------------------------------------------------------------------
void EffectEventsPanel::OnListCtrlItemSelected(wxListEvent& event)
{
	int sel = event.m_itemIndex;
	EffectEvent *effectEvent = (EffectEvent*)(mListCtrl->GetItemData(sel));
	PX2_UNUSED(effectEvent);

	Event *ent = 0;
	ent = EditorEventSpace::CreateEvent
		(EditorEventSpace::SelectEffectEvent);
	ent->SetData<EffectEvent*>(effectEvent);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//-----------------------------------------------------------------------------
void EffectEventsPanel::OnEE_EmitRate (wxCommandEvent &e)
{

}
//-----------------------------------------------------------------------------
void EffectEventsPanel::OnEE_ParticleSize (wxCommandEvent &e)
{
	PX2::Movable *obj = EditSystem::GetSingleton().GetSingleton()
		.GetEffectEdit()->GetEditEffect();
	PX2::ParticleEmitter *emitter = DynamicCast<PX2::ParticleEmitter>(obj);
	if (emitter)
	{
		float insertingTime = EditSystem::GetSingleton().GetEffectEdit()
			->GetInsertingTime();

		if (insertingTime >= 0.0f)
		{
			ParticleEvent_Size *ent = new0 ParticleEvent_Size();
			ent->SetTimeRange(TRange<float>(insertingTime, insertingTime));

			emitter->GetParticleEmitterControl()->AttachEffectEvent(ent);
			emitter->GetParticleEmitterControl()->ConfigeAllEvents();

			Event *event = 0;
			event = EditorEventSpace::CreateEvent
				(EditorEventSpace::AddEffectEvent);
			event->SetData<Object*>(emitter);
			EventWorld::GetSingleton().BroadcastingLocalEvent(event);
		}
	}

	UpdateEventsOnEffect(obj);
}
//-----------------------------------------------------------------------------
void EffectEventsPanel::OnEE_ParticleColor (wxCommandEvent &e)
{
	PX2::Movable *obj = EditSystem::GetSingleton().GetSingleton()
		.GetEffectEdit()->GetEditEffect();
	PX2::ParticleEmitter *emitter = DynamicCast<PX2::ParticleEmitter>(obj);
	if (emitter)
	{
		float insertingTime = EditSystem::GetSingleton().GetEffectEdit()
			->GetInsertingTime();

		if (insertingTime >= 0.0f)
		{
			ParticleEvent_Color *ent = new0 ParticleEvent_Color();
			ent->SetTimeRange(TRange<float>(insertingTime, insertingTime));

			emitter->GetParticleEmitterControl()->AttachEffectEvent(ent);
			emitter->GetParticleEmitterControl()->ConfigeAllEvents();

			Event *event = 0;
			event = EditorEventSpace::CreateEvent
				(EditorEventSpace::AddEffectEvent);
			event->SetData<Object*>(emitter);
			EventWorld::GetSingleton().BroadcastingLocalEvent(event);
		}
	}

	UpdateEventsOnEffect(obj);
}
//-----------------------------------------------------------------------------
void EffectEventsPanel::OnEE_ParticleAlpha (wxCommandEvent &e)
{
	PX2::Movable *obj = EditSystem::GetSingleton().GetSingleton()
		.GetEffectEdit()->GetEditEffect();
	PX2::ParticleEmitter *emitter = DynamicCast<PX2::ParticleEmitter>(obj);
	if (emitter)
	{
		float insertingTime = EditSystem::GetSingleton().GetEffectEdit()
			->GetInsertingTime();

		if (insertingTime >= 0.0f)
		{
			ParticleEvent_Alpha *ent = new0 ParticleEvent_Alpha();
			ent->SetTimeRange(TRange<float>(insertingTime, insertingTime));

			emitter->GetParticleEmitterControl()->AttachEffectEvent(ent);
			emitter->GetParticleEmitterControl()->ConfigeAllEvents();

			Event *event = 0;
			event = EditorEventSpace::CreateEvent
				(EditorEventSpace::AddEffectEvent);
			event->SetData<Object*>(emitter);
			EventWorld::GetSingleton().BroadcastingLocalEvent(event);
		}
	}

	UpdateEventsOnEffect(obj);
}
//-----------------------------------------------------------------------------
void EffectEventsPanel::OnEE_ParticleSpeed (wxCommandEvent &e)
{
	PX2::Movable *obj = EditSystem::GetSingleton().GetSingleton()
		.GetEffectEdit()->GetEditEffect();
	PX2::ParticleEmitter *emitter = DynamicCast<PX2::ParticleEmitter>(obj);
	if (emitter)
	{
		float insertingTime = EditSystem::GetSingleton().GetEffectEdit()
			->GetInsertingTime();

		if (insertingTime >= 0.0f)
		{
			ParticleEvent_Speed *ent = new0 ParticleEvent_Speed();
			ent->SetTimeRange(TRange<float>(insertingTime, insertingTime));

			emitter->GetParticleEmitterControl()->AttachEffectEvent(ent);
			emitter->GetParticleEmitterControl()->ConfigeAllEvents();

			Event *event = 0;
			event = EditorEventSpace::CreateEvent
				(EditorEventSpace::AddEffectEvent);
			event->SetData<Object*>(emitter);
			EventWorld::GetSingleton().BroadcastingLocalEvent(event);
		}
	}

	UpdateEventsOnEffect(obj);
}
//-----------------------------------------------------------------------------
void EffectEventsPanel::OnEE_ParticleSpeedDir (wxCommandEvent &e)
{
	PX2::Movable *obj = EditSystem::GetSingleton().GetSingleton()
		.GetEffectEdit()->GetEditEffect();
	PX2::ParticleEmitter *emitter = DynamicCast<PX2::ParticleEmitter>(obj);
	if (emitter)
	{
		float insertingTime = EditSystem::GetSingleton().GetEffectEdit()
			->GetInsertingTime();

		if (insertingTime >= 0.0f)
		{
			ParticleEvent_SpeedDir *ent = new0 ParticleEvent_SpeedDir();
			ent->SetTimeRange(TRange<float>(insertingTime, insertingTime));

			emitter->GetParticleEmitterControl()->AttachEffectEvent(ent);
			emitter->GetParticleEmitterControl()->ConfigeAllEvents();

			Event *event = 0;
			event = EditorEventSpace::CreateEvent
				(EditorEventSpace::AddEffectEvent);
			event->SetData<Object*>(emitter);
			EventWorld::GetSingleton().BroadcastingLocalEvent(event);
		}
	}

	UpdateEventsOnEffect(obj);
}
//-----------------------------------------------------------------------------