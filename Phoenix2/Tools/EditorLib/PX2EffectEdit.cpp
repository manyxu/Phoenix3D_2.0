/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectEdit.cpp
*
*/

#include "PX2EffectEdit.hpp"
#include "PX2EditEventType.hpp"
using namespace PX2Editor;
using namespace PX2;

EffectEdit::EffectEdit ()
{
	mInsertingTime = -1.0f;
}
//----------------------------------------------------------------------------
EffectEdit::~EffectEdit ()
{
}
//----------------------------------------------------------------------------
void EffectEdit::SetEditEffectNode (PX2::EffectNode *node)
{
	mEffectNode = node;
}
//----------------------------------------------------------------------------
PX2::EffectNode *EffectEdit::GetEditEffectNode ()
{
	return mEffectNode;
}
//----------------------------------------------------------------------------
void EffectEdit::SetEditEffect (PX2::Movable *obj)
{
	mEffect = obj;
}
//----------------------------------------------------------------------------
PX2::Movable *EffectEdit::GetEditEffect ()
{
	return mEffect;
}
//----------------------------------------------------------------------------
void EffectEdit::SetInsertingTime (float insertingTime)
{
	mInsertingTime = insertingTime;
}
//----------------------------------------------------------------------------
float EffectEdit::GetInsertingTime ()
{
	return mInsertingTime;
}
//----------------------------------------------------------------------------