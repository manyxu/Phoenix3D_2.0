/*
*
* ÎÄ¼þÃû³Æ	£º	TdKeyframeArray.cpp
*
*/

#include "TdKeyframeArray.hpp"
using namespace Td;

//----------------------------------------------------------------------------
bool KeyframeArray::HasSeq (int seq)
{
	if (mRanges.size() == 0)
		return false;

	if (seq<0 || seq>=(int)(mRanges.size()))
		return false;

	if (mRanges[seq].Begin > mRanges[seq].End)
		return false;

	return true;
}
//----------------------------------------------------------------------------