/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ModelPhysicsPropertyGrid.cpp
*
*/

#include "PX2ModelPhysicsPropertyGrid.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(ModelPhysicsPropertyGrid, ObjectPropertyGrid)
BEGIN_EVENT_TABLE(ModelPhysicsPropertyGrid, ObjectPropertyGrid)
	EVT_PG_CHANGED(PGT_ACTOR, ModelPhysicsPropertyGrid::OnPropertyGridChange )
END_EVENT_TABLE()

ModelPhysicsPropertyGrid::ModelPhysicsPropertyGrid (wxWindow *parent)
:
ObjectPropertyGrid (parent)
{
	mPropertyGridType = PGT_ACTOR;
	mDoPhysicsSimulateion = false;
	mPhysicsStatic = true;
}
//-----------------------------------------------------------------------------
ModelPhysicsPropertyGrid::~ModelPhysicsPropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void ModelPhysicsPropertyGrid::OnSetObject(PX2::Object *object)
{
	if (object->IsDerived(Actor::TYPE))
	{
		RefreshOnModelActor();
	}
}
//-----------------------------------------------------------------------------
void ModelPhysicsPropertyGrid::OnPropertyGridChange (wxPropertyGridEvent 
													 &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	Actor *actor = DynamicCast<Actor>(mObject);
	if (actor)
	{
		actor->SetDoPhysicsSimulateion(mDoPhysicsSimulateion);
		actor->SetPhysicsStatic(mPhysicsStatic);
	}
}
//-----------------------------------------------------------------------------
void ModelPhysicsPropertyGrid::OnPropertyGridChanging (wxPropertyGridEvent 
													   &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void ModelPhysicsPropertyGrid::OnPropertyGridSelect (wxPropertyGridEvent 
													 &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void ModelPhysicsPropertyGrid::DoEnter ()
{
	ObjectPropertyGrid::DoEnter();
}
//-----------------------------------------------------------------------------
void ModelPhysicsPropertyGrid::DoUpdate ()
{
	ObjectPropertyGrid::DoUpdate();
}
//-----------------------------------------------------------------------------
void ModelPhysicsPropertyGrid::DoExecute (PX2::Event *event)
{
}
//-----------------------------------------------------------------------------
void ModelPhysicsPropertyGrid::DoLeave ()
{
	ObjectPropertyGrid::DoLeave();
}
//-----------------------------------------------------------------------------
ModelPhysicsPropertyGrid::ModelPhysicsPropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void ModelPhysicsPropertyGrid::RefreshOnModelActor ()
{
	Clear();

	if (!mObject)
		return;

	Actor *actor = DynamicCast<Actor>(mObject);

	if (actor)
	{
		mDoPhysicsSimulateion = actor->IsDoPhysicsSimulateion();
		mPhysicsStatic = actor->IsPhysicsStatic();

		AddPropertyPage("Physics");
		PropertyPage *page = GetPropertyPage("Physics");
		page->AddProperty("Physics", Property::PT_CATEGORY, 0);
		page->AddProperty("DoPhysics", Property::PT_BOOLCHECK, 
			&mDoPhysicsSimulateion);
		page->AddProperty("PhysicsStatic", Property::PT_BOOLCHECK, 
			&mPhysicsStatic);

		mPropGridManager->ExpandAll();
	}
}
//-----------------------------------------------------------------------------