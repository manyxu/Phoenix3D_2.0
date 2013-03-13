/*
*
* ÎÄ¼þÃû³Æ	£º	PX2VisibleSet.cpp
*
*/

#include "PX2VisibleSet.hpp"
#include "PX2Renderable.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
VisibleSet::VisibleSet ()
    :
    mNumVisible(0)
{
}
//----------------------------------------------------------------------------
VisibleSet::~VisibleSet ()
{
}
//----------------------------------------------------------------------------
void VisibleSet::Insert (Renderable* visible)
{
    //int size = (int)mVisible.size();
    //if (mNumVisible < size)
    //{
    //    mVisible[mNumVisible] = visible;
    //}
    //else
    //{
	mVisible.push_back(visible);
    //}
    ++mNumVisible;
}
//----------------------------------------------------------------------------
VisibleSet &VisibleSet::Sort ()
{
	if ((int)mVisible.size() > 0)
	{
		std::sort(mVisible.begin(), mVisible.end(), Renderable::LessThan);
	}
	return *this;
}
//----------------------------------------------------------------------------