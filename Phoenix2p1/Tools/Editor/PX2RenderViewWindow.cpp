/*
*
* 文件名称	：	PX2RenderViewWindow.cpp
*
*/

#include "PX2RenderViewWindow.hpp"
#include "PX2EditorParams.hpp"
#include "PX2ViewCtrlInstMan.hpp"
using namespace PX2Editor;
using namespace PX2;

#define ID_CTRLTIMER wxID_HIGHEST+3001
#define ID_RENDERTIMER wxID_HIGHEST+3002
//----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC_CLASS(PX2Editor::RenderViewWindow, wxWindow)
BEGIN_EVENT_TABLE(RenderViewWindow, wxWindow)
EVT_TIMER(ID_CTRLTIMER, RenderViewWindow::OnTimer)
EVT_TIMER(ID_RENDERTIMER, RenderViewWindow::OnTimer)
EVT_SIZE(RenderViewWindow::OnSize)
EVT_PAINT(RenderViewWindow::OnPaint)
EVT_LEFT_DOWN(RenderViewWindow::OnLeftDown)
EVT_LEFT_UP(RenderViewWindow::OnLeftUp)
EVT_MIDDLE_DOWN(RenderViewWindow::OnMiddleDown)
EVT_MIDDLE_UP(RenderViewWindow::OnMiddleUp)
EVT_MOUSEWHEEL(RenderViewWindow::OnMouseWheel)
EVT_RIGHT_DOWN(RenderViewWindow::OnRightDown)
EVT_RIGHT_UP(RenderViewWindow::OnRightUp)
EVT_MOTION(RenderViewWindow::OnMotion)
EVT_ENTER_WINDOW(RenderViewWindow::OnEnterWindow)
EVT_LEAVE_WINDOW(RenderViewWindow::OnLeaveWindow)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
RenderViewWindow::RenderViewWindow ()
	:wxWindow(NULL, -1),
	mViewType(VT_PERSPECTIVE),
	mViewDetail(VD_TEXTURED),
	mWidth(0),
	mHeight(0),
	mRenderer(0),
	mRenderMilliseconds(25),
	mCtrlMilliseconds(15),
	mCameraMoveSpeed(20.0f),
	mCurCameraMoveSpeed_W(0.0f),
	mCurCameraMoveSpeed_S(0.0f),
	mCurCameraMoveSpeed_A(0.0f),
	mCurCameraMoveSpeed_D(0.0f),
	mInited(false),
	mSceneNodeCtrl(0),
	mActive(false),
	mLeftDown(false),
	mMiddleDown(false),
	mRightDown(false),
	mRightDownOnMotion(false)
{
}
//----------------------------------------------------------------------------
RenderViewWindow::RenderViewWindow (wxWindow *parent)
	:wxWindow(parent, -1),
	mViewType(VT_PERSPECTIVE),
	mViewDetail(VD_TEXTURED),
	mWidth(0),
	mHeight(0),
	mRenderer(0),
	mRenderMilliseconds(25),
	mCtrlMilliseconds(15),
	mCameraMoveSpeed(20.0f),
	mCurCameraMoveSpeed_W(0.0f),
	mCurCameraMoveSpeed_S(0.0f),
	mCurCameraMoveSpeed_A(0.0f),
	mCurCameraMoveSpeed_D(0.0f),
	mInited(false),
	mSceneNodeCtrl(0),
	mActive(false),
	mLeftDown(false),
	mMiddleDown(false),
	mRightDown(false),
	mRightDownOnMotion(false)
{
	mBlack = Float4(0.0f, 0.0f, 0.0f, 1.0f);
	mRed = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	mGreen = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	mBlue = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	mGray = Float4(0.43f, 0.43f, 0.43f, 1.0f);
}
//----------------------------------------------------------------------------
RenderViewWindow::~RenderViewWindow ()
{
	if (mSceneNodeCtrl)
	{
		delete0(mSceneNodeCtrl);
		mSceneNodeCtrl = 0;
	}

	if (mRenderer)
	{
		delete0(mRenderer);
		mRenderer = 0;
		mRendererInput.mDriver->Release();
	}
}
//----------------------------------------------------------------------------
bool RenderViewWindow::Initlize ()
{
	SetAxisPerspective();

	mWidth = 800;
	mHeight = 600;
	mColorFormat = Texture::TF_A8R8G8B8;
	mDepthStencilFormat = Texture::TF_D24S8;
	mNumMultisamples = 2;

	HWND hWnd = (HWND)(this->GetHandle());
	mRendererInput.mWindowHandle = hWnd;
	mRendererInput.mDriver = Direct3DCreate9(D3D_SDK_VERSION);
	assertion(mRendererInput.mDriver != 0, "Failed to create Direct3D9\n");
	mRenderer = new0 Renderer(mRendererInput, mWidth, mHeight,
		mColorFormat, mDepthStencilFormat, mNumMultisamples);
	mRenderer->SetCamera(mCamera);
	mBackGroundColor = Float4(0.6f, 0.5f, 0.5f, 0.0f);
	mRenderer->SetClearColor(mBackGroundColor);

	mRenderTimer.SetOwner(this, ID_RENDERTIMER);
	mRenderTimer.Start(mRenderMilliseconds);

	mCtrlTimer.SetOwner(this, ID_CTRLTIMER);
	mCtrlTimer.Start(mCtrlMilliseconds);

	mOverWriteDepth = new0 DepthProperty();
	mOverWriteDepth->Enabled = false;
	mOverWriteDepth->Writable = false;

	mSceneNodeCtrl = new0 SceneNodeCtrl();
	EventWorld::GetSingleton().ComeIn(mSceneNodeCtrl);

	SetViewType(VT_PERSPECTIVE);

	mInited = true;

	return mInited;
}
//----------------------------------------------------------------------------
void RenderViewWindow::SetViewType (ViewType viewType)
{
	mViewType = viewType;

	mSceneNodeCtrl->SetLookType((SceneNodeCtrl::LookType)viewType);

	switch (mViewType)
	{
	case VT_LEFT:
		break;
	case VT_TOP:
		break;
	case VT_FRONT:
		break;
	case VT_PERSPECTIVE:
		SetAxisPerspective();
		break;
	}

	CreateGridGeometry();

	mRenderer->SetCamera(mCamera);
	mGridCuller.SetCamera(mCamera);
	mCuller.SetCamera(mCamera);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnTimer (wxTimerEvent& event)
{
	int ival = event.GetInterval();
	double dIval = ival/1000.0;

	if (ID_CTRLTIMER == event.GetId())
	{
		Update(dIval);
	}
	else if (ID_RENDERTIMER == event.GetId())
	{
		DrawScene();
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnSize (wxSizeEvent& e)
{
	if (!mInited)
		return;

	wxSize sz = GetClientSize();
	mWidth = sz.GetX();
	mHeight = sz.GetY();
	mRenderer->ResizeWindow(sz.x, sz.y);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnPaint(wxPaintEvent& e)
{
	wxPaintDC dc(this);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnEnterWindow(wxMouseEvent& e)
{
	SetFocus();

	mActive = true;
	mLeftDown = false;
	mRightDown = false;
	mMiddleDown = false;
	mRightDownOnMotion = false;
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnLeaveWindow(wxMouseEvent& e)
{
	mActive = false;
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnLeftDown (wxMouseEvent& e)
{
	if (!mInited)
		return;

	mLeftDown = true;

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->HandleLeftDown(this, e);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnLeftUp (wxMouseEvent& e)
{
	if (!mInited)
		return;

	mLeftDown = false;

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->HandleLeftUp(this, e);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnMiddleDown (wxMouseEvent& e)
{
	if (!mInited)
		return;

	mMiddleDown = true;

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->HandleMiddleDown(this, e);	
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnMiddleUp (wxMouseEvent& e)
{
	if (!mInited)
		return;

	// 不要在此处处理
	// mMiddleDown = false;

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->HandleMiddleUp(this, e);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnMouseWheel (wxMouseEvent& e)
{
	if (!mInited)
		return;

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->HandleMouseWheel(this, e);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnRightDown (wxMouseEvent& e)
{
	if (!mInited)
		return;

	mRightDown = true;
	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->HandleRightDown(this, e);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnRightUp (wxMouseEvent& e)
{
	if (!mInited)
		return;

	wxPoint popupPos = wxGetMousePosition();
	popupPos = ScreenToClient(popupPos);

	wxRect rect(0, 0, 75, 20);
	if (rect.Contains(popupPos))
	{
	}
	else if (!mRightDownOnMotion)
	{
		if (EditSystem::GetSingleton().GetEditMode() == EditSystem::EM_SELECT)
		{
		}
	}

	mRightDownOnMotion = false;
	mRightDown = false;

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->HandleRightUp(this, e);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnMotion (wxMouseEvent& e)
{
	if (!mInited)
		return;

	if (mRightDown)
		mRightDownOnMotion = true;
	else
		mRightDownOnMotion = false;

	wxPoint point = e.GetPosition();
	wxPoint diff = point - mLastMousePoint;

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->HandleMotion(this, e);

	mLastMousePoint = point;
}
//----------------------------------------------------------------------------
std::pair<float, float> RenderViewWindow::StartMouseDrag(wxMouseEvent& e)
{
	std::pair<float, float> pixelToWorld;

	if (mViewType == VT_PERSPECTIVE)
	{
		float rMin = mCamera->GetRMin();
		float uMin = mCamera->GetUMin();
		float viewPortWidth = (float)mRenderer->GetWidth();
		float viewPortHeight = (float)mRenderer->GetHeight();

		float worldW = 2.0f * -rMin;
		float worldH = 2.0f * -uMin;

		worldW *= 10.0f;
		worldH *= 10.0f;

		pixelToWorld.first = worldW/(float)viewPortWidth;
		pixelToWorld.second = worldH/(float)viewPortHeight;
	}
	else
	{
		float rMin = mCamera->GetRMin();
		float uMin = mCamera->GetUMin();
		float viewPortWidth = (float)mRenderer->GetWidth();
		float viewPortHeight = (float)mRenderer->GetHeight();

		float worldW = 2.0f * -rMin;
		float worldH = 2.0f * -uMin;

		worldW *= 1.0f;
		worldH *= 1.0f;

		pixelToWorld.first = worldW/(float)viewPortWidth;
		pixelToWorld.second = worldH/(float)viewPortHeight;
	}

	return pixelToWorld;
}
//----------------------------------------------------------------------------
void RenderViewWindow::EndMouseDrag(wxMouseEvent& e)
{
}
//----------------------------------------------------------------------------
void RenderViewWindow::Update (double detalTime)
{
	if (!mInited)
		return;

	CamMoveUpdate(detalTime);
}
//----------------------------------------------------------------------------
void RenderViewWindow::CamMoveUpdate (double detalTime)
{
	if (!mActive)
	{
		mCurCameraMoveSpeed_W = 0.0f;
		mCurCameraMoveSpeed_S = 0.0f;
		mCurCameraMoveSpeed_A = 0.0f;
		mCurCameraMoveSpeed_D = 0.0f;
		return;
	}

	bool altDown = wxGetKeyState(WXK_ALT);
	bool shiftDown = wxGetKeyState(WXK_SHIFT);
	bool wDown = wxGetKeyState((wxKeyCode)(_T('W')));
	bool sDown = wxGetKeyState((wxKeyCode)(_T('S')));
	bool aDown = wxGetKeyState((wxKeyCode)(_T('A')));
	bool dDown = wxGetKeyState((wxKeyCode)(_T('D')));

	// cal move speed
	float speedParam0 = (mCameraMoveSpeed/0.2f);
	float speedParam1 = (mCameraMoveSpeed/0.1f);
	if (wDown)
	{
		mCurCameraMoveSpeed_W = mCameraMoveSpeed;
	}
	else
	{
		float curSpeedTemp = mCurCameraMoveSpeed_W;
		curSpeedTemp -= (float)detalTime * (speedParam0 + speedParam1*(float)detalTime);
		if (curSpeedTemp >= 0.0f)
		{
			mCurCameraMoveSpeed_W = curSpeedTemp;
		}
		else
		{
			mCurCameraMoveSpeed_W = 0.0f;
		}
	}

	if (sDown)
	{
		mCurCameraMoveSpeed_S = mCameraMoveSpeed;
	}
	else
	{
		float curSpeedTemp = mCurCameraMoveSpeed_S;
		curSpeedTemp -= (float)detalTime * (speedParam0 + speedParam1*(float)detalTime);
		if (curSpeedTemp > 0.0f)
		{
			mCurCameraMoveSpeed_S = curSpeedTemp;
		}
		else
		{
			mCurCameraMoveSpeed_S = 0.0f;
		}
	}

	if (aDown)
	{
		mCurCameraMoveSpeed_A = mCameraMoveSpeed;
	}
	else
	{
		float curSpeedTemp = mCurCameraMoveSpeed_A;
		curSpeedTemp -= (float)detalTime * (speedParam0 + speedParam1*(float)detalTime);
		if (curSpeedTemp > 0.0f)
		{
			mCurCameraMoveSpeed_A = curSpeedTemp;
		}
		else
		{
			mCurCameraMoveSpeed_A = 0.0f;
		}
	}

	if (dDown)
	{
		mCurCameraMoveSpeed_D = mCameraMoveSpeed;
	}
	else
	{
		float curSpeedTemp = mCurCameraMoveSpeed_D;
		curSpeedTemp -= (float)detalTime * (speedParam0 + speedParam1*(float)detalTime);
		if (curSpeedTemp > 0.0f)
		{
			mCurCameraMoveSpeed_D = curSpeedTemp;
		}
		else
		{
			mCurCameraMoveSpeed_D = 0.0f;
		}
	}

	// move
	float moveValue_W = mCurCameraMoveSpeed_W * (float)detalTime;
	float moveValue_S = mCurCameraMoveSpeed_S * (float)detalTime;
	float moveValue_A = mCurCameraMoveSpeed_A * (float)detalTime;
	float moveValue_D = mCurCameraMoveSpeed_D * (float)detalTime;

	if (shiftDown)
	{
		moveValue_W = moveValue_W * 2.0f;
		moveValue_S = moveValue_S * 2.0f;
		moveValue_A = moveValue_A * 2.0f;
		moveValue_D = moveValue_D * 2.0f;
	}

	float moveValueV = moveValue_W - moveValue_S;
	float moveValueH = moveValue_A - moveValue_D;

	if (altDown)
	{
		MoveCamera(0.0f, moveValueV);
	}
	else
	{
		ZoomCamera(moveValueV);
	}

	MoveCamera(moveValueH, 0.0f);
}
//----------------------------------------------------------------------------
void RenderViewWindow::DrawScene ()
{
	if (!mInited)
		return;

	if (mGridScene)
	{
		mGridCuller.ComputeVisibleSet(mGridScene);
	}

	if (mScene)
	{
		mCuller.ComputeVisibleSet(mScene);
	}

	if (mRenderer->PreDraw())
	{
		mRenderer->ClearBuffers();

		mRenderer->Draw(mGridCuller.GetVisibleSet());

		mRenderer->Draw(mCuller.GetVisibleSet());

		mRenderer->PostDraw();

		mRenderer->DisplayColorBuffer();
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::CreateGridGeometry ()
{
	float gridSize = EditorParams::GetSingleton().mGridSize;

	// Grid
	mGridVFormat = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT4, 0);

	StandardMesh sM(mGridVFormat);
	mGrid = sM.LineRectangleForEditor(81, 81, gridSize, gridSize, mGray);

	mVBGridAxis = new0 VertexBuffer(4, mGridVFormat->GetStride(), 
		Buffer::BU_DYNAMIC);
	mGridAxisAssessor.ApplyTo(mGridVFormat, mVBGridAxis);
	mGridAxisAssessor.Position<Float3>(0) = Float3(-gridSize, 0.0f, 0.0f);
	mGridAxisAssessor.Color<Float4>(0, 0) = mRed;
	mGridAxisAssessor.Position<Float3>(1) = Float3(gridSize, 0.0f, 0.0f);
	mGridAxisAssessor.Color<Float4>(0, 1) = mRed;
	mGridAxisAssessor.Position<Float3>(2) = Float3(0.0f, -gridSize, 0.0f);
	mGridAxisAssessor.Color<Float4>(0, 2) = mGreen;
	mGridAxisAssessor.Position<Float3>(3) = Float3(0.0f, gridSize, 0.0f);
	mGridAxisAssessor.Color<Float4>(0, 3) = mGreen;
	mGridAxis = new0 Polysegment(mGridVFormat, mVBGridAxis, false);

	mGrid->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	mGridAxis->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());

	mGridScene = new0 Node();
	mGridScene->AttachChild(mGridAxis);
	mGridScene->AttachChild(mGrid);
	mGridScene->Update();
}
//----------------------------------------------------------------------------
void RenderViewWindow::SetAxisPerspective ()
{
	mCamera = 0;
	mCamera = new Camera();
	mCamera->SetFrustum(1.0f, 1000.0f, -0.4125f, 0.4125f, -0.55f, 0.55f);
	APoint loc;
	AVector dir;
	AVector up;
	AVector right;
	loc = APoint::ORIGIN;
	loc.X() = -20.0f; loc.Y() = -20.0f; loc.Z() = 10.0f;
	dir.X() = -loc.X();
	dir.Y() = -loc.Y();
	dir.Z() = -loc.Z();
	dir.Normalize();
	up = AVector(Float3(0.0f, 0.0f, 1.0f));
	right = dir.Cross(up);
	right.Normalize();	
	up = right.Cross(dir);
	up.Normalize();

	AVector::Orthonormalize(dir, up, right);
	mCamera->SetFrame(loc, dir, up, right);
}
//----------------------------------------------------------------------------
void RenderViewWindow::ZoomCamera (float zoom)
{
	mSceneNodeCtrl->OnMouseWheel(mRenderer, zoom);

	Vector3f position = mCamera->GetPosition();
	AVector dir = mCamera->GetDVector();
	dir.Normalize();

	if (mViewType == VT_PERSPECTIVE)
	{
		position += dir*zoom;
		mCamera->SetPosition(position);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::PanCamera (const float &horz, const float &vert)
{
	Vector3f position = mCamera->GetPosition();
	AVector dVector = mCamera->GetDVector();
	AVector uVector = mCamera->GetUVector();
	AVector rVector = mCamera->GetRVector();

	if (mViewType == VT_PERSPECTIVE)
	{
		rVector.Normalize();
		position += rVector * horz * 5.0f;

		uVector.Normalize();
		position -= uVector * vert * 5.0f;

		mCamera->SetPosition(position);
	}
	else if (mViewType == VT_TOP)
	{
		position.Y() += vert * 1.0f;
		position.X() -= horz * 1.0f;

		mCamera->SetPosition(position);
	}
	else if (mViewType == VT_LEFT)
	{
		position.Z() += vert * 1.0f;
		position.Y() += horz * 1.0f;

		mCamera->SetPosition(position);
	}
	else if (mViewType == VT_FRONT)
	{
		position.Z() += vert * 1.0f;
		position.X() -= horz * 1.0f;

		mCamera->SetPosition(position);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::MoveCamera (const float &horz, const float vert)
{
	Vector3f position = mCamera->GetPosition();
	AVector dVector = mCamera->GetDVector();
	AVector uVector = mCamera->GetUVector();
	AVector rVector = mCamera->GetRVector();

	if (mViewType == VT_PERSPECTIVE)
	{
		dVector.Z() = 0.0f;
		dVector.Normalize();
		rVector.Z() = 0.0f;
		rVector.Normalize();
		position += dVector * vert;
		position -= rVector * horz;

		mCamera->SetPosition(position);
	}
	else if (mViewType == VT_TOP)
	{
		position.Y() += vert * 1.0f;
		position.X() -= horz * 1.0f;

		mCamera->SetPosition(position);
	}
	else if (mViewType == VT_LEFT)
	{
		position.Z() += vert * 1.0f;
		position.Y() += horz * 1.0f;

		mCamera->SetPosition(position);
	}
	else if (mViewType == VT_FRONT)
	{
		position.Z() += vert * 1.0f;
		position.X() -= horz * 1.0f;

		mCamera->SetPosition(position);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::RolateCamera (const float &horz, const float &vert)
{
	if (mViewType == VT_PERSPECTIVE)
	{
		AVector dVector = mCamera->GetDVector();
		AVector uVector = mCamera->GetUVector();
		AVector rVector = mCamera->GetRVector();

		// horz
		HMatrix incrH(AVector::UNIT_Z, -horz*0.5f);
		dVector = incrH * dVector;
		uVector = incrH * uVector;
		rVector = incrH * rVector;

		// vert
		Matrix3f kIncrV(rVector, -vert*0.5f);
		dVector = kIncrV * dVector;
		uVector = kIncrV * uVector;

		AVector::Orthonormalize(dVector, uVector, rVector);
		mCamera->SetAxes(dVector, uVector, rVector);

	}
}
//----------------------------------------------------------------------------