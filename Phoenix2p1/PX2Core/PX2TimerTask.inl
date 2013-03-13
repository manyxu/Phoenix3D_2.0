/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TimerTask.inl
*
*/

//----------------------------------------------------------------------------
inline bool TimerTask::IsCancelled() const
{
	return mIsCancelled;
}
//----------------------------------------------------------------------------
inline Timestamp TimerTask::GetLastExecution() const
{
	return mLastExecution;
}
//----------------------------------------------------------------------------