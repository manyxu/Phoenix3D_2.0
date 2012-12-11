/*
*
* 文件名称	：	PX2RenderViewWindow.cpp
*
*/

#include "PX2RenderViewWindow.hpp"
#include "PX2EditorParams.hpp"
#include "PX2ViewCtrlInstMan.hpp"
#include "PX2EditEventType.hpp"
using namespace PX2Editor;
using namespace PX2;

#define ID_CTRLTIMER wxID_HIGHEST+3001
#define ID_RENDERTIMER wxID_HIGHEST+3002
#define ID_ADDACTOR_MODEL wxID_HIGHEST + 3101
#define ID_ADDACTOR_EFFECT wxID_HIGHEST + 3102
#define ID_ADDACTOR_LIGHT_AMBIENT wxID_HIGHEST +3103
#define ID_ADDACTOR_LIGHT_DIRECTION wxID_HIGHEST + 3104
#define ID_ADDACTOR_LIGHT_POINT wxID_HIGHEST + 3105
#define ID_ADDACTOR_LIGHT_SPOT wxID_HIGHEST + 3106
#define ID_ADDACTOR_SOUND wxID_HIGHEST + 3107
#define ID_ADDACTOR_TRIGER wxID_HIGHEST + 3108
#define ID_CREATE_BOX wxID_HIGHEST + 3109
#define ID_CREATE_SPHERE wxID_HIGHEST + 3110
#define ID_CLONE_INSTANCE wxID_HIGHEST + 3111
#define ID_CLONE_DATA wxID_HIGHEST + 3112
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
EVT_MENU(ID_ADDACTOR_MODEL, RenderViewWindow::OnActorModel)
EVT_MENU(ID_ADDACTOR_LIGHT_DIRECTION, RenderViewWindow::OnActorLight_Direction)
EVT_MENU(ID_ADDACTOR_LIGHT_POINT, RenderViewWindow::OnActorLight_Point)
EVT_MENU(ID_ADDACTOR_LIGHT_SPOT, RenderViewWindow::OnActorLight_Spot)
EVT_MENU(ID_CREATE_BOX, RenderViewWindow::OnCreateBox)
EVT_MENU(ID_CREATE_SPHERE, RenderViewWindow::OnCreateSphere)
EVT_MENU(ID_CLONE_INSTANCE, RenderViewWindow::OnCloneShare)
EVT_MENU(ID_CLONE_DATA, RenderViewWindow::OnCloneData)
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
	mRightDownOnMotion(false),
	mEditMenu(0)
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
	mRightDownOnMotion(false),
	mEditMenu(0)
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
	if (mEditMenu)
	{
		delete mEditMenu;
		mEditMenu = 0;
	}

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
	mCtrlScene = new0 Node();
	mCtrlScene->AttachChild(mSceneNodeCtrl->GetCtrlsGroup());
	mCtrlScene->Update();

	SetViewType(VT_PERSPECTIVE);

	CreateEditMenu();

	EditSystem::GetSingleton().GetEditMap()->GetScene()->GetDefaultCameraActor()
		->SetCamera(mCamera);
	SetScene(EditSystem::GetSingleton().GetEditMap()->GetScene()
		->GetSceneNode());
	SetHelpScene(EditSystem::GetSingleton().GetHelpScene());

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
	mCtrlCuller.SetCamera(mCamera);
	mCuller.SetCamera(mCamera);
	mHelpCuller.SetCamera(mCamera);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnTimer (wxTimerEvent& event)
{
	if (!mInited)
		return;

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
		EditSystem::EditMode editMode = EditSystem::GetSingleton().GetEditMode();
		if (editMode == EditSystem::EM_SELECT
			|| editMode == EditSystem::EM_TRANSLATE
			|| editMode == EditSystem::EM_ROLATE
			|| editMode == EditSystem::EM_SCALE)
		{
			if (mEditMenu)
				this->PopupMenu(mEditMenu, popupPos.x, popupPos.y);
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
void RenderViewWindow::OnActorModel (wxCommandEvent& e)
{
	APoint pos = ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->GetSelectPoint();
	Object *obj = EditSystem::GetSingleton().GetSelectedResource();
	Movable *mov = DynamicCast<Movable>(obj);
	if (mov)
	{
		EditSystem::GetSingleton().GetEditMap()->AddModelActor(mov, pos);
	}
	else
	{
		wxMessageBox(PX2_LM.GetValue("Tip1"), PX2_LM.GetValue("Tip0"), wxOK);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnActorLight_Direction (wxCommandEvent& e)
{

}
//----------------------------------------------------------------------------
void RenderViewWindow::OnActorLight_Point (wxCommandEvent& e)
{

}
//----------------------------------------------------------------------------
void RenderViewWindow::OnActorLight_Spot (wxCommandEvent& e)
{

}
//----------------------------------------------------------------------------
void RenderViewWindow::OnCreateBox (wxCommandEvent& e)
{
	APoint pos = ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->GetSelectPoint();
	EditSystem::GetSingleton().GetEditMap()->CreateBox(pos);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnCreateSphere (wxCommandEvent& e)
{
	APoint pos = ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->GetSelectPoint();
	EditSystem::GetSingleton().GetEditMap()->CreateSphere(pos);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnCloneShare (wxCommandEvent& e)
{
	Actor *actor = EditSystem::GetSingleton().GetSelection()->GetActor(0);
	if (actor)
	{
		APoint pos = ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
			->GetSelectPoint();
		EditSystem::GetSingleton().GetEditMap()->CloneShare(actor, pos);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnCloneData (wxCommandEvent& e)
{
	Actor *actor = EditSystem::GetSingleton().GetSelection()->GetActor(0);
	if (actor)
	{
		APoint pos = ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
			->GetSelectPoint();
		EditSystem::GetSingleton().GetEditMap()->CloneData(actor, pos);
	}
	else
	{

	}
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
void RenderViewWindow::Update (double detalSeconds)
{
	if (!mInited)
		return;

	CamMoveUpdate(detalSeconds);

	if (mCtrlScene)
		mCtrlScene->Update();
}
//----------------------------------------------------------------------------
void RenderViewWindow::CamMoveUpdate (double detalSeconds)
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
	bool ctrlDown = wxGetKeyState(WXK_CONTROL);
	bool shiftDown = wxGetKeyState(WXK_SHIFT);
	bool wDown = wxGetKeyState((wxKeyCode)(_T('W')));
	bool sDown = wxGetKeyState((wxKeyCode)(_T('S')));
	bool aDown = wxGetKeyState((wxKeyCode)(_T('A')));
	bool dDown = wxGetKeyState((wxKeyCode)(_T('D')));

	if (ctrlDown)
		return;

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
		curSpeedTemp -= (float)detalSeconds * (speedParam0 + speedParam1*(float)detalSeconds);
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
		curSpeedTemp -= (float)detalSeconds * (speedParam0 + speedParam1*(float)detalSeconds);
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
		curSpeedTemp -= (float)detalSeconds * (speedParam0 + speedParam1*(float)detalSeconds);
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
		curSpeedTemp -= (float)detalSeconds * (speedParam0 + speedParam1*(float)detalSeconds);
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
	float moveValue_W = mCurCameraMoveSpeed_W * (float)detalSeconds;
	float moveValue_S = mCurCameraMoveSpeed_S * (float)detalSeconds;
	float moveValue_A = mCurCameraMoveSpeed_A * (float)detalSeconds;
	float moveValue_D = mCurCameraMoveSpeed_D * (float)detalSeconds;

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

	if (mCtrlScene)
	{
		mCtrlCuller.ComputeVisibleSet(mCtrlScene);
	}

	if (mHelpScene)
	{
		mHelpCuller.ComputeVisibleSet(mHelpScene);
	}

	if (mScene)
	{
		mCuller.ComputeVisibleSet(mScene);
		mCuller.ComputeEnvironment();
	}

	if (mRenderer->PreDraw())
	{
		mRenderer->ClearBuffers();

		mRenderer->Draw(mGridCuller.GetVisibleSet());

		mRenderer->Draw(mCuller.GetVisibleSet());

		mRenderer->ClearDepthBuffer();
		mRenderer->Draw(mHelpCuller.GetVisibleSet());
		mRenderer->Draw(mCtrlCuller.GetVisibleSet().Sort());

		mRenderer->PostDraw();

		mRenderer->DisplayColorBuffer();
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::CreateEditMenu ()
{
	mEditMenu = new wxMenu();

	//--
	wxMenu *createMenu = new wxMenu();
	mEditMenu->AppendSubMenu(createMenu, PX2_LM.GetValue("Create"));

	createMenu->Append(ID_CREATE_BOX, PX2_LM.GetValue("Box"));
	createMenu->Append(ID_CREATE_SPHERE, PX2_LM.GetValue("Sphere"));

	//--
	wxMenu *addActorMenu = new wxMenu();
	mEditMenu->AppendSubMenu(addActorMenu, PX2_LM.GetValue("AddActor"));

	addActorMenu->Append(ID_ADDACTOR_MODEL, PX2_LM.GetValue("AddActorModel"));
	addActorMenu->Append(ID_ADDACTOR_EFFECT,PX2_LM.GetValue("AddActorEffect"));

	wxMenu *addActorMenu_Light = new wxMenu();
	addActorMenu->AppendSubMenu(addActorMenu_Light, PX2_LM.GetValue("AddActorLight"));
	addActorMenu_Light->Append(ID_ADDACTOR_LIGHT_POINT, PX2_LM.GetValue("AddActorLightPoint"));
	addActorMenu_Light->Append(ID_ADDACTOR_LIGHT_SPOT, PX2_LM.GetValue("AddActorLightSpot"));

	//--
	wxMenu *cloneMenu = new wxMenu();
	cloneMenu->Append(ID_CLONE_INSTANCE, PX2_LM.GetValue("CloneInstance"));
	cloneMenu->Append(ID_CLONE_DATA, PX2_LM.GetValue("CloneData"));
	mEditMenu->AppendSubMenu(cloneMenu, PX2_LM.GetValue("Clone"));
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
void RenderViewWindow::DoEnter ()
{
}
//----------------------------------------------------------------------------
void RenderViewWindow::DoExecute (PX2::Event *event)
{
	if (!mInited)
		return;

	if (EditorEventSpace::IsEqual(event, EditorEventSpace::NewScene)
		|| EditorEventSpace::IsEqual(event, EditorEventSpace::LoadedScene))
	{
		Scene *scene = EditSystem::GetSingleton().GetEditMap()->GetScene();
		if (scene)
		{
			SetScene(scene->GetSceneNode());
			scene->GetDefaultCameraActor()->SetCamera(mCamera);
		}

		Movable *helpScene = EditSystem::GetSingleton().GetHelpScene();
		if (helpScene)
		{
			SetHelpScene(helpScene);
		}
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::SetEditMode))
	{
		PX2Editor::EditSystem::EditMode mode = 
			event->GetData<PX2Editor::EditSystem::EditMode>();

		if (mode == PX2Editor::EditSystem::EM_SELECT)
			mSceneNodeCtrl->SetCtrlType(SceneNodeCtrl::CT_SELECT);
		if (mode == PX2Editor::EditSystem::EM_TRANSLATE)
			mSceneNodeCtrl->SetCtrlType(SceneNodeCtrl::CT_TRANSLATE);
		else if (mode == PX2Editor::EditSystem::EM_ROLATE)
			mSceneNodeCtrl->SetCtrlType(SceneNodeCtrl::CT_ROLATE);
		else if (mode == PX2Editor::EditSystem::EM_SCALE)
			mSceneNodeCtrl->SetCtrlType(SceneNodeCtrl::CT_SCALE);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::SceneNodeDrag))
	{
		int drag = event->GetData<int>();
		if (1 == drag)
		{
			SetCursor(wxCursor(wxCURSOR_SIZING));
		}
		else if (0 == drag)
		{
			SetCursor(wxCursor(wxCURSOR_ARROW));
		}
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::DoLeave ()
{
}
//----------------------------------------------------------------------------