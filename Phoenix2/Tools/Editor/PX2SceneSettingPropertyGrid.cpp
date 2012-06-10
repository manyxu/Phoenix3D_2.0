/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SceneSettingPropertyGrid.cpp
*
*/

#include "PX2SceneSettingPropertyGrid.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(SceneSettingPropertyGrid, ObjectPropertyGrid)
	BEGIN_EVENT_TABLE(SceneSettingPropertyGrid, ObjectPropertyGrid)
	EVT_PG_CHANGED(PGT_ACTOR, SceneSettingPropertyGrid::OnPropertyGridChange )
END_EVENT_TABLE()
//----------------------------------------------------------------------------
SceneSettingPropertyGrid::SceneSettingPropertyGrid (wxWindow *parent)
:
ObjectPropertyGrid (parent)
{
	mDrawTerrain = true;
	mDrawWater = true;
	mDrawPhysics = EditSystem::GetSingleton().GetEditMap()->IsPhysicsDraw();

	PropertyPage *page = AddPropertyPage("SceneSetting");
	page->AddProperty("Scene", Property::PT_CATEGORY, 0);
	page->AddProperty("DrawTerrain", Property::PT_BOOLCHECK, &mDrawTerrain);
	page->AddProperty("DrawWater", Property::PT_BOOLCHECK, &mDrawWater);

	page->AddProperty("Physics", Property::PT_CATEGORY, 0);
	page->AddProperty("DrawPhysics", Property::PT_BOOLCHECK, &mDrawPhysics);

}
//----------------------------------------------------------------------------
SceneSettingPropertyGrid::~SceneSettingPropertyGrid ()
{

}
//----------------------------------------------------------------------------
void SceneSettingPropertyGrid::OnPropertyGridChange (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	EditSystem::GetSingleton().GetEditMap()->SetDrawPhysics(mDrawPhysics);
}
//----------------------------------------------------------------------------
void SceneSettingPropertyGrid::OnPropertyGridChanging (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//----------------------------------------------------------------------------
void SceneSettingPropertyGrid::OnPropertyGridSelect (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//----------------------------------------------------------------------------
void SceneSettingPropertyGrid::DoEnter ()
{

}
//----------------------------------------------------------------------------
void SceneSettingPropertyGrid::DoUpdate ()
{

}
//----------------------------------------------------------------------------
void SceneSettingPropertyGrid::DoExecute (PX2::Event *event)
{
	PX2_UNUSED(event);
}
//----------------------------------------------------------------------------
void SceneSettingPropertyGrid::DoLeave ()
{

}
//----------------------------------------------------------------------------
SceneSettingPropertyGrid::SceneSettingPropertyGrid ()
{

}
//----------------------------------------------------------------------------