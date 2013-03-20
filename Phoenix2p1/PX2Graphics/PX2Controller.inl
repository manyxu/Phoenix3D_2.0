/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Controller.inl
*
*/

//----------------------------------------------------------------------------
inline double Controller::GetRunTime ()
{
	if (!mIsTimeInited)
		return 0.0;

	return mApplicationTime - mInitedApplicationIime;
}
//----------------------------------------------------------------------------
inline Controlledable* Controller::GetControlledable () const
{
    return mObject;
}
//----------------------------------------------------------------------------
inline double Controller::GetApplicationTime () const
{
    return mApplicationTime;
}
//----------------------------------------------------------------------------
inline bool Controller::IsTimeInited ()
{
	return mIsTimeInited;
}
//----------------------------------------------------------------------------
inline double Controller::GetElapsedTime ()
{
	return mApplicationTime - mLastApplicationTime;
}
//----------------------------------------------------------------------------