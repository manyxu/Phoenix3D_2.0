/*
*
* ÎÄ¼þÃû³Æ	£º	PX2GeneralPropertyGrid.cpp
*
*/

#include "PX2GeneralPropertyGrid.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2Project.hpp"
#include "PX2EditEventType.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(GeneralPropertyGrid, ObjectPropertyGrid)
BEGIN_EVENT_TABLE(GeneralPropertyGrid, ObjectPropertyGrid)
EVT_PG_CHANGED(PGT_PROJSCENEUI, GeneralPropertyGrid::OnPropertyGridChange)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
GeneralPropertyGrid::GeneralPropertyGrid (wxWindow *parent)
:
ObjectPropertyGrid (parent),
mType(0)
{
	mPropertyGridType = PGT_PROJSCENEUI;

	mProjWidth = 0;
	mProjHeight = 0;
	mProjColor = Float3::BLACK;
	mIsShowProjectInfo = true;
	mIsShowSceneBound = true;
	mIsSceneWired = false;
	mIsShowUI = false;
	mIsUIWired = false;
	mIsShowGrid = false;
	mUICameraPercent = 1.0f;
	mIsShowUIRange = true;
}
//-----------------------------------------------------------------------------
GeneralPropertyGrid::~GeneralPropertyGrid ()
{
}
//-----------------------------------------------------------------------------
void GeneralPropertyGrid::SetType (int type)
{
	if (mType == type)
		return;

	mType = type;

	if (1 == mType)
	{
		RefreshOnProject();
	}
	else if (2 == mType)
	{
		RefreshOnScene();
	}
	else if (3 == mType)
	{
		RefreshOnUI();
	}
}
//-----------------------------------------------------------------------------
void GeneralPropertyGrid::OnPropertyGridChange (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	Project *proj = Project::GetSingletonPtr();

	if (PX2_LM.GetValue("BackColor") == event.GetPropertyName())
	{
		if (proj)
		{
			proj->SetColor(Float4(mProjColor[0], mProjColor[1], mProjColor[2],
				1.0f));
		}
	}
	else if (PX2_LM.GetValue("IsShowProjectInfo") == event.GetPropertyName())
	{
		if (proj)
		{
			proj->SetShowProjectInfo(mIsShowProjectInfo);
		}
	}
	else if (PX2_LM.GetValue("IsShowSceneBound") == event.GetPropertyName())
	{
		if (proj)
		{
			proj->SetShowSceneBound(mIsShowSceneBound);
		}
	}
	else if (PX2_LM.GetValue("IsSceneWired") == event.GetPropertyName())
	{
		if (proj)
		{
			proj->SetSceneWired(mIsSceneWired);
		}
	}
	else if (PX2_LM.GetValue("IsShowGrid") == event.GetPropertyName())
	{
		if (proj)
		{
			proj->SetShowGrid(mIsShowGrid);
		}
	}
	else if (PX2_LM.GetValue("IsShowUI") == event.GetPropertyName())
	{
		if (proj)
		{
			proj->SetShowUI(mIsShowUI);
		}
	}
	else if (PX2_LM.GetValue("IsUIWired") == event.GetPropertyName())
	{
		if (proj)
		{
			proj->SetUIWired(mIsUIWired);
		}
	}
	else if (PX2_LM.GetValue("UICameraPercent") == event.GetPropertyName())
	{
		if (proj && mUICameraPercent>=0.1f && mUICameraPercent<=10.0f)
		{
			proj->SetUICameraPercent(mUICameraPercent);

			Event *ent = EditorEventSpace::CreateEventX(
				EditorEventSpace::UICameraPercentChanged);
			EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
		}
	}
	else if (PX2_LM.GetValue("IsShowUIRange") == event.GetPropertyName())
	{
		if (proj)
		{
			proj->SetShowUIRange(mIsShowUIRange);
		}
	}
}
//-----------------------------------------------------------------------------
void GeneralPropertyGrid::OnPropertyGridChanging (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void GeneralPropertyGrid::OnPropertyGridSelect (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void GeneralPropertyGrid::DoEnter ()
{
}
//-----------------------------------------------------------------------------
void GeneralPropertyGrid::DoExecute (PX2::Event *event)
{
}
//-----------------------------------------------------------------------------
void GeneralPropertyGrid::DoLeave ()
{
}
//-----------------------------------------------------------------------------
GeneralPropertyGrid::GeneralPropertyGrid ()
{
}
//-----------------------------------------------------------------------------
void GeneralPropertyGrid::RefreshOnProject ()
{
	Clear();

	Project *proj = Project::GetSingletonPtr();
	if (!proj)
		return;

	mProjName = proj->GetName();
	mProjWidth = proj->GetWidth();
	mProjHeight = proj->GetHeight();
	Float4 color = proj->GetColor();
	mProjColor = Float3(color[0], color[1], color[2]);
	mIsShowProjectInfo = proj->IsShowProjectInfo();

	PropertyPage *page = AddPropertyPage("General");
	page->AddProperty(PX2_LM.GetValue("Project"), Property::PT_CATEGORY, 0);
	page->AddProperty(PX2_LM.GetValue("Name"), Property::PT_STRING, &mProjName,
		false);
	page->AddProperty(PX2_LM.GetValue("Width"), Property::PT_INT, &mProjWidth,
		false);
	page->AddProperty(PX2_LM.GetValue("Height"), Property::PT_INT,
		&mProjHeight, false);
	page->AddProperty(PX2_LM.GetValue("BackColor"), Property::PT_COLOR3FLOAT3,
		&mProjColor);
	page->AddProperty(PX2_LM.GetValue("Show"), Property::PT_CATEGORY, 0);
	page->AddProperty(PX2_LM.GetValue("IsShowProjectInfo"),
		Property::PT_BOOLCHECK, &mIsShowProjectInfo);
}
//-----------------------------------------------------------------------------
void GeneralPropertyGrid::RefreshOnScene ()
{
	Clear();

	Project *proj = Project::GetSingletonPtr();
	if (!proj)
		return;

	mIsShowSceneBound = proj->IsShowSceneBound();
	mIsSceneWired = proj->IsSceneWired();
	mIsShowGrid = proj->IsShowGrid();

	PropertyPage *page = AddPropertyPage("General");
	page->AddProperty(PX2_LM.GetValue("Show"), Property::PT_CATEGORY, 0);
	page->AddProperty(PX2_LM.GetValue("IsShowSceneBound"),
		Property::PT_BOOLCHECK, &mIsShowSceneBound);
	page->AddProperty(PX2_LM.GetValue("IsSceneWired"),
		Property::PT_BOOLCHECK, &mIsSceneWired);
	page->AddProperty(PX2_LM.GetValue("IsShowGrid"),
		Property::PT_BOOLCHECK, &mIsShowGrid);
}
//-----------------------------------------------------------------------------
void GeneralPropertyGrid::RefreshOnUI ()
{
	Clear();

	Project *proj = Project::GetSingletonPtr();
	if (!proj)
		return;

	mIsShowUI = proj->IsShowUI();
	mIsUIWired = proj->IsUIWired();
	mUICameraPercent = proj->GetUICameraPercent();
	mIsShowUIRange = proj->IsShowUIRange();

	PropertyPage *page = AddPropertyPage("General");
	page->AddProperty(PX2_LM.GetValue("Show"), Property::PT_CATEGORY, 0);
	page->AddProperty(PX2_LM.GetValue("IsShowUI"), Property::PT_BOOLCHECK, 
		&mIsShowUI);
	page->AddProperty(PX2_LM.GetValue("IsShowUIRange"), Property::PT_BOOLCHECK,
		&mIsShowUIRange);
	page->AddProperty(PX2_LM.GetValue("UICameraPercent"), Property::PT_FLOAT,
		&mUICameraPercent);
	page->AddProperty(PX2_LM.GetValue("IsUIWired"),
		Property::PT_BOOLCHECK, &mIsUIWired);
}
//-----------------------------------------------------------------------------