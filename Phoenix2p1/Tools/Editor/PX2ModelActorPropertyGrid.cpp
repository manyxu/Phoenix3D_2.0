/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ModelActorPropertyGrid.cpp
*
*/

#include "PX2ModelActorPropertyGrid.hpp"
#include "PX2ActorTransProperty.hpp"
#include "PX2ObjectNameProperty.hpp"
#include "PX2EditEventType.hpp"
#include "PX2Actor.hpp"
#include "PX2LanguageManager.hpp"
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
	if (object->IsDerived(Actor::TYPE))
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
void ModelActorPropertyGrid::DoExecute (PX2::Event *event)
{
	ObjectPropertyGrid::DoExecute(event);
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

	AddPropertyPage("General");
	PropertyPage *page = GetPropertyPage("General");
	page->AddProperty(PX2_LM.GetValue("General"), Property::PT_CATEGORY, 0);

	PX2::Actor *actor = DynamicCast<Actor>(mObject);
	mActorName = actor->GetName();
	mActorType = actor->GetRttiType().GetName();

	Property *nameProp = new0 ObjectNameProperty(page, PX2_LM.GetValue("Name"),
		mObject);
	Property *propType = new0 Property(page, PX2_LM.GetValue("Type"),
		Property::PT_STRING, &mActorType, false);
	Property *propTrans = new0 ActorTransProperty(page, PX2_LM.GetValue("Trans"), 
		actor);
	EventWorld::GetSingleton().ComeIn(propTrans);

	mPropGridManager->ExpandAll();
}
//-----------------------------------------------------------------------------