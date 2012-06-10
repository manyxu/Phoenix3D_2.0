/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ActorInspector.cpp
*
*/

#include "PX2ObjectPropertyGrid.hpp"
#include "PX2ActorTransProperty.hpp"
#include "PX2ObjectNameProperty.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(ObjectPropertyGrid, wxWindow)
BEGIN_EVENT_TABLE(ObjectPropertyGrid, wxWindow)
	EVT_SIZE(ObjectPropertyGrid::OnSize)
	EVT_MOVE(ObjectPropertyGrid::OnMove)
	EVT_PG_CHANGED(PGT_ACTOR, ObjectPropertyGrid::OnPropertyGridChange )
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
ObjectPropertyGrid::ObjectPropertyGrid ()
{
	mObjectVisible = true;
	mUseLOD = true;
}
//-----------------------------------------------------------------------------
ObjectPropertyGrid::ObjectPropertyGrid (wxWindow *parent)
:
PropertyGrid(parent, PGT_ACTOR)
{
	//AddPropertyPage("a");
	//GetPropertyPage("a")->AddProperty("a", Property::PT_CATEGORY, 0);
	//GetPropertyPage("a")->AddProperty("int_a", Property::PT_INT, 0);
	//GetPropertyPage("a")->AddProperty("float_a", Property::PT_FLOAT, 0);
	//GetPropertyPage("a")->AddProperty("bool_a", Property::PT_BOOL, 0);
	//GetPropertyPage("a")->AddProperty("boolcheck_a", Property::PT_BOOLCHECK, 0);
	//GetPropertyPage("a")->AddProperty("color_a", Property::PT_COLOR3FLOAT4, 0);
	//GetPropertyPage("a")->AddProperty("string_a", Property::PT_STRING, 0);

	//PropertyPage *page = GetPropertyPage("a");
	//Property *prop = new ActorTransProperty(page, "Translation", 0);

	//AddPropertyPage("b");
	//GetPropertyPage("b")->AddProperty("int_b", Property::PT_INT, 0);

	mObjectVisible = true;
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
void ObjectPropertyGrid::OnMove(wxMoveEvent& e)
{
}
//-----------------------------------------------------------------------------
void ObjectPropertyGrid::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void ObjectPropertyGrid::DoUpdate ()
{

}
//-----------------------------------------------------------------------------
void ObjectPropertyGrid::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::AddSelectActor))
	{
		int selectQuantity = ActorSelection::GetSingleton().GetActorQuantity();
		if (selectQuantity == 1)
		{
			Actor *actor = event->GetData<Actor*>();

			SetObject(actor);
		}
		else
		{
			SetObject(0);
		}
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::ClearSelectActor))
	{
		SetObject(0);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::SetPreViewObject) && 
		EditSystem::GetSingleton().GetEditMode() != EditSystem::EM_TERRAIN_TEXTURE)
	{
		Object *object = event->GetData<Object*>();
		SetObject(object);
	}

	if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::RemoveActor))
	{
		Actor *actor = event->GetData<Actor*>();

		if (actor == mObject)
			SetObject(0);
	}
}
//-----------------------------------------------------------------------------
void ObjectPropertyGrid::DoLeave ()
{

}
//-----------------------------------------------------------------------------
void ObjectPropertyGrid::Refresh ()
{
	Clear();

	if (!mObject)
		return;

	//AddPropertyPage("Actor");
	//PropertyPage *page = GetPropertyPage("Actor");

	//page->AddProperty("Base", Property::PT_CATEGORY, 0);
	//Property *prop = new0 ObjectNameProperty(page, "Name", mActor);
	//mObjectVisible = mActor->IsVisible();
	//page->AddProperty("Visible", Property::PT_BOOL, &mObjectVisible);

	//page->AddProperty("Translation", Property::PT_CATEGORY, 0);
	//prop = new0 ActorTransProperty(page, "Translation", mActor);

	//mPropGridManager->ExpandAll();
}
//-----------------------------------------------------------------------------