/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Float4.cpp
*
*/

#include "PX2Float4.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Float4::Float4 ()
{
}
//----------------------------------------------------------------------------
Float4::~Float4 ()
{
}
//----------------------------------------------------------------------------
Float4::Float4 (float f0, float f1, float f2, float f3)
{
	mTuple[0] = f0;
	mTuple[1] = f1;
	mTuple[2] = f2;
	mTuple[3] = f3;
}
//----------------------------------------------------------------------------
Float4::Float4 (const Float4& tuple)
{
	mTuple[0] = tuple.mTuple[0];
	mTuple[1] = tuple.mTuple[1];
	mTuple[2] = tuple.mTuple[2];
	mTuple[3] = tuple.mTuple[3];
}
//----------------------------------------------------------------------------
Float4& Float4::operator= (const Float4& tuple)
{
	mTuple[0] = tuple.mTuple[0];
	mTuple[1] = tuple.mTuple[1];
	mTuple[2] = tuple.mTuple[2];
	mTuple[3] = tuple.mTuple[3];
	return *this;
}
//----------------------------------------------------------------------------