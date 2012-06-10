/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ModelActorPropertyGrid.cpp
*
*/

#include "PX2ModelActorPropertyGrid.hpp"
#include "PX2ObjectNameProperty.hpp"
#include "PX2ActorTransProperty.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(ModelActorPropertyGrid, ObjectPropertyGrid)
	BEGIN_EVENT_TABLE(ModelActorPropertyGrid, ObjectPropertyGrid)
	EVT_PG_CHANGED(PGT_ACTOR, ModelActorPropertyGrid::OnPropertyGridChange )
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
ModelActorPropertyGrid::ModelActorPropertyGrid ()
{
}
//-----------------------------------------------------------------------------
ModelActorPropertyGrid::ModelActorPropertyGrid (wxWindow *parent)
:
ObjectPropertyGrid (parent)
{
	mPropertyGridType = PGT_ACTOR;
}
//-----------------------------------------------------------------------------
ModelActorPropertyGrid::~ModelActorPropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void ModelActorPropertyGrid::OnSetObject(PX2::Object *object)
{
	if (object->IsExactly(Actor::TYPE))
	{
		RefreshOnModelActor();
	}
}
//-----------------------------------------------------------------------------
void ModelActorPropertyGrid::OnPropertyGridChange (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);
}
//-----------------------------------------------------------------------------
void ModelActorPropertyGrid::OnPropertyGridChanging (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void ModelActorPropertyGrid::OnPropertyGridSelect (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void ModelActorPropertyGrid::DoEnter ()
{
	ObjectPropertyGrid::DoEnter();
}
//-----------------------------------------------------------------------------
void ModelActorPropertyGrid::DoUpdate ()
{
	ObjectPropertyGrid::DoUpdate();
}
//-----------------------------------------------------------------------------
void ModelActorPropertyGrid::DoExecute (PX2::Event *event)
{
}
//-----------------------------------------------------------------------------
void ModelActorPropertyGrid::DoLeave ()
{
	ObjectPropertyGrid::DoLeave();
}
//-----------------------------------------------------------------------------
void ModelActorPropertyGrid::RefreshOnModelActor ()
{
	Clear();

	if (!mObject)
		return;

	AddPropertyPage("General");
	PropertyPage *page = GetPropertyPage("General");
	page->AddProperty("General", Property::PT_CATEGORY, 0);
	Property *prop = new0 ObjectNameProperty(page, "Name", mObject);

	PX2::Actor *actor = DynamicCast<Actor>(mObject);
	prop = new0 ActorTransProperty(page, "Name", actor);

	mPropGridManager->ExpandAll();
}
//-----------------------------------------------------------------------------