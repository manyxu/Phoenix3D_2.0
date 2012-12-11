/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ActorInspector.cpp
*
*/

#include "PX2ObjectPropertyGrid.hpp"
#include "PX2ActorTransProperty.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(ObjectPropertyGrid, wxWindow)
BEGIN_EVENT_TABLE(ObjectPropertyGrid, wxWindow)
EVT_SIZE(ObjectPropertyGrid::OnSize)
EVT_MOVE(ObjectPropertyGrid::OnMove)
EVT_PG_CHANGED(PGT_ACTOR, ObjectPropertyGrid::OnPropertyGridChange)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
ObjectPropertyGrid::ObjectPropertyGrid ()
:
mObjectVisible(true)
{
}
//-----------------------------------------------------------------------------
ObjectPropertyGrid::ObjectPropertyGrid (wxWindow *parent)
	:
PropertyGrid(parent, PGT_ACTOR),
	mObjectVisible(true)
{
}
//-----------------------------------------------------------------------------
ObjectPropertyGrid::~ObjectPropertyGrid ()
{
}
//-----------------------------------------------------------------------------
void ObjectPropertyGrid::SetObject (PX2::Object *actor)
{
	mObject = actor;

	if (!mObject)
	{
		Clear();
		return;
	}

	OnSetObject(actor);
}
//-----------------------------------------------------------------------------
void ObjectPropertyGrid::OnSetObject (PX2::Object *actor)
{
	Refresh();
}
//-----------------------------------------------------------------------------
PX2::Object *ObjectPropertyGrid::GetObject ()
{
	return mObject;
}
//-----------------------------------------------------------------------------
void ObjectPropertyGrid::OnPropertyGridChange (wxPropertyGridEvent &event)
{
	PropertyGrid::OnPropertyGridChange(event);

	Actor *actor = DynamicCast<Actor>(mObject);
	if (actor)
	{
		actor->SetVisible(mObjectVisible);
	}
}
//-----------------------------------------------------------------------------
void ObjectPropertyGrid::OnPropertyGridChanging (wxPropertyGridEvent &event)
{
}
//-----------------------------------------------------------------------------
void ObjectPropertyGrid::OnPropertyGridSelect (wxPropertyGridEvent &event)
{
}
//-----------------------------------------------------------------------------
void ObjectPropertyGrid::OnSize(wxSizeEvent &e)
{
	PropertyGrid::OnSize(e);
}
//-----------------------------------------------------------------------------