/*
*
* 文件名称	：	PX2TerEditCtrl.cpp
*
*/

#include "PX2TerEditCtrl.hpp"
#include "PX2RenderViewWindow.hpp"
#include "PX2EditSystem.hpp"
#include "PX2Project.hpp"
using namespace PX2Editor;
using namespace PX2;

TerEditCtrl::TerEditCtrl (ViewCtrlInst *inst)
	:
ViewCtrl(inst),
mLeftDown(false),
mRightDown(false),
mMiddleDown(false)
{

}
//-----------------------------------------------------------------------------
TerEditCtrl::~TerEditCtrl ()
{
}
//-----------------------------------------------------------------------------
void TerEditCtrl::HandleLeftDown (RenderViewWindow *win, 
	wxMouseEvent &e)
{
	AttachToWindow(win);
	StartMouseDrag(e);
	mLeftDown = true;

	EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()->SelectPage();

	EditSystem::GetSingleton().GetTerrainEdit()->Apply();
	UpdateBrushPos(win, e);
}
//-----------------------------------------------------------------------------
void TerEditCtrl::HandleLeftUp (RenderViewWindow *win,
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
void TerEditCtrl::HandleMiddleDown(RenderViewWindow *win, 
	wxMouseEvent &e)
{
	AttachToWindow(win);
	StartMouseDrag(e);
	mMiddleDown = true;
}
//-----------------------------------------------------------------------------
void TerEditCtrl::HandleMiddleUp(RenderViewWindow *win, 
	wxMouseEvent &e)
{
	if (mMiddleDown)
	{
		mMiddleDown = false;
		EndMouseDrag(e);
	}
}
//-----------------------------------------------------------------------------
void TerEditCtrl::HandleMouseWheel(RenderViewWindow *win,
	wxMouseEvent &e)
{
	AttachToWindow(win);

	float delta = e.GetWheelRotation()*0.02f;

	mWindow->ZoomCamera(delta);

	UpdateBrushPos(win, e);
}
//-----------------------------------------------------------------------------
void TerEditCtrl::HandleRightDown(RenderViewWindow *win,
	wxMouseEvent &e)
{
	AttachToWindow(win);
	StartMouseDrag(e);
	mRightDown = true;

	EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()->SelectPage();
}
//-----------------------------------------------------------------------------
void TerEditCtrl::HandleRightUp(RenderViewWindow *win, 
	wxMouseEvent &e)
{
	if (mRightDown)
	{
		mRightDown = false;
		EndMouseDrag(e);
	}
}
//-----------------------------------------------------------------------------
void TerEditCtrl::HandleMotion (RenderViewWindow *win,
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
	{
		return;
	}

	if (mLeftDown)
	{
		// Jungler在鼠标移动中不处理Apply
		if (TerrainProcess::TPT_JUNGLER != 
			EditSystem::GetSingleton().GetTerrainEdit()->GetEditType())
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
void TerEditCtrl::UpdateBrushPos (RenderViewWindow *win, 
	wxMouseEvent &e)
{
	PX2::Scene *scene = 0;
	
	if (Project::GetSingletonPtr())
		scene = Project::GetSingleton().GetScene();

	if (!scene)
		return;

	PX2::TerrainActor *actor = scene->GetTerrainActor();
	if (!actor)
		return;

	PX2::RawTerrain *terrain = actor->GetRawTerrain();
	PX2::Movable *pickObject = 0;

#ifdef _DEBUG
	pickObject = EditSystem::GetSingleton().GetXYPlane();
#else
	pickObject = terrain;
#endif

	if (pickObject)
	{
		PX2::APoint origin;
		PX2::AVector dir;
		int x = e.GetX();
		int y = e.GetY();
		y = win->GetSize().GetHeight() - y;
		win->GetRenderer()->GetPickRay(x, y, origin, dir);

		PX2::Picker picker;
		picker.Execute(pickObject, origin, dir, 0.0f, Mathf::MAX_REAL);
		if ((int)picker.Records.size() > 0)
		{
			PX2::PickRecord pickRecord = picker.GetClosestToZero();
			PX2::APoint dest = origin + dir*pickRecord.T;

			EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()
				->SetPos(dest);
		}
	}
}
//-----------------------------------------------------------------------------