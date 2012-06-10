/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ActorBaseProperty.cpp
*
*/

#include "PX2ObjectNameProperty.hpp"
using namespace PX2Editor;
using namespace PX2;

ObjectNameProperty::ObjectNameProperty (PropertyPage *parent, std::string name,
										PX2::Object *object)
				   :
Property(parent, name, Property::PT_STRING, (void *)&(object->GetName())),
mObject(object)
{
}
//-----------------------------------------------------------------------------
ObjectNameProperty::~ObjectNameProperty ()
{

}
//-----------------------------------------------------------------------------
void ObjectNameProperty::OnChange (wxPropertyGridEvent &event)
{
	if (!mObject)
		return;

	Property::OnChange(event);

	Event *ent = EditorEventSpace::CreateEvent(
		EditorEventSpace::ObjectNamePropertyChanged);
	ent->SetData<Object*>(mObject);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//-----------------------------------------------------------------------------
void ObjectNameProperty::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void ObjectNameProperty::DoUpdate ()
{

}
//-----------------------------------------------------------------------------
void ObjectNameProperty::DoExecute (PX2::Event *event)
{

}
//-----------------------------------------------------------------------------
void ObjectNameProperty::DoLeave ()
{

}
//-----------------------------------------------------------------------------