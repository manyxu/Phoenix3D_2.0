/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SwitchNode.inl
*
*/

//----------------------------------------------------------------------------
inline void SwitchNode::SetActiveChild (int activeChild)
{
    assertion(
        activeChild == SN_INVALID_CHILD || activeChild < (int)mChild.size(),
        "Invalid active child specified\n");

    mActiveChild = activeChild;
}
//----------------------------------------------------------------------------
inline int SwitchNode::GetActiveChild () const
{
    return mActiveChild;
}
//----------------------------------------------------------------------------
inline void SwitchNode::DisableAllChildren ()
{
    mActiveChild = SN_INVALID_CHILD;
}
//----------------------------------------------------------------------------
