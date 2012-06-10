/*
*
* 文件名称	：	PX2SelectionController.cpp
*
*/

#include "PX2STRSController.hpp"
#include "PX2ControllerInstance.hpp"
#include "PX2RenderViewWindow.hpp"
#include "PX2EditSystem.hpp"
using namespace PX2Editor;
using namespace PX2;

STRSController::STRSController(ControllerInstance* callback)
:
PaneController(callback),
mLeftDown(false),
mRightDown(false),
mMiddleDown(false),
mDragSelect(false),
mAttachedCtrl(0),
mTransChanged(false),
mSelectPen(new wxPen(*wxWHITE, 1, wxSOLID))
{
}
//-----------------------------------------------------------------------------
STRSController::~STRSController()
{
	delete mSelectPen;
}
//-----------------------------------------------------------------------------
void STRSController::HandleLeftDown (RenderViewWindow *win, 
										  wxMouseEvent &e)
{
	AttachToWindow(win);
	StartMouseDrag(e);
	mLeftDown = true;

	if (!mAttachedCtrl)
		return;

	wxPoint mousePoint = e.GetPosition();
	wxSize size = win->GetSize();

	PX2::Vector2f point(
		(float)mousePoint.x/(float)size.x,
		(float)mousePoint.y/(float)size.y);

	mAttachedCtrl->OnLeftMouseDown(win->GetRenderer(), point);

	if (mAttachedCtrl->GetDragType() == SceneNodeCtrl::DT_NONE)
		FinishClickSelection(e);

	mCommand = new0 ActorTransCommand();
}
//-----------------------------------------------------------------------------
void STRSController::HandleLeftUp (RenderViewWindow *win, wxMouseEvent &e)
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
				EditCommandManager::GetSingleton().PushUnDo(mCommand);
				mTransChanged = false;
			}
		}

		if (mDragSelect)
		{
			mDragSelect = false;
		}
	}
	
	if (mAttachedCtrl)
		mAttachedCtrl->OnLeftMouseUp(win->GetRenderer(), Vector2f::ZERO);
}
//-----------------------------------------------------------------------------
void STRSController::HandleMiddleDown(RenderViewWindow *win,
										   wxMouseEvent &e)
{
	AttachToWindow(win);
	StartMouseDrag(e);
	mMiddleDown = true;
}
//-----------------------------------------------------------------------------
void STRSController::HandleMiddleUp(RenderViewWindow *win, 
										 wxMouseEvent &e)
{
	if (mMiddleDown)
	{
		mMiddleDown = false;
		EndMouseDrag(e);
	}
}
//-----------------------------------------------------------------------------
void STRSController::HandleMouseWheel(RenderViewWindow *win, wxMouseEvent &e)
{
	AttachToWindow(win);
	
	float delta = e.GetWheelRotation()*0.02f;

	mWindow->ZoomCamera(delta);
}
//-----------------------------------------------------------------------------
void STRSController::HandleRightDown(RenderViewWindow *win, wxMouseEvent &e)
{
	AttachToWindow(win);
	StartMouseDrag(e);

	RightGetSelectPoint(e);

	mRightDown = true;
}
//-----------------------------------------------------------------------------
void STRSController::HandleRightUp(RenderViewWindow *win, wxMouseEvent &e)
{
	if (mRightDown)
	{
		mRightDown = false;
		EndMouseDrag(e);
	}
}
//-----------------------------------------------------------------------------
void STRSController::HandleMotion (RenderViewWindow *win, wxMouseEvent &e)
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
		return;

	EditSystem::EditMode editMode = EditSystem::GetSingleton().GetEditMode();

	if (mLeftDown)
	{
	    if (editMode == EditSystem::EM_SELECT)
		{
			if (mDragSelect)
			{
				// 已经绘制过，翻转回去
				DrawSelectBox(mLastMousePoint, mLastSelectEnd);
			}

			mLastSelectEnd = e.GetPosition();

			mDragSelect = true;

			DrawSelectBox(mLastMousePoint, e.GetPosition());
		}
		else if (editMode == EditSystem::EM_TRANSLATE ||
			editMode == EditSystem::EM_ROLATE ||
			editMode == EditSystem::EM_SCALE)
		{
			if (mAttachedCtrl)
				mAttachedCtrl->OnMouseMove(win->GetRenderer(),
				diff.x*mPixelToWorld.first, -diff.y*mPixelToWorld.second);

			mTransChanged = true;
			mLastMousePoint = point;
		}
	}
	else if (mMiddleDown)
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
void STRSController::HandleKeyDown (RenderViewWindow *win, wxKeyEvent &e)
{
	PaneController::HandleKeyDown(win, e);

	//long keycode = e.GetKeyCode();

	//unsigned char key = (unsigned char)keycode;

	//if (key == _T('W'))
	//{
	//	win->MoveCamera(0, 1.0f);
	//}
	//else if (key == _T('S'))
	//{
	//	win->MoveCamera(0, -1.0f);
	//}
	//else if (key == _T('A'))
	//{
	//	win->MoveCamera(1.0f, 0.0f);
	//}
	//else if (key == _T('D'))
	//{
	//	win->MoveCamera(-1.0f, 0.0f);
	//}
}
//-----------------------------------------------------------------------------
void STRSController::HandleKeyUp (RenderViewWindow *win, wxKeyEvent &e)
{
	PaneController::HandleKeyUp(win, e);

}
//-----------------------------------------------------------------------------
void STRSController::HandleChar (RenderViewWindow *win, wxKeyEvent &e)
{
	PaneController::HandleChar(win, e);
}
//-----------------------------------------------------------------------------
void STRSController::FinishClickSelection (wxMouseEvent& e)
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

	if (mDragSelect)
	{ // 区域选择
	}
	else
	{ // 点选选择
		mControllerInstance->DoSelection(mWindow->GetRenderer(), topLeft, 
			selectMode);
	}
}
//-----------------------------------------------------------------------------
void STRSController::FinishDragSelection(wxMouseEvent &e)
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

	if (mDragSelect)
	{ // 区域选择
		DrawSelectBox(mLastMousePoint, mLastSelectEnd);

		mControllerInstance->DoSelection(mWindow->GetRenderer(), topLeft,
			bottomRight, selectMode);
	}
	else
	{ // 点选选择
	}
}
//-----------------------------------------------------------------------------
void STRSController::CalcSelectionBox (wxMouseEvent& e, PX2::Vector2f &topLeft, 
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
void STRSController::DrawSelectBox(const wxPoint &from, const wxPoint &to)
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
void STRSController::StartMouseDrag (wxMouseEvent &e)
{
	PaneController::StartMouseDrag(e);
}
//-----------------------------------------------------------------------------
void STRSController::EndMouseDrag (wxMouseEvent &e)
{
	PaneController::EndMouseDrag(e);
}
//-----------------------------------------------------------------------------
void STRSController::AttachToWindow (RenderViewWindow *win)
{
	PaneController::AttachToWindow(win);

	mAttachedCtrl = win->GetSceneNodeCtrl();
}
//-----------------------------------------------------------------------------
void STRSController::RightGetSelectPoint (wxMouseEvent& e)
{
	PX2::Vector2f topLeft, bottomRight;

	CalcSelectionBox(e, topLeft, bottomRight);

	mControllerInstance->CalculateSelectPoint(mWindow->GetRenderer(), topLeft);
}
//----------------------------------------------------------------------------