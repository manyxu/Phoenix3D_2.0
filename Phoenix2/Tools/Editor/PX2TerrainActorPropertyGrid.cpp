/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainActorPropertyGrid.cpp
*
*/

#include "PX2TerrainActorPropertyGrid.hpp"
#include "PX2ObjectNameProperty.hpp"
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
}
//-----------------------------------------------------------------------------
TerrainActorPropertyGrid::~TerrainActorPropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::OnSetObject(PX2::Object *object)
{
	if (object->IsExactly(RawTerrainActor::TYPE))
	{
		RefreshOnRawTerrainActor();
	}
}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::OnPropertyGridChange (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	PX2::Object* object = mObject;
	PX2::RawTerrain *terrain = 0;
	RawTerrainActor *actor = DynamicCast<RawTerrainActor>(object);
	if (actor)
	{
		terrain = actor->GetTerrain();
	}

	PX2::RawTerrainPage *selectedPage = EditSystem::GetSingleton().GetTerrainEdit()
		->GetBrush()->GetSelectedPage();
	PX2_UNUSED(selectedPage);

	if (actor)
	{
		actor->SetDoPhysicsSimulateion(mDoPhysicsSimulateion);
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
void TerrainActorPropertyGrid::DoUpdate ()
{
	ObjectPropertyGrid::DoUpdate();
}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::DoExecute (PX2::Event *event)
{
	ObjectPropertyGrid::DoExecute(event);

	if (EditorEventSpace::IsEqual(event, EditorEventSpace::SelectTerrainPage))
	{
		RefreshOnRawTerrainActor();
	}
}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::DoLeave ()
{
	ObjectPropertyGrid::DoLeave();
}
//-----------------------------------------------------------------------------
void TerrainActorPropertyGrid::RefreshOnRawTerrainActor ()
{
	Clear();

	if (!mObject)
		return;

	AddPropertyPage("Terrain");
	PropertyPage *page = GetPropertyPage("Terrain");

	PX2::Object* object = mObject;
	RawTerrainActor *actor = DynamicCast<RawTerrainActor>(object);
	if (actor)
	{
		RawTerrain *terrain = actor->GetTerrain();

		page->AddProperty("TerrainInfo", Property::PT_CATEGORY, 0);
		Property *prop = new0 ObjectNameProperty(page, "Name", mObject);
		PX2_UNUSED(prop);
		mObjectVisible = actor->IsVisible();
		int rowQuantity = terrain->GetRowQuantity();
		int colQuantity = terrain->GetColQuantity();
		float spacing = terrain->GetSpacing();
		int sizeMius1 = terrain->GetSize()-1;
		float pageWidth = spacing*sizeMius1;
		float terWidth = pageWidth*rowQuantity;
		page->AddProperty("Visible", Property::PT_BOOL, &mObjectVisible);
		page->AddProperty("PageSize", Property::PT_INT, &sizeMius1);
		page->AddProperty("Spacing", Property::PT_FLOAT, &spacing);
		page->AddProperty("RowQuantity", Property::PT_INT, &rowQuantity);
		page->AddProperty("ColQuantity", Property::PT_INT, &colQuantity);
		page->AddProperty("PageWidth", Property::PT_FLOAT, &pageWidth);
		page->AddProperty("TerWidth", Property::PT_FLOAT, &terWidth);
		page->AddProperty("Physics", Property::PT_CATEGORY, 0);

		mDoPhysicsSimulateion = actor->IsDoPhysicsSimulateion();			
		page->AddProperty("DoPhysics", Property::PT_BOOLCHECK,
			&mDoPhysicsSimulateion);
	}

	mPropGridManager->ExpandAll();
}
//-----------------------------------------------------------------------------