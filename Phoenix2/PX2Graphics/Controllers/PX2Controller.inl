/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Controller.inl
*
*/

//----------------------------------------------------------------------------
inline Controlledable* Controller::GetObject () const
{
    return mObject;
}
//----------------------------------------------------------------------------
inline void Controller::SetApplicationTime (double applicationTime)
{
    mApplicationTime = applicationTime;
}
//----------------------------------------------------------------------------
inline double Controller::GetApplicationTime () const
{
    return mApplicationTime;
}
//----------------------------------------------------------------------------