/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainHeightController.cpp
*
*/

#include "PX2TerrainEditController.hpp"
#include "PX2RenderViewWindow.hpp"
using namespace PX2Editor;
using namespace PX2;

TerrainEditController::TerrainEditController (ControllerInstance 
												  *callback)
												  :
PaneController(callback),
mLeftDown(false),
mRightDown(false),
mMiddleDown(false)
{

}
//-----------------------------------------------------------------------------
TerrainEditController::~TerrainEditController ()
{

}
//-----------------------------------------------------------------------------
void TerrainEditController::HandleLeftDown (RenderViewWindow *win, 
											  wxMouseEvent &e)
{
	AttachToWindow(win);
	StartMouseDrag(e);
	mLeftDown = true;

	EditSystem::GetSingleton().GetTerrainEdit()->Apply();
	UpdateBrushPos(win, e);
}
//-----------------------------------------------------------------------------
void TerrainEditController::HandleLeftUp (RenderViewWindow *win,
											wxMouseEvent &e)
{
	PX2_UNUSED(win);

	if (mLeftDown)
	{
		mLeftDown = false;
		EndMouseDrag(e);
	}
}
//-----------------------------------------------------------------------------
void TerrainEditController::HandleMiddleDown(RenderViewWindow *win, 
											   wxMouseEvent &e)
{
	AttachToWindow(win);
	StartMouseDrag(e);
	mMiddleDown = true;
}
//-----------------------------------------------------------------------------
void TerrainEditController::HandleMiddleUp(RenderViewWindow *win, 
											 wxMouseEvent &e)
{
	if (mMiddleDown)
	{
		mMiddleDown = false;
		EndMouseDrag(e);
	}
}
//-----------------------------------------------------------------------------
void TerrainEditController::HandleMouseWheel(RenderViewWindow *win,
											   wxMouseEvent &e)
{
	AttachToWindow(win);

	float delta = e.GetWheelRotation()*0.02f;

	mWindow->ZoomCamera(delta);

	UpdateBrushPos(win, e);
}
//-----------------------------------------------------------------------------
void TerrainEditController::HandleRightDown(RenderViewWindow *win,
											  wxMouseEvent &e)
{
	AttachToWindow(win);
	StartMouseDrag(e);
	mRightDown = true;

	EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()->SelectPage();
}
//-----------------------------------------------------------------------------
void TerrainEditController::HandleRightUp(RenderViewWindow *win, 
											wxMouseEvent &e)
{
	if (mRightDown)
	{
		mRightDown = false;
		EndMouseDrag(e);
	}
}
//-----------------------------------------------------------------------------
void TerrainEditController::HandleMotion (RenderViewWindow *win,
											wxMouseEvent &e)
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

	if (mLeftDown)
	{
		EditSystem::GetSingleton().GetTerrainEdit()->Apply();
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

	UpdateBrushPos(win, e);
}
//-----------------------------------------------------------------------------
void TerrainEditController::UpdateBrushPos (RenderViewWindow *win, 
											  wxMouseEvent &e)
{
	PX2::Scene *scene = EditSystem::GetSingleton().GetEditMap()->GetScene();
	if (!scene)
		return;
	
	PX2::RawTerrainActor *actor = scene->GetRawTerrainActor();
	if (!actor)
		return;

	PX2::RawTerrain *terrain = actor->GetTerrain();

	if (terrain)
	{
		PX2::APoint origin;
		PX2::AVector dir;
		int x = e.GetX();
		int y = e.GetY();
		y = win->GetSize().GetHeight() - y;
		win->GetRenderer()->GetPickRay(x, y, origin, dir);

		PX2::Picker picker;
		picker.Execute(terrain, origin, dir, 0.0f, Mathf::MAX_REAL);
		if ((int)picker.Records.size() > 0)
		{
			PX2::PickRecord pickRecord = picker.GetClosestToZero();
			PX2::APoint dest = origin + dir*pickRecord.T;

			EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()->SetPos(dest);
		}
	}

}
//-----------------------------------------------------------------------------