/*
*
* ÎÄ¼þÃû³Æ	£º	PX2CurveEditWindow.cpp
*
*/

#include "PX2CurveEditWindow.hpp"
#include "PX2DlgSetCurveVal.hpp"
#include "PX2EditSystem.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2UIManager.hpp"
using namespace PX2Editor;
using namespace PX2;

#define ID_CURVEEDIT_TIMER 6001
#define ID_CURVEEDIT_FITHORZ 6002
#define ID_CURVEEDIT_FITVERT 6003
#define ID_CURVEEDIT_FITALL 6004
#define ID_CURVEEDIT_FITSELECTED 6005
#define ID_CURVEEDIT_PAN 6006
#define ID_CURVEEDIT_ZOOM 6007
#define ID_CURVEEDIT_AUTO 6008
#define ID_CURVEEDIT_AUTO_CLAMPED 6009
#define ID_CURVEEDIT_USER 6010
#define ID_CURVEEDIT_BREAK 6011
#define ID_CURVEEDIT_LINEAR 6012
#define ID_CURVEEDIT_CONSTANT 6013
#define ID_CURVEEDIT_FLATTEN_TANGENTS_TO_AXIS 6014
#define ID_CURVEEDIT_STRAIGHTEN_TANGENTS 6015
#define ID_SETINVAL 6016
#define ID_SETOUTVAL 6017
#define ID_DELETE 6018
#define ID_DELETEUICURVEGROUP 6019
#define ID_DELETEALLUICURVEGROUP 6020

BEGIN_EVENT_TABLE(CurveEditWindow, wxWindow)
	EVT_SIZE(CurveEditWindow::OnSize)
	EVT_PAINT(CurveEditWindow::OnPaint)
	EVT_TIMER(ID_CURVEEDIT_TIMER, CurveEditWindow::OnTimer)
	EVT_ENTER_WINDOW(CurveEditWindow::OnEnterWindow)
	EVT_LEAVE_WINDOW(CurveEditWindow::OnLeaveWindow)
	EVT_PAINT(CurveEditWindow::OnPaint)
	EVT_LEFT_DOWN(CurveEditWindow::OnLeftDown)
	EVT_LEFT_DCLICK(CurveEditWindow::OnLeftDoubleClick)
	EVT_LEFT_UP(CurveEditWindow::OnLeftUp)
	EVT_MIDDLE_DOWN(CurveEditWindow::OnMiddleDown)
	EVT_MIDDLE_UP(CurveEditWindow::OnMiddleUp)
	EVT_MOUSEWHEEL(CurveEditWindow::OnMouseWheel)
	EVT_RIGHT_DOWN(CurveEditWindow::OnRightDown)
	EVT_RIGHT_UP(CurveEditWindow::OnRightUp)
	EVT_MOTION(CurveEditWindow::OnMotion)
	EVT_MENU(ID_CURVEEDIT_FITHORZ, CurveEditWindow::OnFitHor)
	EVT_MENU(ID_CURVEEDIT_FITVERT, CurveEditWindow::OnFitVer)
	EVT_MENU(ID_CURVEEDIT_FITALL, CurveEditWindow::OnFitAll)
	EVT_MENU(ID_CURVEEDIT_FITSELECTED, CurveEditWindow::OnFitSelect)
	EVT_MENU(ID_CURVEEDIT_PAN, CurveEditWindow::OnPan)
	EVT_MENU(ID_CURVEEDIT_ZOOM, CurveEditWindow::OnZoom)
	EVT_MENU_RANGE(ID_CURVEEDIT_AUTO, ID_CURVEEDIT_CONSTANT, CurveEditWindow::OnChangeInterpMode)
	EVT_MENU(ID_CURVEEDIT_FLATTEN_TANGENTS_TO_AXIS, CurveEditWindow::OnFattenTangentsToAxis)
	EVT_MENU(ID_CURVEEDIT_STRAIGHTEN_TANGENTS, CurveEditWindow::OnStraightenTangents)
	EVT_MENU(ID_SETINVAL, CurveEditWindow::OnSetInVal)
	EVT_MENU(ID_SETOUTVAL, CurveEditWindow::OnSetOutVal)
	EVT_MENU(ID_DELETE, CurveEditWindow::OnDelete)
	EVT_MENU(ID_DELETEUICURVEGROUP, CurveEditWindow::OnDeleteUICurveGroup)
	EVT_MENU(ID_DELETEALLUICURVEGROUP, CurveEditWindow::OnDeleteAllUICurveGroup)
END_EVENT_TABLE()

CurveEditWindow::CurveEditWindow (wxWindow *parent)
:
wxWindow(parent, wxID_ANY),
	mInited(false),
	mActive(false),
	mRenderer(0),
	mUPerGrid(10.0f),
	mVPerGrid(10.0f),
	mLeftDown(false),
	mLeftDownOnMotion(false),
	mMiddleDown(false),
	mRightDown(false),
	mRightDownOnMotion(false),
	mPixelOverCamIn(1.0f),
	mPixelOverCamOut(1.0f),
	mXStart(0.0f),
	mXEnd(0.0f),
	mZStart(0.0f),
	mZEnd(0.0f),
	mLeftWidth(122),
	mRightDownRMax(10.0f),
	mRightDownUMax(10.0f),
	mMoveMode(MM_PAN)
{
	wxBoxSizer* sizer0;
	sizer0 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* sizer00;
	sizer00 = new wxBoxSizer( wxVERTICAL );

	sizer0->Add(sizer00, 0, wxEXPAND, 5 );

	mToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, 
		wxSize( -1,12 ), wxTB_FLAT|wxTB_HORIZONTAL ); 

	mToolBar->AddTool(ID_CURVEEDIT_FITHORZ,
		wxBitmap(wxT("ToolRes/icons/cur_FitHorz.png"), wxBITMAP_TYPE_PNG), 
		PX2_LM.GetValue("FitHorizontally"));
	mToolBar->AddTool(ID_CURVEEDIT_FITVERT, 
		wxBitmap(wxT("ToolRes/icons/cur_FitVert.png"), wxBITMAP_TYPE_PNG),
		PX2_LM.GetValue("FitVertically"));
	mToolBar->AddTool(ID_CURVEEDIT_FITALL, 
		wxBitmap(wxT("ToolRes/icons/cur_FitViewToAll.png"), wxBITMAP_TYPE_PNG), 
		PX2_LM.GetValue("FitAll"));
	mToolBar->AddTool(ID_CURVEEDIT_FITSELECTED, 
		wxBitmap(wxT("ToolRes/icons/cur_FitViewToSelected.png"), wxBITMAP_TYPE_PNG),
		PX2_LM.GetValue("FitSelected"));
	mToolBar->AddSeparator();
	mToolBar->AddTool(ID_CURVEEDIT_PAN, 
		wxBitmap(wxT("ToolRes/icons/cur_Pan.png"), wxBITMAP_TYPE_PNG),
		wxBitmap(wxT("ToolRes/icons/cur_Pan.png"), wxBITMAP_TYPE_PNG),
		true,
		0,
		PX2_LM.GetValue("PanMode"));
	mToolBar->ToggleTool(ID_CURVEEDIT_PAN, true);
	mToolBar->AddTool(ID_CURVEEDIT_ZOOM,
		wxBitmap(wxT("ToolRes/icons/cur_Zoom.png"), wxBITMAP_TYPE_PNG),
		wxBitmap(wxT("ToolRes/icons/cur_Zoom.png"), wxBITMAP_TYPE_PNG),
		true,
		0,
		PX2_LM.GetValue("ZoomMode"));
	mToolBar->AddSeparator();
	mToolBar->AddTool(ID_CURVEEDIT_AUTO,
		wxBitmap(wxT("ToolRes/icons/cur_ModeAuto.png"), wxBITMAP_TYPE_PNG),
		wxBitmap(wxT("ToolRes/icons/cur_ModeAuto_dis.png"), wxBITMAP_TYPE_PNG),
		true,
		0,
		PX2_LM.GetValue("CurveAuto"));
	mToolBar->AddTool(ID_CURVEEDIT_AUTO_CLAMPED,
		wxBitmap(wxT("ToolRes/icons/cur_ModeAutoClamped.png"), wxBITMAP_TYPE_PNG),
		wxBitmap(wxT("ToolRes/icons/cur_ModeAutoClamped_dis.png"), wxBITMAP_TYPE_PNG),
		true,
		0,
		PX2_LM.GetValue("CurveAutoClamped"));
	mToolBar->AddTool(ID_CURVEEDIT_USER,
		wxBitmap(wxT("ToolRes/icons/cur_ModeUser.png"), wxBITMAP_TYPE_PNG),
		wxBitmap(wxT("ToolRes/icons/cur_ModeUser_dis.png"), wxBITMAP_TYPE_PNG),
		true,
		0,
		PX2_LM.GetValue("CurveUser"));
	mToolBar->AddTool(ID_CURVEEDIT_BREAK,
		wxBitmap(wxT("ToolRes/icons/cur_ModeBreak.png"), wxBITMAP_TYPE_PNG),
		wxBitmap(wxT("ToolRes/icons/cur_ModeBreak_dis.png"), wxBITMAP_TYPE_PNG),
		true,
		0,
		PX2_LM.GetValue("CurveBreak"));
	mToolBar->AddTool(ID_CURVEEDIT_LINEAR,
		wxBitmap(wxT("ToolRes/icons/cur_ModeLinear.png"), wxBITMAP_TYPE_PNG),
		wxBitmap(wxT("ToolRes/icons/cur_ModeLinear_dis.png"), wxBITMAP_TYPE_PNG),
		true,
		0,
		PX2_LM.GetValue("CurveLinear"));
	mToolBar->AddTool(ID_CURVEEDIT_CONSTANT,
		wxBitmap(wxT("ToolRes/icons/cur_ModeConstant.png"), wxBITMAP_TYPE_PNG),
		wxBitmap(wxT("ToolRes/icons/cur_ModeConstant_dis.png"), wxBITMAP_TYPE_PNG),
		true,
		0,
		PX2_LM.GetValue("CurveConstant"));
	mToolBar->AddSeparator();
	mToolBar->AddTool(ID_CURVEEDIT_FLATTEN_TANGENTS_TO_AXIS,
		wxBitmap(wxT("ToolRes/icons/cur_FlattenTangentsToAxis.png"), wxBITMAP_TYPE_PNG),
		wxBitmap(wxT("ToolRes/icons/cur_FlattenTangentsToAxis_dis.png"), wxBITMAP_TYPE_PNG),
		false,
		0,
		PX2_LM.GetValue("TangentsToAxis"));
	mToolBar->AddTool(ID_CURVEEDIT_STRAIGHTEN_TANGENTS,
		wxBitmap(wxT("ToolRes/icons/cur_StraightenTangents.png"), wxBITMAP_TYPE_PNG),
		wxBitmap(wxT("ToolRes/icons/cur_StraightenTangents_dis.png"), wxBITMAP_TYPE_PNG),
		false,
		0,
		PX2_LM.GetValue("StraightenTangents"));

	mToolBar->Realize(); 
	sizer00->Add(mToolBar, 0, wxEXPAND, 5);

	EnableInterps(false);

	Initlize();

	SetSizer(sizer0);
	Layout();
}
//----------------------------------------------------------------------------
CurveEditWindow::~CurveEditWindow ()
{
	if (mEditMenu)
	{
		delete mEditMenu;
		mEditMenu = 0;
	}

	if (mEditCurveGroupMenu)
	{
		delete mEditCurveGroupMenu;
		mEditCurveGroupMenu = 0;
	}

	if (mRenderer)
	{
		delete0(mRenderer);
		mRenderer = 0;
	}
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnSize(wxSizeEvent& e)
{
	if (!mInited)
		return;

	wxSize sz = e.GetSize();
	mWidth = sz.GetX();
	mHeight = sz.GetY();

	if (mWidth <= 0.0f)
		return;

	if (!mGridPoly)
	{
		VertexBuffer *vBuffer = new0 VertexBuffer(1024, mVFormat->GetStride(), Buffer::BU_DYNAMIC);
		mGridPoly = new0 Polysegment(mVFormat, vBuffer, false);
		VertexColor4Material *mtl = new0 VertexColor4Material();
		mGridPoly->SetMaterialInstance(mtl->CreateInstance());
		mScene->AttachChild(mGridPoly);
	}
	UIView *view = UIManager::GetSingleton().GetUIView("CurveEditWindow");
	if (view)
	{
		view->SetSize(Sizef((float)mWidth, (float)mHeight));
	}
	RefreshGrid(mRenderer, true);

	mToolBar->SetSize(wxSize(mWidth, 12));
	mRenderer->ResizeWindow(mWidth, mHeight);
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnPaint(wxPaintEvent& e)
{
	wxPaintDC dc(this);
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnEnterWindow(wxMouseEvent& e)
{
	mActive = true;
	mLeftDown = false;
	mRightDown = false;
	mMiddleDown = false;
	mRightDownOnMotion = false;
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnLeaveWindow(wxMouseEvent& e)
{
	mActive = false;
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnTimer (wxTimerEvent& event)
{
	if (!mInited)
		return;

	double timeInSeconds = GetTimeInSeconds();

	if (mScene)
	{
		mScene->Update(timeInSeconds);
	}

	UIView *view = UIManager::GetSingleton().GetUIView("CurveEditWindow");
	if (view)
	{
		view->Update(timeInSeconds, 0.0f);
		view->ComputeVisibleSet();
	}

	DrawScene();
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnLeftDown (wxMouseEvent& e)
{
	SetFocus();
	mLeftDown = true;
	mLeftDownOnMotion = false;

	wxPoint mousePos = e.GetPosition();

	wxRect rect(0, 0, mLeftWidth, mHeight);
	bool leftContain = rect.Contains(mousePos);
	if (leftContain)
	{
		Event *ent = InputEventSpace::CreateEventX(InputEventSpace::TouchPressed);
		InputEventData data;
		data.MState.X.Absoulate = mousePos.x;
		data.MState.Y.Absoulate = mHeight - mousePos.y;
		data.TState.X = data.MState.X;
		data.TState.Y = data.MState.Y;
		data.ViewID = 2;
		ent->SetData<InputEventData>(data);
		EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
	}
	else
	{
		TrySelectCurveCtrlPoint(mousePos);
	}
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnLeftDoubleClick (wxMouseEvent& e)
{
	UICurveGroup *uiCurveGroup = EditSystem::GetSingleton().GetCurveEdit()
		->GetSelectedUICurveGroup();
	if (!uiCurveGroup)
		return;

	if (wxGetKeyState(WXK_CONTROL))
	{
		wxPoint mousePos = e.GetPosition();

		APoint camPos = mCamera->GetPosition();
		Vector2f camScreenPos = mRenderer->PointWorldToViewPort(camPos);
		float xDissCam = mousePos.x - camScreenPos.X();
		float zDissCam = (mHeight-mousePos.y) - camScreenPos.Y();
		float xDissCamReal = xDissCam / mPixelOverCamIn;
		float zDissCamReal = zDissCam / mPixelOverCamOut;
		APoint pointPos = camPos + AVector(xDissCamReal, 0.0f, zDissCamReal);

		CurveGroup *curveGroup = uiCurveGroup->GetCurveGroup();
		curveGroup->AddPoint(pointPos);
	}
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnLeftUp (wxMouseEvent& e)
{
	wxPoint mousePos = e.GetPosition();

	wxRect rect(0, 0, mLeftWidth, mHeight);
	bool leftContain = rect.Contains(mousePos);

	if (leftContain)
	{
		Event *ent = InputEventSpace::CreateEventX(InputEventSpace::TouchReleased);
		InputEventData data;
		data.MState.X.Absoulate = mousePos.x;
		data.MState.Y.Absoulate = mHeight - mousePos.y;
		data.TState.X = data.MState.X;
		data.TState.Y = data.MState.Y;
		data.ViewID = 2;
		ent->SetData<InputEventData>(data);
		EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
	}

	if (mLeftDownOnMotion)
	{
		CurveCtrl *ctrl = EditSystem::GetSingleton().GetCurveEdit()->GetSelectedCurveCtrl();

		if (ctrl)
		{
			Event *ent = EditorEventSpace::CreateEventX(
				EditorEventSpace::CurveChangedByEditor);
			ent->SetData<void*>(ctrl->GetCurve());
			EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
		}
	}

	mLeftDownOnMotion = false;
	mLeftDown = false;
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnMiddleDown (wxMouseEvent& e)
{
	SetFocus();
	mMiddleDown = true;
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnMiddleUp (wxMouseEvent& e)
{
	mMiddleDown = false;
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnMouseWheel (wxMouseEvent& e)
{
	float delta = (float)(e.GetWheelRotation());

	float val = 1.2f * Mathf::Sign(delta);

	ZoomCamera(val, val);
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnRightDown (wxMouseEvent& e)
{
	SetFocus();
	mRightDown = true;
	mRightDownMousePoint = e.GetPosition();

	float dMin = 0.0f;
	float dMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float rMin = 0.0f;
	float rMax = 0.0f;
	mCamera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);

	mRightDownRMax = rMax;
	mRightDownUMax = uMax;
	mLastMousePoint = mRightDownMousePoint;
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnRightUp (wxMouseEvent& e)
{
	wxPoint mousePos = e.GetPosition();
	mLastMousePoint = mousePos;

	if (!mRightDownOnMotion)
	{
		wxRect rect(0, 0, mLeftWidth, mHeight);
		if (!rect.Contains(mousePos))
		{
			CurveCtrl *ctrl = EditSystem::GetSingleton().GetCurveEdit()
				->GetSelectedCurveCtrl();

			if (mEditMenu && ctrl)
			{
				bool isForInit = ctrl->GetCurve()->IsForInit();
				mEditMenu->Enable(ID_SETINVAL, !isForInit);

				PopupMenu(mEditMenu, mousePos.x, mousePos.y);
			}
		}
		else
		{
			UICurveGroup *uiCruveGroup = EditSystem::GetSingleton().GetCurveEdit()
				->GetSelectedUICurveGroup();

			if (mEditCurveGroupMenu && uiCruveGroup)
			{
				PopupMenu(mEditCurveGroupMenu, mousePos.x, mousePos.y);
			}
		}
	}

	mRightDownOnMotion = false;
	mRightDown = false;
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnMotion (wxMouseEvent& e)
{
	if (!mInited)
		return;

	if (mLeftDown)
		mLeftDownOnMotion = true;
	else
		mLeftDownOnMotion = false;

	if (mRightDown)
		mRightDownOnMotion = true;
	else
		mRightDownOnMotion = false;

	wxPoint point = e.GetPosition();
	wxPoint diff = point - mLastMousePoint;
	float movedX = -diff.x/mPixelOverCamIn;
	float movedZ = diff.y/mPixelOverCamOut;
	wxRect rect(0, 0, mLeftWidth, mHeight);
	bool leftContain = rect.Contains(point);

	if (mLeftDown && !leftContain)
	{
		CurveCtrl *selectedCtrl = EditSystem::GetSingleton().GetCurveEdit()
			->GetSelectedCurveCtrl();

		if (wxGetKeyState(WXK_CONTROL) && selectedCtrl)
		{
			bool isForInit = selectedCtrl->GetCurve()->IsForInit();

			APoint outVal = selectedCtrl->GetOutVal();
			Vector2f pos = mRenderer->PointWorldToViewPort(outVal);
			float xDiss = point.x - pos.X();
			float zDiss = (mHeight-point.y) - pos.Y();
			float xDissReal = xDiss / mPixelOverCamIn;
			float zDissReal = zDiss / mPixelOverCamOut;

			AVector arrive = AVector(-xDissReal, 0.0f, -zDissReal);
			arrive.Normalize();
			AVector leave = AVector(xDissReal, 0.0f, zDissReal);
			leave.Normalize();

			if (CurveCtrl::SM_ARRIVE == selectedCtrl->GetSelectMode())
			{
				if (xDiss < 0.0f)
				{
					selectedCtrl->SetArriveTangent(arrive);

					InterpCurveMode mode = selectedCtrl->GetInterpCurveMode();
					if (ICM_CURVE_AUTO==mode || ICM_CURVE_AUTOCLAMPED==mode)
					{
						selectedCtrl->SetInterpCurveMode(ICM_CURVE_USER);
						UnToggleAllInterps();
						ToggleInterp(ICM_CURVE_USER);
					}
				}
			}
			else if (CurveCtrl::SM_LEAVE == selectedCtrl->GetSelectMode())
			{
				if (xDiss > 0.0f)
				{
					selectedCtrl->SetLeaveTangent(leave);

					InterpCurveMode mode = selectedCtrl->GetInterpCurveMode();
					if (ICM_CURVE_AUTO==mode || ICM_CURVE_AUTOCLAMPED==mode)
					{
						selectedCtrl->SetInterpCurveMode(ICM_CURVE_USER);
						UnToggleAllInterps();
						ToggleInterp(ICM_CURVE_USER);
					}
				}
			}
			else if (CurveCtrl::SM_CENTER == selectedCtrl->GetSelectMode())
			{
				APoint camPos = mCamera->GetPosition();
				Vector2f camScreenPos = mRenderer->PointWorldToViewPort(camPos);
				float xDissCam = point.x - camScreenPos.X();
				float zDissCam = (mHeight-point.y) - camScreenPos.Y();
				float xDissCamReal = xDissCam / mPixelOverCamIn;
				float zDissCamReal = zDissCam / mPixelOverCamOut;
				APoint pointPos = camPos + AVector(xDissCamReal, 0.0f, zDissCamReal);
				pointPos.Y() = 0.0f;

				if (isForInit)
					pointPos.X() = 0.0f;

				selectedCtrl->SetInVal(pointPos.X()); // ctrl may changed

				selectedCtrl = EditSystem::GetSingleton().GetCurveEdit()
					->GetSelectedCurveCtrl(); // ctrl may changed, can it again
				if (selectedCtrl)
					selectedCtrl->SetOutVal(pointPos);
			}
		}
	}
	
	if (mRightDown && !leftContain)
	{
		if (MM_PAN == mMoveMode)
		{
			APoint pos = mCamera->GetPosition();
			pos += AVector(movedX, 0.0f, movedZ);
			mCamera->SetPosition(pos);

			RefreshGrid(mRenderer, false);
		}
		else if (MM_ZOOM == mMoveMode)
		{
			wxPoint pos = e.GetPosition();
			float xDetal = (float)(pos.x - mRightDownMousePoint.x);
			float zDetal = (float)(pos.y - mRightDownMousePoint.y);

			float rTo = mRightDownRMax;
			float uTo = mRightDownUMax;

			if (xDetal > 0.0f)
			{
				rTo = mRightDownRMax * (1.0f+xDetal/100.0f);
			}
			else
			{
				rTo = mRightDownRMax / (1.0f-xDetal/100.0f);
			}

			if (zDetal < 0.0f)
			{
				uTo = mRightDownUMax * (1.0f-zDetal/100.0f);
			}
			else
			{
				uTo = mRightDownUMax / (1.0f+zDetal/100.0f);
			}

			ZoomCameraTo(rTo, uTo);

			RefreshGrid(mRenderer, true);
		}
	}

	mLastMousePoint = point;
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnFitHor (wxCommandEvent &e)
{
	FitViewHorizontally();
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnFitVer (wxCommandEvent &e)
{
	FitViewVertically();
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnFitAll (wxCommandEvent &e)
{
	FitViewToAll();
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnFitSelect (wxCommandEvent &e)
{
	FitViewToSelected();
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnPan (wxCommandEvent &e)
{
	mMoveMode = MM_PAN;

	mToolBar->ToggleTool(ID_CURVEEDIT_PAN, true);
	mToolBar->ToggleTool(ID_CURVEEDIT_ZOOM, false);
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnZoom (wxCommandEvent &e)
{
	mMoveMode = MM_ZOOM;

	mToolBar->ToggleTool(ID_CURVEEDIT_PAN, false);
	mToolBar->ToggleTool(ID_CURVEEDIT_ZOOM, true);
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnChangeInterpMode (wxCommandEvent &e)
{
	CurveCtrl *ctrl = EditSystem::GetSingleton().GetCurveEdit()
		->GetSelectedCurveCtrl();

	if (!ctrl)
		return;
	
	mToolBar->ToggleTool(ID_CURVEEDIT_AUTO, false);
	mToolBar->ToggleTool(ID_CURVEEDIT_AUTO_CLAMPED, false);
	mToolBar->ToggleTool(ID_CURVEEDIT_USER, false);
	mToolBar->ToggleTool(ID_CURVEEDIT_BREAK, false);
	mToolBar->ToggleTool(ID_CURVEEDIT_LINEAR, false);
	mToolBar->ToggleTool(ID_CURVEEDIT_CONSTANT, false);

	InterpCurveMode mode = ICM_MAX_MODE;

	if (ID_CURVEEDIT_AUTO == e.GetId())
	{
		mode = ICM_CURVE_AUTO;
	}
	else if (ID_CURVEEDIT_AUTO_CLAMPED == e.GetId())
	{
		mode = ICM_CURVE_AUTOCLAMPED;
	}
	else if (ID_CURVEEDIT_USER == e.GetId())
	{
		mode = ICM_CURVE_USER;
	}
	else if (ID_CURVEEDIT_BREAK == e.GetId())
	{
		mode = ICM_CURVE_BREAK;
	}
	else if (ID_CURVEEDIT_LINEAR == e.GetId())
	{
		mode = ICM_LINEAR;
	}
	else if (ID_CURVEEDIT_CONSTANT == e.GetId())
	{
		mode = ICM_CONSTANT;
	}
	else
	{
		assertion(false, "OnChangeInterpMode id error.\n");
	}

	mToolBar->ToggleTool(e.GetId(), true);

	ctrl->SetInterpCurveMode(mode);
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnFattenTangentsToAxis (wxCommandEvent &e)
{
	CurveCtrl *ctrl = EditSystem::GetSingleton().GetCurveEdit()
		->GetSelectedCurveCtrl();
	if (!ctrl)
		return;

	InterpCurveMode mode = ctrl->GetInterpCurveMode();
	if (ICM_CURVE_AUTO==mode || ICM_CURVE_AUTOCLAMPED==mode)
	{
		ctrl->SetInterpCurveMode(ICM_CURVE_USER);
		ToggleInterp(ICM_CURVE_USER);
	}
	ctrl->SetArriveTangent(AVector::UNIT_X);
	ctrl->SetLeaveTangent(AVector::UNIT_X);
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnStraightenTangents (wxCommandEvent &e)
{
	CurveCtrl *ctrl = EditSystem::GetSingleton().GetCurveEdit()
		->GetSelectedCurveCtrl();
	if (!ctrl)
		return;

	const AVector &at = ctrl->GetArriveTangent();
	const AVector &lt = ctrl->GetLeaveTangent();
	AVector half = (at + lt)*0.5f;

	InterpCurveMode mode = ctrl->GetInterpCurveMode();
	if (ICM_CURVE_AUTO==mode || ICM_CURVE_AUTOCLAMPED==mode)
	{
		ctrl->SetInterpCurveMode(ICM_CURVE_USER);
		ToggleInterp(ICM_CURVE_USER);
	}

	ctrl->SetArriveTangent(half);
	ctrl->SetLeaveTangent(half);
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnSetInVal (wxCommandEvent &e)
{
	CurveCtrl *ctrl = EditSystem::GetSingleton().GetCurveEdit()
		->GetSelectedCurveCtrl();
	if (!ctrl)
		return;

	DlgSetCurveVal dlg(this);
	dlg.SetVal(ctrl->GetInVal());
	dlg.SetTitle(PX2_LM.GetValue("SetInVal"));
	dlg.SetLabel(PX2_LM.GetValue("NewInVal"));
	if (dlg.ShowModal() == wxID_OK)
	{
		float val = dlg.GetVal();
		ctrl->SetInVal(val);
	}
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnSetOutVal (wxCommandEvent &e)
{
	CurveCtrl *ctrl = EditSystem::GetSingleton().GetCurveEdit()
		->GetSelectedCurveCtrl();
	if (!ctrl)
		return;

	DlgSetCurveVal dlg(this);
	dlg.SetVal(ctrl->GetOutVal().Z());
	dlg.SetTitle(PX2_LM.GetValue("SetOutVal"));
	dlg.SetLabel(PX2_LM.GetValue("NewOutVal"));
	if (dlg.ShowModal() == wxID_OK)
	{
		float val = dlg.GetVal();

		APoint outVal = ctrl->GetOutVal();
		outVal.Z() = val;
		ctrl->SetOutVal(outVal);
	}
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnDelete (wxCommandEvent &e)
{
	CurveCtrl *ctrl = EditSystem::GetSingleton().GetCurveEdit()
		->GetSelectedCurveCtrl();
	if (ctrl)
	{
		CurveGroup *group = EditSystem::GetSingleton().GetCurveEdit()
			->GetCurveGroup(ctrl->GetCurve());
		group->DeletePoint(ctrl->GetIndex());
	}
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnDeleteUICurveGroup (wxCommandEvent &e)
{
	UICurveGroup *group = EditSystem::GetSingleton().GetCurveEdit()
		->GetSelectedUICurveGroup();

	if (group)
	{
		EditSystem::GetSingleton().GetCurveEdit()->SetSelectedUICurveGroup(0);
		EditSystem::GetSingleton().GetCurveEdit()->ClearGroup(group);
	}
}
//----------------------------------------------------------------------------
void CurveEditWindow::OnDeleteAllUICurveGroup (wxCommandEvent &e)
{
	EditSystem::GetSingleton().GetCurveEdit()->ClearAllGroups();
	EditSystem::GetSingleton().GetCurveEdit()->SetSelectedUICurveGroup(0);
}
//----------------------------------------------------------------------------
void CurveEditWindow::DoEnter ()
{
}
//----------------------------------------------------------------------------
void CurveEditWindow::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::CurveChangedByGrid))
	{
		EffectModule *module = event->GetData<EffectModule*>();
		EditSystem::GetSingleton().GetCurveEdit()->UpdateCurve(module);

		CurveCtrl *ctrl = EditSystem::GetSingleton().GetCurveEdit()
			->GetSelectedCurveCtrl();
		if (ctrl)
		{
			ToggleInterp(ctrl->GetInterpCurveMode());
		}
	}
}
//----------------------------------------------------------------------------
void CurveEditWindow::DoLeave ()
{
}
//----------------------------------------------------------------------------
void CurveEditWindow::Initlize ()
{
	mWidth = 200;
	mHeight = 150;
	mColorFormat = Texture::TF_A8R8G8B8;
	mDepthStencilFormat = Texture::TF_D24S8;
	mNumMultisamples = 0;

	HWND hWnd = (HWND)(GetHandle());
	mInput.mWindowHandle = hWnd;
	mInput.mDriver = Direct3DCreate9(D3D_SDK_VERSION);
	assertion(mInput.mDriver != 0, "Failed to create Direct3D9\n");
	mRenderer = new0 Renderer(mInput, mWidth, mHeight, mColorFormat, 
		mDepthStencilFormat, mNumMultisamples);
	mBackGroundColor = Float4(0.4f, 0.4f, 0.4f, 0.0f);
	mRenderer->SetClearColor(mBackGroundColor);

	mCamera = ScreenTarget::CreateCamera();
	mRenderer->SetCamera(mCamera);
	mCuller.SetCamera(mCamera);
	mCamera->SetFrame(APoint(0.0f, -10.0f, 0.0f), AVector::UNIT_Y, AVector::UNIT_Z,
		AVector::UNIT_X);
	mCamera->SetFrustum(0.1f, 100.0f, -(float)mHeight, (float)mHeight,
		-(float)mWidth, (float)mWidth);
	float rWidth = 2.0f*mWidth;
	float scaleX = rWidth/22.5f;
	float scaleZ = scaleX * (mPixelOverCamIn/mPixelOverCamOut);
	EditSystem::GetSingleton().GetCurveEdit()->SetCtrlsScale(scaleX, scaleZ);

	// grid
	mVFormat = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT3, 0);
	mScene = new0 Node();
	mScene->AttachChild(EditSystem::GetSingleton().GetCurveEdit()
		->GetCurveEditorScene());

	mEditMenu = new wxMenu();
	mEditMenu->Append(ID_SETINVAL, PX2_LM.GetValue("SetInVal"));
	mEditMenu->Append(ID_SETOUTVAL, PX2_LM.GetValue("SetOutVal"));
	mEditMenu->AppendSeparator();
	mEditMenu->Append(ID_DELETE, PX2_LM.GetValue("Delete"));

	mEditCurveGroupMenu = new wxMenu();
	mEditCurveGroupMenu->Append(ID_DELETEUICURVEGROUP, PX2_LM.GetValue("Delete"));
	mEditCurveGroupMenu->Append(ID_DELETEALLUICURVEGROUP, PX2_LM.GetValue("DeleteAll"));

	mTimer.SetOwner(this, ID_CURVEEDIT_TIMER);
	mTimer.Start(20);

	UIViewPtr view = new0 UIView(2);
	UIManager::GetSingleton().AddUIView("CurveEditWindow", view);
	mEditorUI = new0 UIFrame();
	view->SetMainFrame(mEditorUI);
	view->SetRenderer(mRenderer);

	mInited = true;
}
//----------------------------------------------------------------------------
void CurveEditWindow::DrawScene ()
{
	if (!mInited)
		return;

	if (mScene)
	{
		mCuller.ComputeVisibleSet(mScene);
	}

	if (mRenderer->PreDraw())
	{
		// draw right
		mRenderer->SetClearColor(mBackGroundColor);
		mRenderer->ClearBuffers();

		mRenderer->Draw(mCuller.GetVisibleSet());

		for (int i=0; i<(int)mFontStrs.size(); i++)
		{
			mRenderer->Draw(mFontStrs[i].x, mFontStrs[i].y, Float4::WHITE, 
				mFontStrs[i].str);
		}

		// draw left
		mRenderer->SetClearColor(Float4::BLACK);
		mRenderer->ClearBuffers(0, 0, mLeftWidth, mHeight+1);
		mRenderer->SetClearColor(Float4(0.6f, 0.6f, 0.6f, 1.0f));
		mRenderer->ClearColorBuffer(0, 1, mLeftWidth-1, mHeight+1);

		// draw ui
		UIView *view = UIManager::GetSingleton().GetUIView("CurveEditWindow");
		if (view)
		{
			CameraPtr cameraPre = mRenderer->GetCamera();
			mRenderer->SetCamera(view->GetCamera());
			Culler &uiCuller = view->GetCuller();
			mRenderer->Draw(uiCuller.GetVisibleSet());
			mRenderer->SetCamera(cameraPre);
		}

		mRenderer->PostDraw();
		mRenderer->DisplayColorBuffer();
	}
}
//----------------------------------------------------------------------------
void CurveEditWindow::ZoomCamera (float xDetal, float zDetal)
{
	float dMin = 0.0f;
	float dMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float rMin = 0.0f;
	float rMax = 0.0f;
	mCamera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	float uMaxTemp = uMax;
	float rMaxTemp = rMax;

	if (xDetal > 0.0f)
	{
		rMaxTemp *= xDetal;
	}
	else
	{
		rMaxTemp /= -xDetal;
	}

	if (zDetal > 0.0f)
	{
		uMaxTemp *= zDetal;
	}
	else
	{
		uMaxTemp /= -zDetal;
	}

	if (uMaxTemp > 0.0f)
	{
		uMax = uMaxTemp;
	}
	if (rMaxTemp > 0.0f)
	{
		rMax = rMaxTemp;
	}

	uMin = -uMax;
	rMin = -rMax;
	mCamera->SetFrustum(0.1f, 100.0f, uMin, uMax, rMin, rMax);

	RefreshGrid(mRenderer, true);
}
//----------------------------------------------------------------------------
void CurveEditWindow::ZoomCameraTo (float xMax, float zMax)
{
	if (xMax <= 0.0f || zMax<=0.0f)
	{
		return;
	}

	float dMin = 0.0f;
	float dMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float rMin = 0.0f;
	float rMax = 0.0f;
	mCamera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);

	rMax = xMax;
	rMin = -rMax;
	uMax = zMax;
	uMin = -uMax;	
	mCamera->SetFrustum(0.1f, 100.0f, uMin, uMax, rMin, rMax);

	RefreshGrid(mRenderer, true);
}
//----------------------------------------------------------------------------
float GetGridSpacing(int gridNum)
{
	if(gridNum & 0x01) // Odd numbers
	{
		return Mathf::Pow(10.f, 0.5f*((float)(gridNum-1)) + 1.f );
	}
	else // Even numbers
	{
		return 0.5f * Mathf::Pow( 10.f, 0.5f*((float)(gridNum)) + 1.f );
	}
}
//----------------------------------------------------------------------------
void CurveEditWindow::RefreshGrid (PX2::Renderer *renderer, bool doScale)
{
	if (!mGridPoly)
		return;

	// wx
	wxSize sz = GetSize();
	float width = (float)sz.GetWidth();
	float height = (float)sz.GetHeight();

	if (width<=0.0f && height<=0.0f)
		return;

	// px
	APoint pos = mCamera->GetPosition();
	float dMin = 0.0f;
	float dMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float rMin = 0.0f;
	float rMax = 0.0f;
	mCamera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);

	if (0.0f==rMax || 0.0f==uMax || 0.0f==dMax)
		return;

	float inLength = rMax - rMin;
	float outLength = uMax - uMin;

	mPixelOverCamIn = mWidth/inLength;
	mPixelOverCamOut = mHeight/outLength;

	int minPixelsPerInGrid = 35;
	int minPixelsPerOutGrid = 25;
	float minGridSpacing = 0.001f;

	int gridNum = 0;
	float inGridSpacing = minGridSpacing;
	while (inGridSpacing*mPixelOverCamIn < minPixelsPerInGrid )
	{
		inGridSpacing = minGridSpacing * GetGridSpacing(gridNum);
		gridNum++;
	}
	mUPerGrid = inGridSpacing;

	gridNum = 0;
	float outGridSpacing = minGridSpacing;
	while (outGridSpacing*mPixelOverCamOut < minPixelsPerOutGrid )
	{
		outGridSpacing = minGridSpacing * GetGridSpacing(gridNum);
		gridNum++;
	}
	mVPerGrid = outGridSpacing;

	mXStart = pos.X() + rMin;
	mXEnd = pos.X() + rMax;
	mZStart = pos.Z() + uMin;
	mZEnd = pos.Z() + uMax;

	Float3 gray(0.62f, 0.62f, 0.62f);
	int segNum = 0;
	mFontStrs.clear();
	VertexBufferAccessor vba(mGridPoly);

	float zPosTemp = 0.0f;
	while (zPosTemp < mZEnd)
	{
		zPosTemp += mVPerGrid;

		vba.Position<Float3>(2*segNum) = Float3(mXStart, 1.0f, zPosTemp);
		vba.Color<Float3>(0, 2*segNum) = gray;
		vba.Position<Float3>(2*segNum+1) = Float3(mXEnd, 1.0f, zPosTemp);
		vba.Color<Float3>(0, 2*segNum+1) = gray;

		Vector2f scrv = mRenderer->PointWorldToViewPort(APoint(0.0f, 0.0f,
			zPosTemp));
		FontStr fs;
		fs.x = (int)scrv.X();
		fs.y = mHeight - (int)scrv.Y();
		fs.str = StringHelp::FloatToString(zPosTemp);
		mFontStrs.push_back(fs);

		segNum++;
	}
	zPosTemp = 0.0f;
	while (zPosTemp > mZStart)
	{
		zPosTemp -= mVPerGrid;

		vba.Position<Float3>(2*segNum) = Float3(mXStart, 1.0f, zPosTemp);
		vba.Color<Float3>(0, 2*segNum) = gray;
		vba.Position<Float3>(2*segNum+1) = Float3(mXEnd, 1.0f, zPosTemp);
		vba.Color<Float3>(0, 2*segNum+1) = gray;

		Vector2f scrv = mRenderer->PointWorldToViewPort(APoint(0.0f, 0.0f,
			zPosTemp));
		FontStr fs;
		fs.x = (int)scrv.X();
		fs.y = mHeight - (int)scrv.Y();
		fs.str = StringHelp::FloatToString(zPosTemp);
		mFontStrs.push_back(fs);

		segNum++;
	}
	float xPosTemp = 0.0f;
	while (xPosTemp < mXEnd)
	{
		xPosTemp += mUPerGrid;

		vba.Position<Float3>(2*segNum) = Float3(xPosTemp, 1.0f, mZStart);
		vba.Color<Float3>(0, 2*segNum) = gray;
		vba.Position<Float3>(2*segNum+1) = Float3(xPosTemp, 1.0f, mZEnd);
		vba.Color<Float3>(0, 2*segNum+1) = gray;

		Vector2f scrv = mRenderer->PointWorldToViewPort(APoint(xPosTemp, 0.0f,
			0.0f));
		FontStr fs;
		fs.x = (int)scrv.X();
		fs.y = mHeight - (int)scrv.Y();
		fs.str = StringHelp::FloatToString(xPosTemp);
		mFontStrs.push_back(fs);

		segNum++;
	}
	xPosTemp = 0.0f;
	while (xPosTemp > mXStart)
	{
		xPosTemp -= mUPerGrid;

		vba.Position<Float3>(2*segNum) = Float3(xPosTemp, 1.0f, mZStart);
		vba.Color<Float3>(0, 2*segNum) = gray;
		vba.Position<Float3>(2*segNum+1) = Float3(xPosTemp, 1.0f, mZEnd);
		vba.Color<Float3>(0, 2*segNum+1) = gray;

		Vector2f scrv = mRenderer->PointWorldToViewPort(APoint(xPosTemp, 0.0f,
			0.0f));
		FontStr fs;
		fs.x = (int)scrv.X();
		fs.y = mHeight - (int)scrv.Y();
		fs.str = StringHelp::FloatToString(xPosTemp);
		mFontStrs.push_back(fs);

		segNum++;
	}

	vba.Position<Float3>(2*segNum) = Float3(mXStart, 1.0f, 0.0f);
	vba.Color<Float3>(0, 2*segNum) = Float3::WHITE;
	vba.Position<Float3>(2*segNum+1) = Float3(mXEnd, 1.0f, 0.0f);
	vba.Color<Float3>(0, 2*segNum+1) = Float3::WHITE;
	segNum++;
	vba.Position<Float3>(2*segNum) = Float3(0.0f, 1.0f, mZStart);
	vba.Color<Float3>(0, 2*segNum) = Float3::WHITE;
	vba.Position<Float3>(2*segNum+1) = Float3(0.0f, 1.0f, mZEnd);
	vba.Color<Float3>(0, 2*segNum+1) = Float3::WHITE;
	segNum++;

	Vector2f scrv = mRenderer->PointWorldToViewPort(APoint::ORIGIN);
	FontStr fs;
	fs.x = (int)scrv.X();
	fs.y = mHeight - (int)scrv.Y();
	fs.str = "0";
	mFontStrs.push_back(fs);

	mGridPoly->SetNumSegments(segNum);

	mGridPoly->UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);
	renderer->Update(mGridPoly->GetVertexBuffer());

	if (doScale)
	{
		float rWidth = 2.0f * rMax;
		float scaleX = rWidth/22.5f;

		float uHeight = 2.0f * uMax;
		float scaleZ = uHeight/(((float)mHeight/(float)mWidth)*22.5f);
		EditSystem::GetSingleton().GetCurveEdit()->SetCtrlsScale(scaleX, scaleZ);
	}
}
//----------------------------------------------------------------------------
void CurveEditWindow::FitViewHorizontally()
{
	float inMin = Mathf::MAX_REAL;
	float inMax = -Mathf::MAX_REAL;
	EditSystem::GetSingleton().GetCurveEdit()->GetInRange(inMin, inMax);

	float inLength = inMax - inMin;
	bool inLenghtZero = false;
	if (inLength == 0.0f)
	{
		inLength = 10.0f;
		inLenghtZero = true;
	}

	float rightWidth = (float)mWidth - mLeftWidth;
	float leftOverWidth = (float)mLeftWidth/(float)mWidth;
	float allOverRight = (float)mWidth/rightWidth;
	inLength *= allOverRight;

	float dMin = 0.0f;
	float dMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float rMin = 0.0f;
	float rMax = 0.0f;
	mCamera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	rMax = inLength/2.0f * 1.5f;
	rMin = -rMax;
	mCamera->SetFrustum(0.1f, 100.0f, uMin, uMax, rMin, rMax);

	APoint pos = mCamera->GetPosition();

	if (inLenghtZero)
	{
		pos.X() = inMin;
	}
	else
	{
		pos.X() = inMin+inLength/2.0f-inLength*leftOverWidth;
	}

	mCamera->SetPosition(pos);

	RefreshGrid(mRenderer, true);
}
//----------------------------------------------------------------------------
void CurveEditWindow::FitViewVertically()
{
	float outMin = Mathf::MAX_REAL;
	float outMax = -Mathf::MAX_REAL;
	EditSystem::GetSingleton().GetCurveEdit()->GetOutRange(outMin, outMax);

	float outLength = outMax - outMin;
	bool outLenghtZero = false;
	if (outLength == 0.0f)
	{
		outLength = 10.0f;
		outLenghtZero = true;
	}

	float dMin = 0.0f;
	float dMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float rMin = 0.0f;
	float rMax = 0.0f;
	mCamera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	uMax = outLength/2.0f * 1.5f;
	uMin = -uMax;
	mCamera->SetFrustum(0.1f, 100.0f, uMin, uMax, rMin, rMax);

	APoint pos = mCamera->GetPosition();

	if (outLenghtZero)
	{
		pos.Z() = outMin;
	}
	else
	{
		pos.Z() = outMin+outLength/2.0f;
	}

	mCamera->SetPosition(pos);

	RefreshGrid(mRenderer, true);
}
//----------------------------------------------------------------------------
void CurveEditWindow::FitViewToSelected()
{
	CurveCtrl *ctrl = 
		EditSystem::GetSingleton().GetCurveEdit()->GetSelectedCurveCtrl();

	if (!ctrl)
		return;

	float inMin = Mathf::MAX_REAL;
	float inMax = -Mathf::MAX_REAL;
	EditSystem::GetSingleton().GetCurveEdit()->GetInRange(inMin, inMax);

	float outMin = Mathf::MAX_REAL;
	float outMax = -Mathf::MAX_REAL;
	EditSystem::GetSingleton().GetCurveEdit()->GetOutRange(outMin, outMax);

	float inLength = inMax - inMin;
	float outLength = outMax - outMin;

	if (inLength == 0.0f)
	{
		inLength = 10.0f;
	}
	if (outLength == 0.0f)
	{
		outLength = 10.0f;
	}

	float rightWidth = (float)mWidth - mLeftWidth;
	float leftOverWidth = (float)mLeftWidth/(float)mWidth;
	float allOverRight = (float)mWidth/rightWidth;
	inLength *= allOverRight;

	float dMin = 0.0f;
	float dMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float rMin = 0.0f;
	float rMax = 0.0f;
	mCamera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	rMax = inLength/2.0f * 1.5f;
	rMin = -rMax;
	uMax = outLength/2.0f * 1.5f;
	uMin = -uMax;
	mCamera->SetFrustum(0.1f, 100.0f, uMin, uMax, rMin, rMax);

	APoint camPos = mCamera->GetPosition();
	APoint ctrPos = ctrl->GetOutVal();
	camPos.X() = ctrPos.X();
	camPos.Z() = ctrPos.Z();
	mCamera->SetPosition(camPos);

	RefreshGrid(mRenderer, true);
}
//----------------------------------------------------------------------------
void CurveEditWindow::FitViewToAll()
{
	FitViewHorizontally();
	FitViewVertically();
}
//----------------------------------------------------------------------------
void CurveEditWindow::EnableInterps (bool enable)
{
	mToolBar->EnableTool(ID_CURVEEDIT_AUTO, enable);
	mToolBar->EnableTool(ID_CURVEEDIT_AUTO_CLAMPED, enable);
	mToolBar->EnableTool(ID_CURVEEDIT_USER, enable);
	mToolBar->EnableTool(ID_CURVEEDIT_BREAK, enable);
	mToolBar->EnableTool(ID_CURVEEDIT_LINEAR, enable);
	mToolBar->EnableTool(ID_CURVEEDIT_CONSTANT, enable);

	mToolBar->EnableTool(ID_CURVEEDIT_FLATTEN_TANGENTS_TO_AXIS, enable);
	mToolBar->EnableTool(ID_CURVEEDIT_STRAIGHTEN_TANGENTS, enable);

}
//----------------------------------------------------------------------------
void CurveEditWindow::UnToggleAllInterps ()
{
	mToolBar->ToggleTool(ID_CURVEEDIT_AUTO, false);
	mToolBar->ToggleTool(ID_CURVEEDIT_AUTO_CLAMPED, false);
	mToolBar->ToggleTool(ID_CURVEEDIT_USER, false);
	mToolBar->ToggleTool(ID_CURVEEDIT_BREAK, false);
	mToolBar->ToggleTool(ID_CURVEEDIT_LINEAR, false);
	mToolBar->ToggleTool(ID_CURVEEDIT_CONSTANT, false);
}
//----------------------------------------------------------------------------
void CurveEditWindow::TrySelectCurveCtrlPoint (const wxPoint &pos)
{
	APoint origin = APoint::ORIGIN;
	AVector direction = AVector::UNIT_Y;
	mRenderer->GetPickRay(pos.x, mHeight-pos.y, origin, direction);

	Picker picker;
	picker.Execute(mScene, origin, direction, 0.0f, Mathf::MAX_REAL);

	if ((int)(picker.Records.size()) > 0)
	{
		Movable *mov = picker.GetClosestNonnegative().Intersected;

		CurveCtrl *ctrl = 
			EditSystem::GetSingleton().GetCurveEdit()->TrySelectCurve(mov);

		if (ctrl)
		{
			UnToggleAllInterps();
			EnableInterps(true);
			ToggleInterp(ctrl->GetInterpCurveMode());

			EditSystem::GetSingleton().GetCurveEdit()
				->SetSelectedCurveCtrl(ctrl);
		}
	}
	else
	{
		UnToggleAllInterps();
		EnableInterps(false);

		EditSystem::GetSingleton().GetCurveEdit()->SetSelectedCurveCtrl(0);
	}
}
//----------------------------------------------------------------------------
void CurveEditWindow::ToggleInterp (InterpCurveMode mode)
{
	if (mode == ICM_CURVE_AUTO)
	{
		mToolBar->ToggleTool(ID_CURVEEDIT_AUTO, true);
	}
	else if (mode == ICM_CURVE_AUTOCLAMPED)
	{
		mToolBar->ToggleTool(ID_CURVEEDIT_AUTO_CLAMPED, true);
	}
	else if (mode == ICM_CURVE_USER)
	{
		mToolBar->ToggleTool(ID_CURVEEDIT_USER, true);
	}
	else if (mode == ICM_CURVE_BREAK)
	{
		mToolBar->ToggleTool(ID_CURVEEDIT_BREAK, true);
	}
	else if (mode == ICM_LINEAR)
	{
		mToolBar->ToggleTool(ID_CURVEEDIT_LINEAR, true);
	}
	else if (mode == ICM_CONSTANT)
	{
		mToolBar->ToggleTool(ID_CURVEEDIT_CONSTANT, true);
	}
}
//----------------------------------------------------------------------------