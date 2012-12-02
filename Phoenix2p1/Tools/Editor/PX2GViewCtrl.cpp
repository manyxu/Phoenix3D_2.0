/*
*
* 文件名称	：	PX2GeneralCtrl.cpp
*
*/

#include "PX2GViewCtrl.hpp"
#include "PX2RenderViewWindow.hpp"
#include "PX2EditSystem.hpp"
#include "PX2ViewCtrlInst.hpp"
using namespace PX2Editor;
using namespace PX2;

GViewCtrl::GViewCtrl(ViewCtrlInst *inst)
	:
ViewCtrl(inst),
	mLeftDown(false),
	mRightDown(false),
	mMiddleDown(false),
	mDragRangeSelect(false),
	mAttachedCtrl(0),
	mSelectPen(new wxPen(*wxWHITE, 1, wxSOLID))
{
}
//-----------------------------------------------------------------------------
GViewCtrl::~GViewCtrl()
{
	if (mSelectPen)
	{
		delete mSelectPen;
		mSelectPen = 0;
	}
}
//-----------------------------------------------------------------------------
void GViewCtrl::HandleLeftDown (RenderViewWindow *win, wxMouseEvent &e)
{
	AttachToWindow(win);
	StartMouseDrag(e);
	mLeftDown = true;

	wxPoint mousePoint = e.GetPosition();
	wxSize size = win->GetSize();

	PX2::Vector2f point((float)mousePoint.x, (float)mousePoint.y);

	mAttachedCtrl->OnLeftMouseDown(win->GetRenderer(), point);

	if (mAttachedCtrl->GetDragType() == SceneNodeCtrl::DT_NONE)
		FinishClickSelection(e);

	mCommand = 0;
	mCommand = new0 ActorTransCommand();
}
//-----------------------------------------------------------------------------
void GViewCtrl::HandleLeftUp (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);

	if (mLeftDown)
	{
		FinishDragSelection(e);
		mLeftDown = false;
		EndMouseDrag(e);

		EditSystem::EditMode mode = EditSystem::GetSingleton().GetEditMode();
		if (mode == EditSystem::EM_TRANSLATE || mode == EditSystem::EM_ROLATE
			|| mode == EditSystem::EM_SCALE)
		{
			if (mTransChanged)
			{
				EditSystem::GetSingleton().GetCM()->PushUnDo(mCommand);
				mTransChanged = false;
			}
		}

		if (mDragRangeSelect)
		{
			mDragRangeSelect = false;
		}
	}

	if (mAttachedCtrl)
		mAttachedCtrl->OnLeftMouseUp(win->GetRenderer(), Vector2f::ZERO);
}
//-----------------------------------------------------------------------------
void GViewCtrl::HandleMiddleDown(RenderViewWindow *win,
	wxMouseEvent &e)
{
	AttachToWindow(win);
	StartMouseDrag(e);
	mMiddleDown = true;
}
//-----------------------------------------------------------------------------
void GViewCtrl::HandleMiddleUp(RenderViewWindow *win, 
	wxMouseEvent &e)
{
	if (mMiddleDown)
	{
		mMiddleDown = false;
		EndMouseDrag(e);
	}
}
//-----------------------------------------------------------------------------
void GViewCtrl::HandleMouseWheel(RenderViewWindow *win, wxMouseEvent &e)
{
	AttachToWindow(win);

	float delta = e.GetWheelRotation()*0.02f;

	mWindow->ZoomCamera(delta);
}
//-----------------------------------------------------------------------------
void GViewCtrl::HandleRightDown(RenderViewWindow *win, wxMouseEvent &e)
{
	AttachToWindow(win);
	StartMouseDrag(e);

	RightGetSelectPoint(e);

	mRightDown = true;
}
//-----------------------------------------------------------------------------
void GViewCtrl::HandleRightUp(RenderViewWindow *win, wxMouseEvent &e)
{
	if (mRightDown)
	{
		mRightDown = false;
		EndMouseDrag(e);
	}
}
//-----------------------------------------------------------------------------
void GViewCtrl::HandleMotion (RenderViewWindow *win, wxMouseEvent &e)
{
	if (mWindow != win)
	{
		e.Skip();
		return;
	}

	bool mouseMoved = false;
	wxPoint point = e.GetPosition();
	wxPoint diff = point - mLastMousePoint;
	if (diff.x!=0 || diff.y!=0)
	{
		mouseMoved = true;
	}
	else
	{
		return;
	}

	EditSystem::EditMode editMode = EditSystem::GetSingleton().GetEditMode();

	if (editMode == EditSystem::EM_TRANSLATE 
		|| editMode == EditSystem::EM_ROLATE
		|| editMode == EditSystem::EM_SCALE)
	{
		if (mAttachedCtrl)
			mAttachedCtrl->OnMouseMove(mLeftDown,
			win->GetRenderer(),
			Vector2f((float)point.x, (float)point.y), 
			Vector2f((float)mLastMousePoint.x, (float)mLastMousePoint.y));

		if (mLeftDown)
		{
			mTransChanged = true;
			mLastMousePoint = point;
		}
	}

	if (mMiddleDown)
	{
		mWindow->PanCamera(diff.x*mPixelToWorld.first, 
			diff.y*mPixelToWorld.second);

		mLastMousePoint = e.GetPosition();
	}
	else if (mRightDown)
	{
		if (mWindow->GetViewType() == RenderViewWindow::VT_PERSPECTIVE)
		{
			if (wxGetKeyState(WXK_ALT))
			{
				mWindow->ZoomCamera((float)diff.y);

				mLastMousePoint = e.GetPosition();
			}
			else
			{
				mWindow->RolateCamera(diff.x*mPixelToWorld.first,
					diff.y*mPixelToWorld.second);

				mLastMousePoint = e.GetPosition();
			}
		}
		else
		{
			mWindow->PanCamera(diff.x*mPixelToWorld.first,
				diff.y*mPixelToWorld.second);

			mLastMousePoint = e.GetPosition();
		}
	}
}
//-----------------------------------------------------------------------------
void GViewCtrl::HandleKeyDown (RenderViewWindow *win, wxKeyEvent &e)
{
	ViewCtrl::HandleKeyDown(win, e);
}
//-----------------------------------------------------------------------------
void GViewCtrl::HandleKeyUp (RenderViewWindow *win, wxKeyEvent &e)
{
	ViewCtrl::HandleKeyUp(win, e);
}
//-----------------------------------------------------------------------------
void GViewCtrl::HandleChar (RenderViewWindow *win, wxKeyEvent &e)
{
	ViewCtrl::HandleChar(win, e);
}
//-----------------------------------------------------------------------------
void GViewCtrl::FinishClickSelection (wxMouseEvent& e)
{
	PX2::Vector2f topLeft, bottomRight;

	SelectionMode selectMode = SM_REPLACE;
	if (e.ControlDown())
	{
		selectMode = SM_ADD;
	}
	else if (e.ShiftDown())
	{
		selectMode = SM_SUBTRACT;
	}

	CalcSelectionBox(e, topLeft, bottomRight);

	if (mDragRangeSelect)
	{
	}
	else
	{ // 点选选择
		mViewCtrlInst->DoSelection(mWindow->GetRenderer(), topLeft, 
			selectMode);
	}
}
//-----------------------------------------------------------------------------
void GViewCtrl::FinishDragSelection(wxMouseEvent &e)
{
	PX2::Vector2f topLeft, bottomRight;

	SelectionMode selectMode = SM_REPLACE;

	if (e.ControlDown())
	{
		selectMode = SM_ADD;
	}
	else if (e.ShiftDown())
	{
		selectMode = SM_SUBTRACT;
	}

	CalcSelectionBox(e, topLeft, bottomRight);

	if (mDragRangeSelect)
	{ // 区域选择
		DrawSelectBox(mLastMousePoint, mLastSelectEnd);

		mViewCtrlInst->DoSelection(mWindow->GetRenderer(), topLeft,
			bottomRight, selectMode);
	}
	else
	{ // 点选选择
	}
}
//-----------------------------------------------------------------------------
void GViewCtrl::CalcSelectionBox (wxMouseEvent& e, PX2::Vector2f &topLeft, 
	PX2::Vector2f &bottomRight)
{
	wxSize size = mWindow->GetSize();

	PX2::Vector2f tempTopLeft(
		(float)mLastMousePoint.x/(float)size.x,
		(float)mLastMousePoint.y/(float)size.y);
	PX2::Vector2f tempBottomRight(
		(float)e.GetPosition().x/(float)size.x,
		(float)e.GetPosition().y/(float)size.y);

	topLeft.X() = min(tempTopLeft.X(), tempBottomRight.X());
	topLeft.Y() = min(tempTopLeft.Y(), tempBottomRight.Y());
	bottomRight.X() = max(tempTopLeft.X(), tempBottomRight.X());
	bottomRight.Y() = max(tempTopLeft.Y(), tempBottomRight.Y());
}
//-----------------------------------------------------------------------------
void GViewCtrl::DrawSelectBox(const wxPoint &from, const wxPoint &to)
{
	wxSize size = mWindow->GetSize();
	wxScreenDC dc;

	dc.SetLogicalFunction(wxINVERT);
	dc.SetPen(*mSelectPen);
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	wxPoint newFrom(from);
	wxPoint newTo(to);

	if (newFrom.x > size.x)
		newFrom.x = size.x;
	else if (newFrom.x < 0)
		newFrom.x = 0;

	if (newFrom.y > size.y)
		newFrom.y = size.y;
	else if (newFrom.y < 0)
		newFrom.y = 0;

	if (newTo.x > size.x)
		newTo.x = size.x;
	if (newTo.x < 0)
		newTo.x = 0;
	if (newTo.y > size.y)
		newTo.y = size.y;
	else if (newTo.y < 0)
		newTo.y = 0;

	newFrom = mWindow->ClientToScreen(newFrom);
	newTo = mWindow->ClientToScreen(newTo);

	wxSize rectSize(newTo.x-newFrom.x, newTo.y-newFrom.y);

	dc.DrawRectangle(newFrom, rectSize);
}
//-----------------------------------------------------------------------------
void GViewCtrl::StartMouseDrag (wxMouseEvent &e)
{
	ViewCtrl::StartMouseDrag(e);
}
//-----------------------------------------------------------------------------
void GViewCtrl::EndMouseDrag (wxMouseEvent &e)
{
	ViewCtrl::EndMouseDrag(e);
}
//-----------------------------------------------------------------------------
void GViewCtrl::AttachToWindow (RenderViewWindow *win)
{
	ViewCtrl::AttachToWindow(win);

	mAttachedCtrl = win->GetSceneNodeCtrl();
}
//-----------------------------------------------------------------------------
void GViewCtrl::RightGetSelectPoint (wxMouseEvent& e)
{
	PX2::Vector2f topLeft, bottomRight;

	CalcSelectionBox(e, topLeft, bottomRight);

	mViewCtrlInst->CalculateSelectPoint(mWindow->GetRenderer(), topLeft);
}
//----------------------------------------------------------------------------