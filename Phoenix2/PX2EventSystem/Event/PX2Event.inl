/*
*
* ÎÄ¼şÃû³Æ	£º	PX2Event.inl
*
*/

//----------------------------------------------------------------------------
template <class DType>
void Event::SetData (DType data)
{
	mEventData = EventDataTemplate<DType>::Set(data);
}
//----------------------------------------------------------------------------
template <class DType>
DType Event::GetData ()
{
	return EventDataTemplate<DType>::Get(mEventData);
}
//----------------------------------------------------------------------------