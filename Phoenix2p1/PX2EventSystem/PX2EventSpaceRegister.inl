/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EventSpaceRegister.inl
*
*/

//----------------------------------------------------------------------------
template <class ES>
EventSpaceRegister<ES>::EventSpaceRegister ()
:
EventSpace(ES::mName, ES::E_QUANTITY)
{
	EventFactory::GetInstance().RegisterEventSpace(this);
}
//----------------------------------------------------------------------------
template <class ES>
EventSpaceRegister<ES>::~EventSpaceRegister ()
{
}
//----------------------------------------------------------------------------
template <class ES>
Event *EventSpaceRegister<ES>::CreateEventX (Event::EventType eventType)
{
	return ES::GetPtr()->CreateEventX(eventType);
}
//----------------------------------------------------------------------------
template <class ES>
bool EventSpaceRegister<ES>::IsEqual (Event *event, Event::EventType eventType)
{
	return ES::GetPtr()->IsEqual(event, eventType);
}
//----------------------------------------------------------------------------
template <class ES>
Event::EventType EventSpaceRegister<ES>::GetEventType (Event *event)
{
	return ES::GetPtr()->GetEventType(event);
}
//----------------------------------------------------------------------------
template <class ES>
bool EventSpaceRegister<ES>::IsIn (Event *event)
{
	return ES::GetPtr()->IsIn(event);
}
//----------------------------------------------------------------------------