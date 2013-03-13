/*
*
* ÎÄ¼þÃû³Æ	£º	PX2InspectorWindow.cpp
*
*/

#include "PX2InspectorWindow.hpp"
#include "PX2ModelActorInspector.hpp"
#include "PX2TerrainActorInspector.hpp"
#include "PX2EnvPanel.hpp"
#include "PX2EffectActorInspector.hpp"
#include "PX2SkyActorInspector.hpp"
#include "PX2UIInspector.hpp"
#include "PX2GeneralInspector.hpp"
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
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::AddSelectObject))
	{
		int selectNum = EditSystem::GetSingleton().GetSelection()
			->GetNumObjects();
		if (selectNum == 1)
		{
			Object *obj = event->GetData<Object*>();
			SetObject(obj);
		}
		else
		{
			SetObject(0);
		}
	}
	else if (EditorEventSpace::IsEqual(event, 
		EditorEventSpace::ClearSelectObject))
	{
		SetObject(0);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::SelectPSU))
	{
		SetObject(0);
		int type = event->GetData<int>();
		if (1 == type)
		{
			ChangeToWindow("P", 1);
		}
		else if (2 == type)
		{
			ChangeToWindow("S", 2);
		}
		else if (3 == type)
		{
			ChangeToWindow("U", 3);
		}
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
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::CurveChangedByEditor))
	{
		void *data = event->GetData<void*>();
		EffectInspector *insp = wxDynamicCast(mCurWindow, EffectInspector);
		if (insp)
		{
			insp->TryRefreshModulePoints(data);
		}
	}
}
//----------------------------------------------------------------------------
void InspectorWindow::DoLeave ()
{
}
//----------------------------------------------------------------------------
void InspectorWindow::ChangeToWindow (std::string str, int userData)
{
	if (mCurWindow)
	{
		delete mCurWindow;
		mCurWindow = 0;
	}

	mCurWinStr = str;
	
	if ("ModelActor" == str)
	{
		ModelActorInspector *inspec = new ModelActorInspector(this);
		inspec->SetActor(DynamicCast<Actor>(mObject));
		mCurWindow = inspec;
	}
	else if ("TerrainActor" == str)
	{
		TerrainActorInspector *inspec = new TerrainActorInspector(this);
		inspec->SetActor(DynamicCast<TerrainActor>(mObject));
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
	else if ("AmbientRegionActor" == str)
	{
		EvnPanel *inspec = new EvnPanel(this);
		inspec->SetActor(DynamicCast<AmbientRegionActor>(mObject));
		mCurWindow = inspec;
	}
	else if ("EffectActor" == str)
	{
		EffectInspector *inspec = new EffectInspector(this);
		inspec->SetActor(DynamicCast<EffectActor>(mObject));
		mCurWindow = inspec;
	}
	else if ("UI" == str)
	{
		UIInspacetor *inspec = new UIInspacetor(this);
		inspec->SetUIObject(DynamicCast<Movable>(mObject));
		mCurWindow = inspec;
	}
	else if ("P"==str || "S"==str || "U"==str)
	{
		GeneralInspector *inspec = new GeneralInspector(this);
		inspec->SetType(userData);
		mCurWindow = inspec;
	}
	else if ("SkyActor" == str)
	{
		SkyActorInspector *inspec = new SkyActorInspector(this);
		inspec->SetActor(DynamicCast<SkyActor>(mObject));
		mCurWindow = inspec;
	}

	if (mCurWindow)
	{
		wxSize size = GetClientSize();
		mCurWindow->SetSize(size);	
	}
}
//----------------------------------------------------------------------------
void InspectorWindow::SetObject (PX2::Object *obj)
{
	if (mObject == obj && obj)
		return;

	mObject = obj;

	if (0 == mObject)
	{
		ChangeToWindow("");
	}
	else if (mObject->IsExactly(Actor::TYPE))
	{
		ChangeToWindow("ModelActor");
	}
	else if (mObject->IsExactly(TerrainActor::TYPE))
	{
		ChangeToWindow("TerrainActor");
	}
	else if (mObject->IsExactly(AmbientRegionActor::TYPE))
	{
		ChangeToWindow("AmbientRegionActor");
	}
	else if (mObject->IsExactly(EffectActor::TYPE))
	{
		ChangeToWindow("EffectActor");
	}
	else if (mObject->IsExactly(SkyActor::TYPE))
	{
		ChangeToWindow("SkyActor");
	}
	else if (mObject->IsDerived(UIPicBox::TYPE))
	{
		ChangeToWindow("UI");
	}
	else if (mObject->IsDerived(UIFrame::TYPE))
	{
		ChangeToWindow("UI");
	}
	else if (mObject->IsDerived(UIStaticText::TYPE))
	{
		ChangeToWindow("UI");
	}
}
//----------------------------------------------------------------------------