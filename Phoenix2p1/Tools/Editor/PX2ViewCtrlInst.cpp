/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ViewCtrlInst.cpp
*
*/

#include "PX2ViewCtrlInst.hpp"
#include "PX2ViewCtrl.hpp"
#include "PX2GViewCtrl.hpp"
#include "PX2TerEditCtrl.hpp"
#include "PX2EditSystem.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
ViewCtrlInst::ViewCtrlInst()
	:
mViewCtrl(0),
mInteractionMode(IM_MAX_MODE)
{
	SetInteractionMode(IM_GENERAL);
}
//-----------------------------------------------------------------------------
ViewCtrlInst::~ViewCtrlInst()
{
	if (mViewCtrl)
	{
		delete0(mViewCtrl);
	}
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::DoSelection (PX2::Renderer *renderer, 
	const PX2::Vector2f &point,	SelectionMode mode)
{
	APoint origin;
	AVector direction;

	float x = renderer->GetWidth() * point.X();
	float y = renderer->GetHeight() * (1.0f - point.Y());

	renderer->GetPickRay((int)x, (int)y, origin, direction);

	Scene *scene = EditSystem::GetSingleton().GetEditMap()->GetScene();

	ActorPicker actorPicker;
	actorPicker.Execute(scene, origin, direction, 0.0f, Mathf::MAX_REAL);

	if (actorPicker.Records.size() > 0)
	{
		const ActorPickRecord &record = actorPicker.GetClosestToZero();
		mSelectPoint = origin + direction*record.T;

		if (mode == SM_REPLACE)
		{
			if (!EditSystem::GetSingleton().GetSelection()->IsActorIn(record.Intersected))
			{
				EditSystem::GetSingleton().GetSelection()->Clear();
				EditSystem::GetSingleton().GetSelection()->AddActor(record.Intersected);
			}
		}
		else if (mode == SM_ADD)
		{
			EditSystem::GetSingleton().GetSelection()->AddActor(record.Intersected);
		}
		else if (mode == SM_SUBTRACT)
		{
			EditSystem::GetSingleton().GetSelection()->RemoveActor(record.Intersected);
		}
	}
	else
	{
		if (EditSystem::GetSingleton().GetSelection()->GetActorQuantity() > 0)
		{
			if (mode == SM_REPLACE)
			{
				EditSystem::GetSingleton().GetSelection()->Clear();
			}
		}
	}
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::DoSelection (PX2::Renderer *renderer, 
	const PX2::Vector2f &topLeft,
	const PX2::Vector2f &bottonRight, 
	SelectionMode mode)
{
}
//-----------------------------------------------------------------------------
PX2::APoint ViewCtrlInst::CalculateSelectPoint (PX2::Renderer *renderer,
	const PX2::Vector2f &point)
{
	APoint origin;
	AVector direction;

	float x = renderer->GetWidth() * point.X();
	float y = renderer->GetHeight() * (1.0f - point.Y());

	renderer->GetPickRay((int)x, (int)y, origin, direction);

	Scene *scene = EditSystem::GetSingleton().GetEditMap()->GetScene();

	ActorPicker actorPicker; 
	actorPicker.Execute(scene, origin, direction, 0.0f, Mathf::MAX_REAL);

	mSelectPoint = PX2::APoint::ORIGIN;

	if ((int)actorPicker.Records.size() > 0)
	{
		const ActorPickRecord &record = actorPicker.GetClosestToZero();

		mSelectPoint = origin + direction*record.T;
	}
	else
	{
		PX2::TriMesh *xyPlane = EditSystem::GetSingleton().GetXYPlane();
		APoint pos = xyPlane->LocalTransform.GetTranslate();
		pos.Z() = 0.0f;
		xyPlane->LocalTransform.SetTranslate(pos);

		Picker picker;
		picker.Execute(xyPlane, origin,	direction, 0.0f, Mathf::MAX_REAL);
		if ((int)picker.Records.size() > 0)
		{
			const PickRecord &rec = picker.GetClosestToZero();
			mSelectPoint = origin + direction*rec.T;
		}
	}

	return mSelectPoint;
}
//-----------------------------------------------------------------------------
PX2::APoint ViewCtrlInst::GetSelectPoint ()
{
	return mSelectPoint;
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::SetInteractionMode (InteractionMode im)
{
	if (im == mInteractionMode)
		return;

	switch (mInteractionMode)
	{
	case IM_GENERAL:
		ExitGeneralMode();
		break;
	case IM_TEREDIT:
		ExitTerEditMode();
		break;
	default:
		break;
	}

	mInteractionMode = im;

	switch (mInteractionMode)
	{
	case IM_GENERAL:
		EnterGeneralMode();
		break;
	case IM_TEREDIT:
		EnterTerEditMode();
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleLeftDown (RenderViewWindow *win, 
	wxMouseEvent &e)
{
	if (mViewCtrl)
		mViewCtrl->HandleLeftDown(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleLeftUp (RenderViewWindow *win,
	wxMouseEvent &e)
{
	if (mViewCtrl)
		mViewCtrl->HandleLeftUp(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleMiddleDown (RenderViewWindow *win,
	wxMouseEvent &e)
{
	if (mViewCtrl)
		mViewCtrl->HandleMiddleDown(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleMiddleUp (RenderViewWindow *win, 
	wxMouseEvent &e)
{
	if (mViewCtrl)
		mViewCtrl->HandleMiddleUp(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleMouseWheel (RenderViewWindow *win, 
	wxMouseEvent &e)
{
	if (mViewCtrl)
		mViewCtrl->HandleMouseWheel(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleRightDown (RenderViewWindow *win,
	wxMouseEvent &e)
{
	if (mViewCtrl)
		mViewCtrl->HandleRightDown(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleRightUp (RenderViewWindow *win, 
	wxMouseEvent &e)
{
	if (mViewCtrl)
		mViewCtrl->HandleRightUp(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleMotion (RenderViewWindow *win, 
	wxMouseEvent &e)
{
	if (mViewCtrl)
		mViewCtrl->HandleMotion(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::SwitchPaneController (ViewCtrl *ctrl)
{
	RenderViewWindow *win = 0;

	if (mViewCtrl)
	{
		win = mViewCtrl->GetAttachedWindow();

		delete0(mViewCtrl);
		mViewCtrl = 0;
	}

	mViewCtrl = ctrl;

	if (win && mViewCtrl)
	{
		mViewCtrl->AttachToWindow(win);
	}
}
//-----------------------------------------------------------------------------
void  ViewCtrlInst::EnterGeneralMode ()
{
	SwitchPaneController(new0 GViewCtrl(this));
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::ExitGeneralMode ()
{
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::EnterTerEditMode ()
{
	SwitchPaneController(new0 TerEditCtrl(this));
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::ExitTerEditMode ()
{
}
//-----------------------------------------------------------------------------
