/*
*
* 文件名称	：	PX2Soundable.cpp
*
*/

#include "PX2Netable.hpp"
#include "PX2EventWorld.hpp"
using namespace PX2;

NetableEventHandler::NetableEventHandler ()
{
}
//----------------------------------------------------------------------------
NetableEventHandler::NetableEventHandler (Netable *netable)
{
	mNetable = netable;
}
//----------------------------------------------------------------------------
NetableEventHandler::~NetableEventHandler ()
{
}
//----------------------------------------------------------------------------
void NetableEventHandler::DoEnter ()
{
	mNetable->DoEnter();
}
//----------------------------------------------------------------------------
void NetableEventHandler::DoUpdate ()
{
	mNetable->DoUpdate();
}
//----------------------------------------------------------------------------
void NetableEventHandler::DoExecute (Event *event)
{
	mNetable->DoExecute(event);
}
//----------------------------------------------------------------------------
void NetableEventHandler::DoLeave ()
{
	mNetable->DoLeave();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Netable
//----------------------------------------------------------------------------

PX2_IMPLEMENT_RTTI(PX2, Object, Netable);
PX2_IMPLEMENT_STREAM(Netable);
PX2_IMPLEMENT_ABSTRACT_FACTORY(Netable);

//----------------------------------------------------------------------------
Netable::Netable()
{
	mNetableEventHandler = new0 NetableEventHandler(this);
}
//----------------------------------------------------------------------------
Netable::~Netable ()
{
	assertion(!IsInEventWorld(), "Netable must out of EventWorld.");

	mNetableEventHandler = 0;
}
//----------------------------------------------------------------------------
void Netable::ComeInToEventWorld ()
{
	if (EventWorld::GetSingletonPtr())
		EventWorld::GetSingletonPtr()->ComeIn(mNetableEventHandler);
}
//----------------------------------------------------------------------------
void Netable::GoOutFromEventWorld ()
{
	if (EventWorld::GetSingletonPtr())
		EventWorld::GetSingletonPtr()->GoOut(mNetableEventHandler);
}
//----------------------------------------------------------------------------
bool Netable::IsInEventWorld ()
{
	return mNetableEventHandler->IsInWorld();
}
//----------------------------------------------------------------------------
void Netable::DoEnter ()
{

}
//----------------------------------------------------------------------------
void Netable::DoUpdate ()
{

}
//----------------------------------------------------------------------------
void Netable::DoExecute (Event *event)
{
	PX2_UNUSED(event);
}
//----------------------------------------------------------------------------
void Netable::DoLeave ()
{

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* Netable::GetObjectByName (const std::string& name)
{
	Object* found = Object::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void Netable::GetAllObjectsByName (const std::string& name,
										  std::vector<Object*>& objects)
{
	Object::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Netable::Netable (LoadConstructor value)
:
Object(value)
{
	mNetableEventHandler = new0 NetableEventHandler(this);
}
//----------------------------------------------------------------------------
void Netable::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Object::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(Netable, source);
}
//----------------------------------------------------------------------------
void Netable::Link (InStream& source)
{
	Object::Link(source);
}
//----------------------------------------------------------------------------
void Netable::PostLink ()
{
	Object::PostLink();
}
//----------------------------------------------------------------------------
bool Netable::Register (OutStream& target) const
{
	if (Object::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void Netable::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(Netable, target);
}
//----------------------------------------------------------------------------
int Netable::GetStreamingSize () const
{
	int size = Object::GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------