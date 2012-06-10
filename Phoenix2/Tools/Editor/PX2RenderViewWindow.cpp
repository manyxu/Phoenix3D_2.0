/*
*
* 文件名称	：	RenderViewWindow.cpp
*
*/

#include "wxFourWaySplitter.h"
#include "PX2RenderViewWindow.hpp"
#include "PX2ControllerManager.hpp"
#include "PX2ControllerInstance.hpp"
#include "PX2EditorOptions.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
std::string RenderViewWindow::ViewTypeString[RenderViewWindow::VT_MAX_TYPE] =
{
	"top",
	"front",
	"left",
	"perspective"
};
//-----------------------------------------------------------------------------

#define ID_TIMER wxID_HIGHEST+1000
#define ID_VIEWTYPE_TOP wxID_HIGHEST + 601
#define ID_VIEWTYPE_FRONT wxID_HIGHEST + 602
#define ID_VIEWTYPE_LEFT wxID_HIGHEST + 603
#define ID_VIEWTYPE_PERSPECTIVE wxID_HIGHEST + 604
#define ID_WIREFRAME wxID_HIGHEST + 605
#define ID_TEXTURE wxID_HIGHEST + 606
#define ID_FULLFOUR wxID_HIGHEST + 607
#define ID_STAGEGRID wxID_HIGHEST + 608

#define ID_ADDACTOR_MODEL wxID_HIGHEST + 701
#define ID_ADDACTOR_EFFECT wxID_HIGHEST + 702
#define ID_ADDACTOR_LIGHT_AMBIENT wxID_HIGHEST + 703
#define ID_ADDACTOR_LIGHT_DIRECTION wxID_HIGHEST + 704
#define ID_ADDACTOR_LIGHT_POINT wxID_HIGHEST + 705
#define ID_ADDACTOR_LIGHT_SPOT wxID_HIGHEST + 706
#define ID_ADDACTOR_SOUND wxID_HIGHEST + 707
#define ID_ADDACTOR_TRIGER wxID_HIGHEST + 708
#define ID_CLONE_INSTANCE wxID_HIGHEST + 709
#define ID_CLONE_DATA wxID_HIGHEST + 710

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC_CLASS(PX2Editor::RenderViewWindow, wxWindow)
BEGIN_EVENT_TABLE(RenderViewWindow, wxWindow)
	EVT_TIMER(ID_TIMER, RenderViewWindow::OnTimer)
	EVT_SIZE(RenderViewWindow::OnSize)
	EVT_MOVE(RenderViewWindow::OnMove)
	EVT_PAINT(RenderViewWindow::OnPaint)
	EVT_KEY_DOWN(RenderViewWindow::OnKeyDown)
	EVT_KEY_UP(RenderViewWindow::OnKeyUp)
	EVT_CHAR(RenderViewWindow::OnChar)
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
	EVT_MENU_RANGE(ID_VIEWTYPE_TOP, ID_VIEWTYPE_PERSPECTIVE, RenderViewWindow::OnViewTypeCommand)
	EVT_MENU(ID_WIREFRAME, RenderViewWindow::OnWireFrame)
	EVT_MENU(ID_TEXTURE, RenderViewWindow::OnTextured)
	EVT_MENU(ID_FULLFOUR, RenderViewWindow::OnFullFour)
	EVT_MENU(ID_STAGEGRID, RenderViewWindow::OnStageGrid)
	EVT_MENU(ID_ADDACTOR_MODEL, RenderViewWindow::OnActorModel)
	EVT_MENU(ID_ADDACTOR_LIGHT_AMBIENT, RenderViewWindow::OnActorLight_Ambient)
	EVT_MENU(ID_ADDACTOR_LIGHT_DIRECTION, RenderViewWindow::OnActorLight_Direction)
	EVT_MENU(ID_ADDACTOR_LIGHT_POINT, RenderViewWindow::OnActorLight_Point)
	EVT_MENU(ID_ADDACTOR_LIGHT_SPOT, RenderViewWindow::OnActorLight_Spot)
	EVT_MENU(ID_ADDACTOR_SOUND, RenderViewWindow::OnActorSound)
	EVT_MENU(ID_CLONE_INSTANCE, RenderViewWindow::OnCloneInstance)
	EVT_MENU(ID_CLONE_DATA, RenderViewWindow::OnCloneData)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
RenderViewWindow::RenderViewWindow()
:
wxWindow(NULL, -1),
mCamera(0),
mViewType(VT_PERSPECTIVE),
mExpanded(false),
mLeftDown(false),
mMiddleDown(false),
mRightDown(false),
mActive(false),
mInited(false),
mWindowIndex(-1),
mSceneNodeCtrl(0),
mViewChoice(0),
mToolbar(0),
mRightDownOnMotion(false),
mViewOptionsPopupMenu(0),
mEditMenu(0)
{
}	
//-----------------------------------------------------------------------------
RenderViewWindow::RenderViewWindow(wxWindow* parent)
:
wxWindow(parent, -1),
mCamera(0),
mViewType(VT_PERSPECTIVE),
mViewDetail(VD_WIREFRAME),
mExpanded(false),
mLeftDown(false),
mMiddleDown(false),
mRightDown(false),
mActive(false),
mInited(false),
mWindowIndex(-1),
mViewChoice(0),
mToolbar(0),
mShowGrid(true),
mRightDownOnMotion(false),
mViewOptionsPopupMenu(0),
mEditMenu(0)
{
	mBlack = Float4(0.0f, 0.0f, 0.0f, 1.0f);
	mRed = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	mGreen = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	mBlue = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	mGray = Float4(0.43f, 0.43f, 0.43f, 1.0f);

	//CreateToolbar();

	CreatePopupMenu();

	mTimer.SetOwner(this, ID_TIMER);
	mTimer.Start(20);

	mSceneNodeCtrl = new SceneNodeCtrl();
	EventWorld::GetSingleton().ComeIn(mSceneNodeCtrl);

	mOverrideWireProperty = new0 WireProperty();
	mOverrideWireProperty->Enabled = true;

	// Ctrl Scene
	mCtrlScene = new0 Node();
	mCtrlScene->AttachChild(mSceneNodeCtrl->GetCtrlsGroup());
	mOverWriteDepth = new0 DepthProperty();
	mOverWriteDepth->Enabled = false;
	mOverWriteDepth->Writable = false;
}
//-----------------------------------------------------------------------------
RenderViewWindow::~RenderViewWindow()
{
	if (mSceneNodeCtrl)
		delete mSceneNodeCtrl;

	mCamera = 0;

	mGridVFormat = 0;
	mGridScene = 0;
	mCtrlScene = 0;
	mGraphicsScene = 0;
	mHelpScene = 0;
	mGrid = 0;

//#ifdef PX2_USE_DX9
	delete0(mRenderer);
	mInput.mDriver->Release();
//#endif
}
//-----------------------------------------------------------------------------
void RenderViewWindow::CreateToolbar()
{
	//long style = wxTB_HORZ_LAYOUT|wxTB_HORZ_LAYOUT
	//	|wxTB_HORIZONTAL;
	//style &= ~wxTB_TEXT;
	//mToolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxSize(10,8),
	//	style);
	//mToolbar->SetWindowStyleFlag(style);

	//wxString m_choice5Choices[] = { _("Top"), _("Front"), _("Left"),
	//	_("Perspective") };

	//int m_choice5NChoices = sizeof( m_choice5Choices ) / sizeof( wxString );
	//mViewChoice = new wxChoice(mToolbar, wxID_ANY, wxDefaultPosition, wxSize(50,8), 
	//	m_choice5NChoices, m_choice5Choices, 0 );

	//mToolbar->SetToolBitmapSize(wxSize(16,8));
	//mToolbar->AddControl(mViewChoice);
	//mToolbar->AddSeparator();
	//mToolbar->AddTool(ID_CAMERA_SAVED1, _("Camera 1"), 
	//	wxBitmap( wxT("./ToolRes/Icons/bullet_green.png"), wxBITMAP_TYPE_PNG), 
	//	wxNullBitmap, wxITEM_NORMAL, 
	//	_("Camera 1"), wxEmptyString );
	//mToolbar->AddSeparator();
	//mToolbar->AddTool(ID_EXPAND, _("Expand"), 
	//	wxBitmap( wxT("./ToolRes/Icons/arrow_out.png"), wxBITMAP_TYPE_PNG), 
	//	wxNullBitmap, wxITEM_NORMAL, 
	//	_("Expand"), wxEmptyString); 
	//mToolbar->AddTool(ID_VIEW_OPTIONS, _("View Options"), 
	//	wxBitmap( wxT("./ToolRes/Icons/eye.png"), wxBITMAP_TYPE_PNG), 
	//	wxNullBitmap, wxITEM_NORMAL, 
	//	_("View Options"), wxEmptyString); 

	//mToolbar->SetSize(10, 10, wxDefaultCoord, 8);
	//mToolbar->SetMargins(1, 1);
	//mToolbar->SetRows(1);
	//mToolbar->Realize();


	//mViewChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED,
	//	wxCommandEventHandler(RenderViewWindow::OnViewChanged), 0, this);
}
//----------------------------------------------------------------------------
void RenderViewWindow::CreatePopupMenu()
{
	if (!mViewOptionsPopupMenu)
	{
		mViewOptionsPopupMenu = new wxMenu();
		mViewOptionsPopupMenu->Append(ID_VIEWTYPE_TOP, _("Top"));
		mViewOptionsPopupMenu->Append(ID_VIEWTYPE_FRONT, _("Front"));
		mViewOptionsPopupMenu->Append(ID_VIEWTYPE_LEFT, _("Left"));
		mViewOptionsPopupMenu->Append(ID_VIEWTYPE_PERSPECTIVE, _("Perspective"));
		mViewOptionsPopupMenu->AppendSeparator();
		mViewOptionsPopupMenu->Append(ID_WIREFRAME, _T("Wireframe"));
		mViewOptionsPopupMenu->Append(ID_TEXTURE, _T("Textured"));
		mViewOptionsPopupMenu->AppendSeparator();
		mViewOptionsPopupMenu->Append(ID_FULLFOUR, _T("Full/4Split"));
		mViewOptionsPopupMenu->Append(ID_STAGEGRID, _T("ShowGrid"));

		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_TOP)->SetCheckable(true);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_FRONT)->SetCheckable(true);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_LEFT)->SetCheckable(true);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_PERSPECTIVE)->SetCheckable(true);
		mViewOptionsPopupMenu->FindItem(ID_STAGEGRID)->SetCheckable(true);
	}

	if (!mEditMenu)
	{
		mEditMenu = new wxMenu();

		wxMenu *actorAddMenu = new wxMenu();
		actorAddMenu->Append(ID_ADDACTOR_MODEL, _("Model"));
		actorAddMenu->Append(ID_ADDACTOR_EFFECT, _("Effect"));

		wxMenu *actorLightMenu = new wxMenu();
		//actorLightMenu->Append(ID_ADDACTOR_LIGHT_DIRECTION, _("DirectionLight"));
		actorLightMenu->Append(ID_ADDACTOR_LIGHT_POINT, _("PointLight"));
		actorLightMenu->Append(ID_ADDACTOR_LIGHT_SPOT, _("SpotLight"));
		actorAddMenu->AppendSubMenu(actorLightMenu, _("Light"));

		actorAddMenu->Append(ID_ADDACTOR_SOUND, _("Sound"));
		actorAddMenu->Append(ID_ADDACTOR_TRIGER, _("Triger"));

		mEditMenu->AppendSubMenu(actorAddMenu, _("Add actor"));

		wxMenu *cloneMenu = new wxMenu();
		cloneMenu->Append(ID_CLONE_INSTANCE, _("Instance"));
		cloneMenu->Append(ID_CLONE_DATA, _("Data"));
		mEditMenu->AppendSubMenu(cloneMenu, _("Clone"));
		//mEditMenu->Enable(ID_CLONE_INSTANCE, false);
		//mEditMenu->Enable(ID_CLONE_DATA, false);
		//cloneMenu->
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::Initialize()
{
	// 相机
	mCamera = new0 Camera();

	// 渲染器
	mWidth = 800;
	mHeight = 600;
	mColorFormat = Texture::TF_A8R8G8B8;
	mDepthStencilFormat = Texture::TF_D24S8;
	mNumMultisamples = 0;

//#ifdef PX2_USE_DX9
	HWND hWnd = (HWND)(this->GetHandle());
	mInput.mWindowHandle = hWnd;
	mInput.mDriver = Direct3DCreate9(D3D_SDK_VERSION);
	assertion(mInput.mDriver != 0, "Failed to create Direct3D9\n");
	mRenderer = new0 Renderer(mInput, mWidth, mHeight,
		mColorFormat, mDepthStencilFormat, mNumMultisamples);
//#else
// ToDo
//#endif
	mRenderer->SetCamera(mCamera);
	mBackGroundColor = Float4(0.4f, 0.4f, 0.4f, 0.0f);
	mRenderer->SetClearColor(mBackGroundColor);

	SetViewType(mViewType);
	SetViewDetail(mViewDetail);
}
//----------------------------------------------------------------------------
void RenderViewWindow::InitExpand ()
{
	int viewFullIndex = EditorOptions::GetSingleton().mViewFullIndex;
	if (GetParent()->IsKindOf(wxClassInfo::FindClass(wxT("wxFourWaySplitter"))))
	{
		wxFourWaySplitter* splitter = static_cast<wxFourWaySplitter*>(GetParent());

		if (viewFullIndex == mWindowIndex)
		{
			splitter->SetExpanded(this);
			mExpanded = true;
		}
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::RegenGridGeometry()
{
	float gridSize = EditorOptions::GetSingleton().mGridSize;

	// Grid
	mGridVFormat = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT4, 0);

	if (mViewType==VT_PERSPECTIVE || mViewType==VT_TOP)
	{
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
	}
	else if (mViewType == VT_FRONT)
	{
		Transform trans;
		HMatrix matRot;
		matRot.MakeRotation(AVector::UNIT_X, Mathf::HALF_PI);
		trans.SetRotate(matRot);
		StandardMesh sM(mGridVFormat, true, false, &trans);
		mGrid = sM.LineRectangleForEditor(81, 81, gridSize, gridSize, mGray);

		mVBGridAxis = new0 VertexBuffer(4, mGridVFormat->GetStride(), 
			Buffer::BU_DYNAMIC);
		mGridAxisAssessor.ApplyTo(mGridVFormat, mVBGridAxis);
		mGridAxisAssessor.Position<Float3>(0) = Float3(-gridSize, -0.0f, 0.0f);
		mGridAxisAssessor.Color<Float4>(0, 0) = mRed;
		mGridAxisAssessor.Position<Float3>(1) = Float3(gridSize, -0.0f, 0.0f);
		mGridAxisAssessor.Color<Float4>(0, 1) = mRed;
		mGridAxisAssessor.Position<Float3>(2) = Float3(0.0f, -0.0f, -gridSize);
		mGridAxisAssessor.Color<Float4>(0, 2) = mBlue;
		mGridAxisAssessor.Position<Float3>(3) = Float3(0.0f, -0.0f, gridSize);
		mGridAxisAssessor.Color<Float4>(0, 3) = mBlue;
		mGridAxis = new0 Polysegment(mGridVFormat, mVBGridAxis, false);
	}
	else if (mViewType == VT_LEFT)
	{
		Transform trans;
		HMatrix matRot;
		matRot.MakeRotation(AVector::UNIT_Y, Mathf::HALF_PI);
		trans.SetRotate(matRot);
		StandardMesh sM(mGridVFormat, true, false, &trans);
		mGrid = sM.LineRectangleForEditor(81, 81, gridSize, gridSize, mGray);

		mVBGridAxis = new0 VertexBuffer(4, mGridVFormat->GetStride(), 
			Buffer::BU_DYNAMIC);
		mGridAxisAssessor.ApplyTo(mGridVFormat, mVBGridAxis);
		mGridAxisAssessor.Position<Float3>(0) = Float3(-0.0f, -gridSize, 0.0f);
		mGridAxisAssessor.Color<Float4>(0, 0) = mGreen;
		mGridAxisAssessor.Position<Float3>(1) = Float3(-0.0f, gridSize, 0.0f);
		mGridAxisAssessor.Color<Float4>(0, 1) = mGreen;
		mGridAxisAssessor.Position<Float3>(2) = Float3(-0.0f, 0.0f, -gridSize);
		mGridAxisAssessor.Color<Float4>(0, 2) = mBlue;
		mGridAxisAssessor.Position<Float3>(3) = Float3(-0.0f, 0.0f, gridSize);
		mGridAxisAssessor.Color<Float4>(0, 3) = mBlue;
		mGridAxis = new0 Polysegment(mGridVFormat, mVBGridAxis, false);
	}

	// Material
	mGrid->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	mGridAxis->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());

	// Scene
	mGridScene = new0 Node();
	mGridScene->AttachChild(mGridAxis);
	mGridScene->AttachChild(mGrid);
	mGridScene->Update();
}
//----------------------------------------------------------------------------
void RenderViewWindow::Update ()
{
	if (mGridScene)
		mGridScene->Update();

	// Scene一帧只能更新一次，GraphicsScene不能在这做更新
	//if (mGraphicsScene)
	//	mGraphicsScene->Update();

	if (mCtrlScene)
		mCtrlScene->Update();
}
//----------------------------------------------------------------------------
void RenderViewWindow::Draw ()
{
	if (mGridScene)
	{
		mGridCuller.ComputeVisibleSet(mGridScene);
	}

	if (mCtrlScene)
	{
		mCtrlCuller.ComputeVisibleSet(mCtrlScene);
	}

	if (mGraphicsScene)
	{
		mCuller.ComputeVisibleSet(mGraphicsScene);
		mCuller.GetVisibleSet().Sort();

		if (GetWindowIndex() == 3)
		{
			mCuller.ComputeEnvironment();
		}
	}

	if (mHelpScene)
	{
		mHelpSceneCuller.ComputeVisibleSet(mHelpScene);
	}

	if (mRenderer->PreDraw())
	{
		mRenderer->ClearBuffers();

		mRenderer->Draw(mGridCuller.GetVisibleSet());

		mRenderer->Draw(mCuller.GetVisibleSet());
	//	mRenderer->Draw(mCuller.GetVisibleSet());

		mRenderer->SetOverrideDepthProperty(mOverWriteDepth);
		mRenderer->Draw(mHelpSceneCuller.GetVisibleSet());
		mRenderer->Draw(mCtrlCuller.GetVisibleSet());
		mRenderer->SetOverrideDepthProperty(0);

		bool drawPhysics = EditSystem::GetSingleton().GetEditMap()
			->IsPhysicsDraw();
		if (drawPhysics)
		{
			((TdBt::DebugLines*)(EditSystem::GetSingleton().GetEditMap()
				->GetScene()->GetDynamicWorld()->GetDebugDrawer()))
				->Draw(mRenderer);
		}

		mRenderer->Draw(20, 20, Float4(1.0f, 1.0f, 1.0f, 1.0f), 
			ViewTypeString[mViewType]);

		mRenderer->PostDraw();
		mRenderer->DisplayColorBuffer();
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnSize(wxSizeEvent& e)
{
	wxSize sz = GetClientSize();
	if (mToolbar)
	{
		mToolbar->SetSize(sz.x, 66);
		mToolbar->Realize();
	}

	mWidth = sz.GetX();
	mHeight = sz.GetY();
	mRenderer->ResizeWindow(sz.x, sz.y);

	UpdateCameraOrthorFrame();
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnMove(wxMoveEvent& e)
{
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnPaint(wxPaintEvent& e)
{
	// Keep wxWidgets happy
	wxPaintDC dc(this);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnLeftDown(wxMouseEvent& e)
{
	mLeftDown = true;
	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->Handle3DPaneLeftDown(this, e);

	if (GetParent()->IsKindOf(wxClassInfo::FindClass(wxT("wxFourWaySplitter"))))
	{
		wxFourWaySplitter* splitter = static_cast<wxFourWaySplitter*>(GetParent());
		splitter->SetActiveWindow(this);
	}	
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnLeftUp(wxMouseEvent& e)
{
	mLeftDown = false;
	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->Handle3DPaneLeftUp(this, e);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnMiddleDown(wxMouseEvent& e)
{
	mMiddleDown = true;
	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->Handle3DPaneMiddleDown(this, e);

	if (GetParent()->IsKindOf(wxClassInfo::FindClass(wxT("wxFourWaySplitter"))))
	{
		wxFourWaySplitter* splitter = static_cast<wxFourWaySplitter*>(GetParent());
		splitter->SetActiveWindow(this);
	}	
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnMiddleUp(wxMouseEvent& e)
{
	// 不要在此处处理
	// mMiddleDown = false;

	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->Handle3DPaneMiddleUp(this, e);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnMouseWheel(wxMouseEvent& e)
{
	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->Handler3DPaneMouseWheel(this, e);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnRightDown(wxMouseEvent& e)
{
	mRightDown = true;
	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->Handle3DPaneRightDown(this, e);

	if (GetParent()->IsKindOf(wxClassInfo::FindClass(wxT("wxFourWaySplitter"))))
	{
		wxFourWaySplitter* splitter = static_cast<wxFourWaySplitter*>(GetParent());
		splitter->SetActiveWindow(this);
	}

	if (EditSystem::GetSingleton().GetEditMode() == EditSystem::EM_PHYSICSPLAY)
	{
		APoint pos = mCamera->GetPosition();
		AVector dir = mCamera->GetDVector();

		EditSystem::GetSingleton().GetEditMap()->FireACube(pos, dir, 20.0f);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnRightUp(wxMouseEvent& e)
{
	wxPoint popupPos = wxGetMousePosition();
	popupPos = ScreenToClient(popupPos);

	wxRect rect(0, 0, 75, 20);
	if (rect.Contains(popupPos))
	{
		if (mViewOptionsPopupMenu)
			this->PopupMenu(mViewOptionsPopupMenu, popupPos.x, popupPos.y);
	}
	else if (!mRightDownOnMotion)
	{
		if (EditSystem::GetSingleton().GetEditMode() == EditSystem::EM_SELECT)
		{
			if (mEditMenu)
				this->PopupMenu(mEditMenu, popupPos.x, popupPos.y);
		}
	}

	mRightDownOnMotion = false;

	mRightDown = false;
	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->Handle3DPaneRightUp(this, e);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnMotion(wxMouseEvent& e)
{
	//if (mRightDown || mMiddleDown)
	//{
	//	ShowCursor(false);
	//}
	//else
	//{
	//	ShowCursor(true);
	//}

	if (mRightDown)
		mRightDownOnMotion = true;
	else
		mRightDownOnMotion = false;

	wxPoint point = e.GetPosition();
	wxPoint diff = point - mLastMousePoint;

	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->Handle3DPaneMotion(this, e);

	mLastMousePoint = point;

}
//----------------------------------------------------------------------------
void RenderViewWindow::OnKeyDown(wxKeyEvent& e)
{
	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->Handle3DPaneKeyDown(this, e);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnKeyUp(wxKeyEvent& e)
{
	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->Handle3DPaneKeyUp(this, e);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnChar(wxKeyEvent& e)
{
	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->Handle3DPaneChar(this, e);
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
void RenderViewWindow::SetCameraFrameAxis ()
{
	switch (mViewType)
	{
	case VT_LEFT:
		SetAxisLeft();
		break;
	case VT_TOP:
		SetAxisTop();
		break;
	case VT_FRONT:
		SetAxisFront();
		break;
	case VT_PERSPECTIVE:
		SetAxisPerspective();
		break;
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::SetAxisTop ()
{
	mCamera = 0;
	mCamera = new Camera(false);
	float orthoAdjust = EditorOptions::GetSingleton().mOrthoAdjust;
	float upMin = orthoAdjust * mHeight/mWidth;
	mCamera->SetFrustum(1.0f, 10000.0f, -upMin, upMin, -orthoAdjust, orthoAdjust);

	APoint pos;
	AVector dir;
	AVector up;
	AVector right;
	dir = AVector(0.0f, 0.0f, -1.0f);
	up = AVector(0.0f, 1.0f, 0.0f);
	right = AVector(1.0f, 0.0f, 0.0f);
	pos.Z() = 5000.0f;

	AVector::Orthonormalize(dir, up, right);
	mCamera->SetFrame(pos, dir, up, right);
}
//----------------------------------------------------------------------------
void RenderViewWindow::SetAxisFront ()
{
	mCamera = 0;
	mCamera = new Camera(false);
	float orthoAdjust = EditorOptions::GetSingleton().mOrthoAdjust;
	float upMin = orthoAdjust * mHeight/mWidth;
	mCamera->SetFrustum(1.0f, 10000.0f, -upMin, upMin, -orthoAdjust, orthoAdjust);

	APoint pos;
	AVector dir;
	AVector up;
	AVector right;
	dir = AVector(0.0f, 1.0f, 0.0f);
	up = AVector(0.0f, 0.0f, 1.0f);
	right = AVector(1.0f, 0.0f, 0.0f);
	pos.Y() = -5000.0f;

	AVector::Orthonormalize(dir, up, right);
	mCamera->SetFrame(pos, dir, up, right);
}
//----------------------------------------------------------------------------
void RenderViewWindow::SetAxisLeft ()
{
	mCamera = 0;
	mCamera = new Camera(false);
	float orthoAdjust = EditorOptions::GetSingleton().mOrthoAdjust;
	float upMin = orthoAdjust * mHeight/mWidth;
	mCamera->SetFrustum(1.0f, 10000.0f, -upMin, upMin, -orthoAdjust, orthoAdjust);

	APoint pos;
	AVector dir;
	AVector up;
	AVector right;
	dir = AVector(1.0f, 0.0f, 0.0f);
	up = AVector(0.0f, 0.0f, 1.0f);
	right = AVector(0.0f, -1.0f, 0.0f);
	pos.X() = -5000.0f;

	AVector::Orthonormalize(dir, up, right);
	mCamera->SetFrame(pos, dir, up, right);
}
//----------------------------------------------------------------------------
void RenderViewWindow::SetAxisPerspective ()
{
	// Camera
	mCamera = 0;
	mCamera = new Camera();
	mCamera->SetFrustum(1.0f, 1000.0f, -0.4125f, 0.4125f, -0.55f, 0.55f);
	APoint loc;
	AVector dir;
	AVector up;
	AVector right;
	loc = APoint::ORIGIN;
	loc.X() = -10.0f; loc.Y() = -10.0f; loc.Z() = 5.0f;
	dir.X() = -loc.X();
	dir.Y() = -loc.Y();
	dir.Z() = -loc.Z();
	up = AVector(Float3(0.0f, 0.0f, 1.0f));
	right = dir.Cross(up);
	dir = up.Cross(right);

	dir.Normalize();
	up.Normalize();
	right.Normalize();
	AVector::Orthonormalize(dir, up, right);
	mCamera->SetFrame(loc, dir, up, right);
}
//----------------------------------------------------------------------------
void RenderViewWindow::UpdateCameraOrthorFrame ()
{
	if (mViewType != VT_PERSPECTIVE)
	{
		float orthoAdjust = EditorOptions::GetSingleton().mOrthoAdjust;
		float upMin = orthoAdjust * mHeight/mWidth;
		mCamera->SetFrustum(1.0f, 10000.0f, -upMin, upMin,
			-orthoAdjust, orthoAdjust);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnMouseCaptureLost(wxMouseCaptureLostEvent& e)
{

}
//----------------------------------------------------------------------------
void RenderViewWindow::OnViewTypeCommand (wxCommandEvent& e)
{
	int id = e.GetId();

	if (id == ID_VIEWTYPE_TOP)
	{
		SetViewType(VT_TOP);
	}
	else if (id == ID_VIEWTYPE_FRONT)
	{
		SetViewType(VT_FRONT);
	}
	else if (id == ID_VIEWTYPE_LEFT)
	{
		SetViewType(VT_LEFT);
	}
	else
	{
		SetViewType(VT_PERSPECTIVE);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnWireFrame (wxCommandEvent& e)
{
	if (!mRenderer)
		return;

	mRenderer->SetOverrideWireProperty(mOverrideWireProperty);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnTextured (wxCommandEvent& e)
{
	if (!mRenderer)
		return;

	mRenderer->SetOverrideWireProperty(0);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnFullFour (wxCommandEvent& e)
{
	if (GetParent()->IsKindOf(wxClassInfo::FindClass(wxT("wxFourWaySplitter"))))
	{
		wxFourWaySplitter* splitter = static_cast<wxFourWaySplitter*>(GetParent());
		if (mExpanded)
		{
			EditorOptions::GetSingleton().mViewFullIndex = -1;

			splitter->SetExpanded(-1);
		}
		else
		{
			EditorOptions::GetSingleton().mViewFullIndex = mWindowIndex;

			splitter->SetExpanded(this);
		}

		mExpanded = !mExpanded;
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnStageGrid (wxCommandEvent& e)
{
	mShowGrid = !mShowGrid;

	if (mShowGrid)
	{
		mGridScene->Culling = Movable::CULL_DYNAMIC;
		mViewOptionsPopupMenu->FindItem(ID_STAGEGRID)->Check(true);
	}
	else
	{
		mGridScene->Culling = Movable::CULL_ALWAYS;
		mViewOptionsPopupMenu->FindItem(ID_STAGEGRID)->Check(false);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnActorModel (wxCommandEvent& e)
{
	PX2::APoint pos = ControllerManager::GetSingleton()
		.GetCurrentControllerInstance()->GetSelectPoint();

	EditSystem::GetSingleton().GetEditMap()->NewAndAddModel(pos);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnActorLight_Ambient (wxCommandEvent& e)
{
	PX2::APoint pos = ControllerManager::GetSingleton()
		.GetCurrentControllerInstance()->GetSelectPoint();

	EditSystem::GetSingleton().GetEditMap()->NewAndAddLight("NoName",
		pos, Light::LT_AMBIENT);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnActorLight_Direction (wxCommandEvent& e)
{
	PX2::APoint pos = ControllerManager::GetSingleton()
		.GetCurrentControllerInstance()->GetSelectPoint();

	EditSystem::GetSingleton().GetEditMap()->NewAndAddLight("NoName",
		pos, Light::LT_DIRECTIONAL);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnActorLight_Point (wxCommandEvent& e)
{
	PX2::APoint pos = ControllerManager::GetSingleton()
		.GetCurrentControllerInstance()->GetSelectPoint();

	EditSystem::GetSingleton().GetEditMap()->NewAndAddLight("NoName",
		pos, Light::LT_POINT);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnActorLight_Spot (wxCommandEvent& e)
{
	PX2::APoint pos = ControllerManager::GetSingleton()
		.GetCurrentControllerInstance()->GetSelectPoint();

	EditSystem::GetSingleton().GetEditMap()->NewAndAddLight("NoName",
		pos, Light::LT_SPOT);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnActorSound (wxCommandEvent& e)
{
	PX2::APoint pos = ControllerManager::GetSingleton()
		.GetCurrentControllerInstance()->GetSelectPoint();

	EditSystem::GetSingleton().GetEditMap()->NewAndAddSound(pos);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnCloneInstance (wxCommandEvent& e)
{
	int num = ActorSelection::GetSingleton().GetActorQuantity();
	if (1 == num)
	{  
		Actor *actor = ActorSelection::GetSingleton().GetActor(0);
		if (!actor)
			return;

		Object *object = actor->Copy("");
		Actor *newActor = 0;
		newActor = DynamicCast<Actor>(object);

		if (newActor)
		{
			PX2::APoint pos = ControllerManager::GetSingleton()
				.GetCurrentControllerInstance()->GetSelectPoint();
			newActor->SetPosition(pos);

			EditSystem::GetSingleton().GetEditMap()->AddActor(newActor);
		}
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnCloneData (wxCommandEvent& e)
{
	int num = ActorSelection::GetSingleton().GetActorQuantity();
	if (1 == num)
	{
		Actor *actor = ActorSelection::GetSingleton().GetActor(0);
		if (actor)
			return;

		Object *object = actor->Copy("");
		Actor *newActor = 0;
		newActor = DynamicCast<Actor>(object);

		if (newActor)
		{
			PX2::APoint pos = ControllerManager::GetSingleton()
				.GetCurrentControllerInstance()->GetSelectPoint();
			newActor->SetPosition(pos);

			EditSystem::GetSingleton().GetEditMap()->AddActor(newActor);
		}
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::DoEnter ()
{

}
//----------------------------------------------------------------------------
void RenderViewWindow::DoUpdate ()
{

}
//----------------------------------------------------------------------------
void RenderViewWindow::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, 
		EditorEventSpace::SetEditMode))
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
}
//----------------------------------------------------------------------------
void RenderViewWindow::DoLeave ()
{

}
//----------------------------------------------------------------------------
void RenderViewWindow::SetWindowIndex (int index)
{
	mWindowIndex = index;
}
//----------------------------------------------------------------------------
int RenderViewWindow::GetWindowIndex ()
{
	return mWindowIndex;
}
//----------------------------------------------------------------------------
void RenderViewWindow::SetViewType (ViewType viewType)
{
	mViewType = viewType;

	if (mViewChoice)
		mViewChoice->SetSelection(mViewType);

	mSceneNodeCtrl->SetLookType((SceneNodeCtrl::LookType)viewType);

	SetCameraFrameAxis();

	RegenGridGeometry();

	mRenderer->SetCamera(mCamera);
	mGridCuller.SetCamera(mCamera);
	mCtrlCuller.SetCamera(mCamera);
	mCuller.SetCamera(mCamera);
	mHelpSceneCuller.SetCamera(mCamera);

	if (viewType == VT_TOP)
	{
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_TOP)->Check(true);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_FRONT)->Check(false);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_LEFT)->Check(false);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_PERSPECTIVE)->Check(false);
	}
	else if (viewType == VT_FRONT)
	{
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_TOP)->Check(false);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_FRONT)->Check(true);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_LEFT)->Check(false);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_PERSPECTIVE)->Check(false);
	}
	else if (viewType == VT_LEFT)
	{
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_TOP)->Check(false);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_FRONT)->Check(false);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_LEFT)->Check(true);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_PERSPECTIVE)->Check(false);
	}
	else
	{
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_TOP)->Check(false);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_FRONT)->Check(false);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_LEFT)->Check(false);
		mViewOptionsPopupMenu->FindItem(ID_VIEWTYPE_PERSPECTIVE)->Check(true);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::SetViewDetail (ViewDetail viewDetail)
{

}
//----------------------------------------------------------------------------
void RenderViewWindow::OnTimer (wxTimerEvent& event)
{
	//if (wxGetKeyState(_T('W')))
	//{
	//	MoveCamera(0, 1.0f);
	//}
	//else if (wxGetKeyState(_T('S')))
	//{
	//	MoveCamera(0, -1.0f);
	//}
	//else if (wxGetKeyState(_T('A')))
	//{
	//	MoveCamera(1.0f, 0.0f);
	//}
	//else if (wxGetKeyState(_T('D')))
	//{
	//	MoveCamera(-1.0f, 0.0f);
	//}

	if (GetParent()->IsKindOf(wxClassInfo::FindClass(wxT("wxFourWaySplitter"))))
	{
		wxFourWaySplitter* splitter = static_cast<wxFourWaySplitter*>(GetParent());

		if (splitter->GetActiveWidnow() == GetWindowIndex())
		{
			bool altDown = wxGetKeyState(WXK_ALT);

			if (wxGetKeyState((wxKeyCode)(_T('W'))))
			{
				if (GetViewType() == VT_PERSPECTIVE)
				{
					if (altDown)
						MoveCamera(0.0f, 0.5f);
					else
						ZoomCamera(1.0f);
				}
				else
				{
					MoveCamera(0.0f, 0.5f);
				}
			}
			if (wxGetKeyState((wxKeyCode)(_T('S'))))
			{
				if (GetViewType() == VT_PERSPECTIVE)
				{
					if (altDown)
						MoveCamera(0.0f, -0.5f);
					else
						ZoomCamera(-1.0f);
				}
				else
				{
					MoveCamera(0.0f, -0.5f);
				}
			}
			if (wxGetKeyState((wxKeyCode)(_T('A'))))
			{
				MoveCamera(0.5f, 0.0f);
			}
			if (wxGetKeyState((wxKeyCode)(_T('D'))))
			{
				MoveCamera(-0.5f, 0.0f);
			}
		}
	}

	Update();

	Draw();
}
//----------------------------------------------------------------------------
void RenderViewWindow::TargetCamera (const PX2::Vector3f &pos)
{
}
//----------------------------------------------------------------------------
void RenderViewWindow::SetCameraOrientation (
	const PX2::HQuaternion &orientation)
{

}
//----------------------------------------------------------------------------
void RenderViewWindow::DollyCamera (const PX2::Vector3f &trans)
{
	Vector3f position = mCamera->GetPosition();
	position += trans;

	mCamera->SetPosition(position);
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
void RenderViewWindow::RollCamera (const float &roll)
{

}
//----------------------------------------------------------------------------
void RenderViewWindow::OrbitCamera (const float &horz, const float &vert)
{

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
		position += dVector * vert * 5.0f;
		position -= rVector * horz * 5.0f;

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
void RenderViewWindow::ZoomCamera (float zoom)
{
	mSceneNodeCtrl->OnMouseWheel(mRenderer, zoom);

	Vector3f position = mCamera->GetPosition();
	AVector dir = mCamera->GetDVector();

	if (mViewType == VT_PERSPECTIVE)
	{
		position += dir*zoom;
		mCamera->SetPosition(position);
	}
	else
	{
		float rMin = 0.0f;
		float rMax = 0.0f;
		float uMin = 0.0f;
		float uMax = 0.0f;
		float dMin = 0.0f;
		float dMax = 0.0f;
		float orthoFrustumMin = EditorOptions::GetSingleton().mOrthoFrustumMin;
		mCamera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
		uMin += (zoom * 0.1f);
		if (uMin > -orthoFrustumMin)
			uMin = -orthoFrustumMin;
		uMax = -uMin;
		rMin = uMin * mWidth/mHeight;
		rMax = -rMin;

		mCamera->SetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::FocusCursourOnCenter ()
{
	wxRect rect = GetClientRect();
	SetCursorPos(rect.GetX() + (int)(rect.GetWidth()/2.0f), 
		rect.GetY() + (int)(rect.GetHeight()/2.0f));
}
//----------------------------------------------------------------------------
PixelToWorld RenderViewWindow::StartMouseDrag(wxMouseEvent& e)
{
	if (mMiddleDown)
	{
	//	ShowCursor(false);
	//	GetCursorPos(&mMouseDragBefore);
	}

	PixelToWorld pixelToWorld;

	if (mViewType == VT_PERSPECTIVE)
	{
		float rMin = mCamera->GetRMin();
		float uMin = mCamera->GetUMin();
		float viewPortWidth = mRenderer->GetWidth();
		float viewPortHeight = mRenderer->GetHeight();

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
		float viewPortWidth = mRenderer->GetWidth();
		float viewPortHeight = mRenderer->GetHeight();

		float worldW = 2.0f * -rMin;
		float worldH = 2.0f * -uMin;

		worldW *= 1.0f;
		worldH *= 1.0f;

		pixelToWorld.first = worldW/(float)viewPortWidth;
		pixelToWorld.second = worldH/(float)viewPortHeight;
	}

	//CaptureMouse();

	return pixelToWorld;
}
//----------------------------------------------------------------------------
void RenderViewWindow::EndMouseDrag(wxMouseEvent& e)
{
	if (mMiddleDown)
	{
//		SetCursorPos(mMouseDragBefore.x, mMouseDragBefore.y);
//		ShowCursor(true);
		mMiddleDown = false;
	}

	//ReleaseMouse();
}
//----------------------------------------------------------------------------
void RenderViewWindow::SetScene (Movable *scene)
{
	mGraphicsScene = scene;
}
//----------------------------------------------------------------------------
Movable *RenderViewWindow::GetScene ()
{
	return mGraphicsScene;
}
//----------------------------------------------------------------------------
void RenderViewWindow::SetHelpScene (PX2::Movable *scene)
{
	mHelpScene = scene;
}
//----------------------------------------------------------------------------
PX2::Movable *RenderViewWindow::GetHelpScene ()
{
	return mHelpScene;
}
//----------------------------------------------------------------------------