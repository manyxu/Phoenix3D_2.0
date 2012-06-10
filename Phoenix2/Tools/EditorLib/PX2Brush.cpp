/*
*
* ÎÄ¼þÃû³Æ	£º	Brush.cpp
*
*/

#include "PX2Brush.hpp"
using namespace PX2Editor;
using namespace PX2;

Brush::Brush ()
{
	mSize = 0.0f;
	mStrength = 0.0f;
}
//----------------------------------------------------------------------------
Brush::~Brush ()
{
}
//----------------------------------------------------------------------------
void Brush::SetPos (PX2::APoint pos)
{
	mPos = pos;
}
//----------------------------------------------------------------------------
void Brush::SetSize (float size) 
{
	mSize = size; 
}
//----------------------------------------------------------------------------