/*
*
* ÎÄ¼þÃû³Æ	£º	PX2CurveGroup.cpp
*
*/

#include "PX2CurveGroup.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditSystem.hpp"
using namespace PX2Editor;
using namespace PX2;

//----------------------------------------------------------------------------
CurveGroup::CurveGroup (CGType t)
	:
mData(0),
mDataPointer(0),
mType(t)
{
}
//----------------------------------------------------------------------------
CurveGroup::~CurveGroup ()
{
	mCurve0 = 0;
	mCurve1 = 0;
	mCurve2 = 0;
	mCurve3 = 0;
	mCurve4 = 0;
	mCurve5 = 0;
}
//----------------------------------------------------------------------------
void CurveGroup::SetName (std::string name)
{
	mName = name;
}
//----------------------------------------------------------------------------
std::string CurveGroup::GetName ()
{
	return mName;
}
//----------------------------------------------------------------------------
void CurveGroup::SetVisible (bool show)
{
	if (mCurve0)
		mCurve0->SetVisible(show);

	if (mCurve1)
		mCurve1->SetVisible(show);

	if (mCurve2)
		mCurve2->SetVisible(show);

	if (mCurve3)
		mCurve3->SetVisible(show);

	if (mCurve4)
		mCurve4->SetVisible(show);

	if (mCurve5)
		mCurve5->SetVisible(show);
}
//----------------------------------------------------------------------------
void CurveGroup::SetVisible (int index, bool show)
{
	if (0 == index)
	{
		if (mCurve0)
			mCurve0->SetVisible(show);
	}
	else if (1 == index)
	{
		if (mCurve1)
			mCurve1->SetVisible(show);
	}
	else if (2 == index)
	{
		if (mCurve2)
			mCurve2->SetVisible(show);
	}
	else if (3 == index)
	{
		if (mCurve3)
			mCurve3->SetVisible(show);
	}
	else if (4 == index)
	{
		if (mCurve4)
			mCurve4->SetVisible(show);
	}
	else if (5 == index)
	{
		if (mCurve5)
			mCurve5->SetVisible(show);
	}
}
//----------------------------------------------------------------------------
void CurveGroup::AddPoint (const PX2::APoint &pos)
{
	if (CGT_FLOAT == mType)
	{
		if (mCurve0)
			mCurve0->AddPoint(pos.X(), pos.Z());
	}
	else if (CGT_FLOATRANGE == mType)
	{
		if (mCurve0)
			mCurve0->AddPoint(pos.X(), pos.Z());

		if (mCurve1)
			mCurve1->AddPoint(pos.X(), pos.Z());
	}
	else if (CGT_FLOAT3 == mType)
	{
		if (mCurve0)
			mCurve0->AddPoint(pos.X(), pos.Z());
	}
	else if (CGT_FLOAT3RANGE == mType)
	{
		if (mCurve0)
			mCurve0->AddPoint(pos.X(), pos.Z());

		if (mCurve3)
			mCurve3->AddPoint(pos.X(), pos.Z());
	}

	UpdateCurve ();
	ReCreateCtrls();

	Object *obj = (Object*)mDataPointer;
	EffectModule *module = DynamicCast<EffectModule>(obj);
	if (module)
	{
		Event *ent = EditorEventSpace::CreateEventX
			(EditorEventSpace::CurveChangedByEditor);
		ent->SetData<void*>(mCurve0);
		EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
	}
}
//----------------------------------------------------------------------------
void CurveGroup::DeletePoint (int index)
{
	if (CGT_FLOAT == mType)
	{
		if (mCurve0)
			mCurve0->DeletePoint(index);
	}
	else if (CGT_FLOATRANGE == mType)
	{
		if (mCurve0)
			mCurve0->DeletePoint(index);

		if (mCurve1)
			mCurve1->DeletePoint(index);
	}
	else if (CGT_FLOAT3 == mType)
	{
		if (mCurve0)
			mCurve0->DeletePoint(index);
	}
	else if (CGT_FLOAT3RANGE == mType)
	{
		if (mCurve0)
			mCurve0->DeletePoint(index);

		if (mCurve3)
			mCurve3->DeletePoint(index);
	}

	UpdateCurve ();
	ReCreateCtrls();

	EditSystem::GetSingleton().GetCurveEdit()->SetSelectedCurveCtrl(0);

	Object *obj = (Object*)mDataPointer;
	EffectModule *module = DynamicCast<EffectModule>(obj);
	if (module)
	{
		Event *ent = EditorEventSpace::CreateEventX
			(EditorEventSpace::CurveChangedByEditor);
		ent->SetData<void*>(mCurve0);
		EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
	}
}
//----------------------------------------------------------------------------
int CurveGroup::SetInVal (int index, float val)
{
	int newIndex = -1;

	if (CGT_FLOAT == mType)
	{
		if (mCurve0)
			newIndex = mCurve0->SetInVal(index, val);
	}
	else if (CGT_FLOATRANGE == mType)
	{
		if (mCurve0)
			newIndex = mCurve0->SetInVal(index, val);

		if (mCurve1)
			mCurve1->SetInVal(index, val);
	}
	else if (CGT_FLOAT3 == mType)
	{
		if (mCurve0)
			newIndex = mCurve0->SetInVal(index, val);
	}
	else if (CGT_FLOAT3RANGE == mType)
	{
		if (mCurve0)
			newIndex = mCurve0->SetInVal(index, val);

		if (mCurve3)
			mCurve3->SetInVal(index, val);
	}

	UpdateCurve ();
	UpdateCtrls ();

	Object *obj = (Object*)mDataPointer;
	EffectModule *module = DynamicCast<EffectModule>(obj);
	if (module)
	{
		Event *ent = EditorEventSpace::CreateEventX
			(EditorEventSpace::CurveChangedByEditor);
		ent->SetData<void*>(mCurve0);
		EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
	}

	return newIndex;
}
//----------------------------------------------------------------------------
void CurveGroup::UpdateCurve ()
{
	if (mCurve0)
		mCurve0->UpdateCurve();

	if (mCurve1)
		mCurve1->UpdateCurve();

	if (mCurve2)
		mCurve2->UpdateCurve();

	if (mCurve3)
		mCurve3->UpdateCurve();

	if (mCurve4)
		mCurve4->UpdateCurve();

	if (mCurve5)
		mCurve5->UpdateCurve();
}
//----------------------------------------------------------------------------
void CurveGroup::UpdateCtrls ()
{
	if (mCurve0)
		mCurve0->UpdateCtrls();

	if (mCurve1)
		mCurve1->UpdateCtrls();

	if (mCurve2)
		mCurve2->UpdateCtrls();

	if (mCurve3)
		mCurve3->UpdateCtrls();

	if (mCurve4)
		mCurve4->UpdateCtrls();

	if (mCurve5)
		mCurve5->UpdateCtrls();
}
//----------------------------------------------------------------------------
void CurveGroup::ReCreateCtrls ()
{
	if (mCurve0)
		mCurve0->ReCreateCtrls();

	if (mCurve1)
		mCurve1->ReCreateCtrls();

	if (mCurve2)
		mCurve2->ReCreateCtrls();

	if (mCurve3)
		mCurve3->ReCreateCtrls();

	if (mCurve4)
		mCurve4->ReCreateCtrls();

	if (mCurve5)
		mCurve5->ReCreateCtrls();
}
//----------------------------------------------------------------------------