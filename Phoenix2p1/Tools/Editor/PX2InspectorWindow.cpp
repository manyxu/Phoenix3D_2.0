/*
*
* ÎÄ¼þÃû³Æ	£º	PX2InspectorWindow.cpp
*
*/

#include "PX2InspectorWindow.hpp"
#include "PX2ModelActorInspector.hpp"
#include "PX2TerrainActorInspector.hpp"
#include "PX2EditSystem.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(InspectorWindow, wxWindow)
	EVT_SIZE(InspectorWindow::OnSize)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
InspectorWindow::InspectorWindow (wxWindow *parent)
	:
wxWindow(parent, wxID_ANY),
	mCurWindow(0)
{
}
//----------------------------------------------------------------------------
InspectorWindow::~InspectorWindow ()
{
	if (mCurWindow)
	{
		delete mCurWindow;
		mCurWindow = 0;
	}
}
//----------------------------------------------------------------------------
void InspectorWindow::OnSize(wxSizeEvent& e)
{
	wxSize size = GetClientSize();

	if (mCurWindow)
	{
		mCurWindow->SetSize(size);
	}
}
//----------------------------------------------------------------------------
void InspectorWindow::DoEnter ()
{
}
//----------------------------------------------------------------------------
void InspectorWindow::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::AddSelectActor))
	{
		int selectNum = EditSystem::GetSingleton().GetSelection()
			->GetActorQuantity();
		if (selectNum == 1)
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
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::SetEditMode))
	{
		EditSystem::EditMode mode = event->GetData<EditSystem::EditMode>();
		if (mode == EditSystem::EM_TERRAIN)
		{
			TerrainActorInspector *insp = wxDynamicCast(mCurWindow, 
				TerrainActorInspector);
			if (insp)
			{
				insp->EnableEdit(true);
			}
		}
		else
		{
			TerrainActorInspector *insp = wxDynamicCast(mCurWindow, 
				TerrainActorInspector);
			if (insp && mCurWinStr=="TerrainActor")
			{
				insp->EnableEdit(false);
			}
		}
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::SelectTerrainPage))
	{
		TerrainActorInspector *insp = wxDynamicCast(mCurWindow, 
			TerrainActorInspector);
		if (insp)
		{
			insp->RefreshSelectTerrainPage ();
		}
	}
}
//----------------------------------------------------------------------------
void InspectorWindow::DoLeave ()
{
}
//----------------------------------------------------------------------------
void InspectorWindow::ChangeToWindow (std::string str)
{
	if (mCurWinStr == str)
		return;

	if (mCurWindow)
	{
		delete mCurWindow;
		mCurWindow = 0;
	}

	mCurWinStr = str;
	
	if ("ModelActor" == str)
	{
		ModelActorInspector *inspec = new ModelActorInspector(this);
		inspec->SetActor(mActor);
		mCurWindow = inspec;
	}
	else if ("TerrainActor" == str)
	{
		TerrainActorInspector *inspec = new TerrainActorInspector(this);
		inspec->SetActor(DynamicCast<TerrainActor>(mActor));
		mCurWindow = inspec;

		EditSystem::EditMode mode = EditSystem::GetSingleton().GetEditMode();
		if (mode == EditSystem::EM_TERRAIN)
		{
			inspec->EnableEdit(true);
		}
		else
		{
			inspec->EnableEdit(false);
		}
	}

	if (mCurWindow)
	{
		wxSize size = GetClientSize();
		mCurWindow->SetSize(size);	
	}
}
//----------------------------------------------------------------------------
void InspectorWindow::SetActor (PX2::Actor *actor)
{
	mActor = actor;

	if (0 == mActor)
	{
		ChangeToWindow("");
	}
	else if (mActor->IsExactly(Actor::TYPE))
	{
		ChangeToWindow("ModelActor");
	}
	else if (mActor->IsExactly(TerrainActor::TYPE))
	{
		ChangeToWindow("TerrainActor");
	}
}
//----------------------------------------------------------------------------