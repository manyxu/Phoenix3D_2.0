/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Controlledable.inl
*
*/

//----------------------------------------------------------------------------
inline int Controlledable::GetNumControllers () const
{
    return mNumControllers;
}
//----------------------------------------------------------------------------
inline Controller* Controlledable::GetController (int i) const
{
    if (0 <= i && i < mNumControllers)
    {
        return mControllers[i];
    }

    assertion(false, "Invalid index in GetController.\n");
    return 0;
}
//----------------------------------------------------------------------------