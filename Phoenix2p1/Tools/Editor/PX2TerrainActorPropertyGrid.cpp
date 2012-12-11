/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainActorPropertyGrid.cpp
*
*/

#include "PX2TerrainActorPropertyGrid.hpp"
#include "PX2ViewCtrlInstMan.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(TerrainActorPropertyGrid, ObjectPropertyGrid)
BEGIN_EVENT_TABLE(TerrainActorPropertyGrid, ObjectPropertyGrid)
EVT_PG_CHANGED(PGT_TERRAINACTOR, TerrainActorPropertyGrid::OnPropertyGridChange )
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
TerrainActorPropertyGrid::TerrainActorPropertyGrid ()
{
}
//-----------------------------------------------------------------------------
TerrainActorPropertyGrid::TerrainActorPropertyGrid (wxWindow *parent)
	:
ObjectPropertyGrid (parent)
{
	mPropertyGridType = PGT_TERRAINACTOR;
	mEnableTerrainEdit = false;
	mShowPageGridLine = false;
}
//-----------------------------------------------------------------------------
TerrainActorPropertyGrid::~TerrainActorPropertyGrid ()
{
}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::EnableTerrainEdit (bool able)
{
	mEnableTerrainEdit = able;
	
	PropertyPage *page = GetPropertyPage("General");
	if (!page)
		return;

	Property *prop = page->GetProperty(PX2_LM.GetValue("TerrainEdit"));
	if (!prop)
		return;

	prop->SetValue(able);
}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::OnSetObject(PX2::Object *object)
{
	if (object->IsExactly(TerrainActor::TYPE))
	{
		RefreshOnActor();
	}
}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::OnPropertyGridChange (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	if (event.GetPropertyName() == PX2_LM.GetValue("TerrainEdit"))
	{
		bool enableEdit = event.GetValue();
		if (enableEdit)
		{
			EditSystem::GetSingleton().SetEditMode(EditSystem::EM_TERRAIN);
			ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
				->SetInteractionMode(IM_TEREDIT);
		}
		else
		{
			EditSystem::GetSingleton().SetEditMode(EditSystem::EM_SELECT);
			ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
				->SetInteractionMode(IM_GENERAL);
		}
	}
	else if (event.GetPropertyName() == PX2_LM.GetValue("ShowPageLine"))
	{
		bool show = event.GetValue();
		EditSystem::GetSingleton().GetTerrainEdit()->ShowPageLine(show);
	}
}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::OnPropertyGridChanging (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::OnPropertyGridSelect (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::DoEnter ()
{
	ObjectPropertyGrid::DoEnter();
}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::DoExecute (PX2::Event *event)
{
	ObjectPropertyGrid::DoExecute(event);
}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::DoLeave ()
{
	ObjectPropertyGrid::DoLeave();
}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::RefreshOnActor ()
{
	Clear();

	AddPropertyPage("General");
	PropertyPage *page = GetPropertyPage("General");
	page->AddProperty(PX2_LM.GetValue("General"), Property::PT_CATEGORY, 0);

	PX2::Actor *actor = DynamicCast<Actor>(mObject);
	mActorName = actor->GetName();
	mActorType = actor->GetRttiType().GetName();
	Property *propName = new0 Property(page, PX2_LM.GetValue("Name"),
		Property::PT_STRING, &mActorName);
	Property *propType = new0 Property(page, PX2_LM.GetValue("Type"),
		Property::PT_STRING, &mActorType, false);

	page->AddProperty(PX2_LM.GetValue("Edit"), Property::PT_CATEGORY, 0);
	page->AddProperty(PX2_LM.GetValue("TerrainEdit"), Property::PT_BOOLCHECK,
		&mEnableTerrainEdit);
	Property *propShowPageLine = new0 Property(page, 
		PX2_LM.GetValue("ShowPageLine"), Property::PT_BOOLCHECK, 
		&mShowPageGridLine);

	mPropGridManager->ExpandAll();
}
//-----------------------------------------------------------------------------