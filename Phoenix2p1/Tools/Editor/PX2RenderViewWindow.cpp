/*
*
* 文件名称	：	PX2RenderViewWindow.cpp
*
*/

#include "PX2RenderViewWindow.hpp"
#include "PX2EditorParams.hpp"
#include "PX2ViewCtrlInstMan.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditSystem.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2UIManager.hpp"
#include "PX2Project.hpp"
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
#define ID_ADDACTOR_SKY wxID_HIGHEST + 3109
#define ID_CREATE_BOX wxID_HIGHEST + 3110
#define ID_CREATE_SPHERE wxID_HIGHEST + 3111
#define ID_CREATE_EFFECT wxID_HIGHEST + 3112
#define ID_CREATE_UI_PICTUREBOX wxID_HIGHEST + 3114
#define ID_CREATE_UI_FRAME wxID_HIGHEST + 3115
#define ID_CREATE_UI_BUTTON wxID_HIGHEST + 3116
#define ID_CREATE_UI_CHECKBOX wxID_HIGHEST + 3117
#define ID_CREATE_UI_EDITBOX wxID_HIGHEST + 3118
#define ID_CREATE_UI_STATICTEXT wxID_HIGHEST + 3119
#define ID_CREATE_UI_PROGRESSBAR wxID_HIGHEST + 3120
#define ID_CREATE_UI_SLIDER wxID_HIGHEST + 3121
#define ID_CREATE_UI_ANIMPICBOX wxID_HIGHEST + 3122
#define ID_CLONE_INSTANCE wxID_HIGHEST + 3151
#define ID_CLONE_DATA wxID_HIGHEST + 3152
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
EVT_MENU(ID_ADDACTOR_SKY, RenderViewWindow::OnActorSky)
EVT_MENU(ID_CREATE_BOX, RenderViewWindow::OnCreateBox)
EVT_MENU(ID_CREATE_SPHERE, RenderViewWindow::OnCreateSphere)
EVT_MENU(ID_CREATE_EFFECT, RenderViewWindow::OnCreateEffect)
EVT_MENU(ID_CREATE_UI_FRAME, RenderViewWindow::OnCreateUIFrame)
EVT_MENU(ID_CREATE_UI_PICTUREBOX, RenderViewWindow::OnCreateUIPicBox)
EVT_MENU(ID_CREATE_UI_ANIMPICBOX, RenderViewWindow::OnCreateUIAnimPixBox)
EVT_MENU(ID_CREATE_UI_STATICTEXT, RenderViewWindow::OnCreateUIStaticText)
EVT_MENU(ID_CREATE_UI_BUTTON, RenderViewWindow::OnCreateUIButton)
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
	mCameraMoveSpeed(40.0f),
	mCurCameraMoveSpeed_W(0.0f),
	mCurCameraMoveSpeed_S(0.0f),
	mCurCameraMoveSpeed_A(0.0f),
	mCurCameraMoveSpeed_D(0.0f),
	mInited(false),
	mSceneNodeCtrl(0),
	mBoundCtrl(0),
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
	mCameraMoveSpeed(40.0f),
	mCurCameraMoveSpeed_W(0.0f),
	mCurCameraMoveSpeed_S(0.0f),
	mCurCameraMoveSpeed_A(0.0f),
	mCurCameraMoveSpeed_D(0.0f),
	mInited(false),
	mSceneNodeCtrl(0),
	mBoundCtrl(0),
	mActive(false),
	mLeftDown(false),
	mMiddleDown(false),
	mRightDown(false),
	mRightDownOnMotion(false),
	mEditMenu(0)
{
	mBlack = Float4(0.0f, 0.0f, 0.0f, 1.0f);
	mRed = Float4(1.0f, 0.0f, 0.0f, 0.7f);
	mGreen = Float4(0.0f, 1.0f, 0.0f, 0.7f);
	mBlue = Float4(0.0f, 0.0f, 1.0f, 0.7f);
	mGray = Float4(0.43f, 0.43f, 0.43f, 0.7f);
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

	if (mBoundCtrl)
	{
		delete0(mBoundCtrl);
		mBoundCtrl = 0;
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
	mBackGroundColor = Float4(0.83f, 0.815f, 0.784f, 0.0f);
	mRenderer->SetClearColor(mBackGroundColor);

	mSceneWireOverride = new0 WireProperty();
	mSceneWireOverride->Enabled = true;
	mUIWireOverride = new0 WireProperty();
	mUIWireOverride->Enabled = true;

	mRenderTimer.SetOwner(this, ID_RENDERTIMER);
	mRenderTimer.Start(mRenderMilliseconds);

	mCtrlTimer.SetOwner(this, ID_CTRLTIMER);
	mCtrlTimer.Start(mCtrlMilliseconds);

	mOverWriteDepth = new0 DepthProperty();
	mOverWriteDepth->Enabled = false;
	mOverWriteDepth->Writable = false;

	mSceneNodeCtrl = new0 SceneNodeCtrl();
	EventWorld::GetSingleton().ComeIn(mSceneNodeCtrl);
	mBoundCtrl = new0 BoundCtrl();
	EventWorld::GetSingleton().ComeIn(mBoundCtrl);

	mCtrlScene = new0 Node();
	mCtrlScene->AttachChild(mSceneNodeCtrl->GetCtrlsGroup());
	mCtrlScene->AttachChild(mBoundCtrl->GetCtrlsGroup());
	mCtrlScene->Update();

	SetViewType(VT_PERSPECTIVE);

	CreateEditMenu();

	Scene *scene = 0;
	if (Project::GetSingletonPtr())
	{
		scene = Project::GetSingleton().GetScene();
	}

	if (scene)
	{
		scene->GetDefaultCameraActor()->SetCamera(mCamera);
		SetScene(scene->GetSceneNode());
	}

	SetHelpScene(EditSystem::GetSingleton().GetHelpScene());

	// splash
	mPicBox = new0 UIPicBox();
	mPicBox->SetTexture("ToolRes/images/picBox.png");
	mPicBox->SetSize((float)(mPicBox->GetTexture()->GetWidth()),
		(float)(mPicBox->GetTexture()->GetHeight()));

	// ui range
	mProjRangeVFormat = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT4, 0);
	mProjRangeVBuffer = new0 VertexBuffer(5, mProjRangeVFormat->GetStride());
	mProjRangeSegment = new0 Polysegment(mProjRangeVFormat, mProjRangeVBuffer, 
		true);
	mProjRangeSegment->SetNumSegments(4);
	mProjRangeSegment->UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);
	mProjRangeSegment->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	UpdateProjectRange();

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
	GraphicsRoot::GetSingleton().SetCamera(mCamera);
	UIManager::GetSingleton().GetDefaultView()->SetRenderer(mRenderer);
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
		Project *proj = Project::GetSingletonPtr();
		if (proj)
		{
			Scene *scene = proj->GetScene();

			if (scene)
			{
				TerrainActor *terActor = scene->GetTerrainActor();
				if (terActor)
				{
					LODTerrain *lodTerrain = terActor->GetLODTerrain();
					if (lodTerrain)
					{
						lodTerrain->Simplify();
					}
				}
			}
		}

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
	
	AdjustUICameraPercent();
	UpdateProjectTrans();

	Sizef picSize = mPicBox->GetSize();
	float picPosX = ((float)mWidth - picSize.Width)/2.0f;
	float picPosZ = ((float)mHeight - picSize.Height)/2.0f;
	mPicBox->WorldTransform.SetTranslate(APoint(picPosX, 0.0f, picPosZ));
	mPicBox->WorldBoundIsCurrent = true;

	GraphicsRoot::GetSingleton().SetSize(Sizef((float)mWidth, (float)mHeight));
	mRenderer->ResizeWindow(sz.x, sz.y);
	mCamera->SetFrustum(35.0f, (float)mWidth/(float)mHeight, 1.0f, 1000.0f);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnPaint(wxPaintEvent& e)
{
	wxPaintDC dc(this);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnEnterWindow(wxMouseEvent& e)
{
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

	SetFocus();
	mLeftDown = true;

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->HandleLeftDown(this, e);

	wxPoint mousePos = e.GetPosition();
	Event *ent = InputEventSpace::CreateEventX(InputEventSpace::TouchPressed);
	InputEventData data;
	data.MState.X.Absoulate = mousePos.x;
	data.MState.Y.Absoulate = mHeight - mousePos.y;
	data.TState.X = data.MState.X;
	data.TState.Y = data.MState.Y;
	ent->SetData<InputEventData>(data);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnLeftUp (wxMouseEvent& e)
{
	if (!mInited)
		return;

	mLeftDown = false;

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->HandleLeftUp(this, e);

	wxPoint mousePos = e.GetPosition();
	Event *ent = InputEventSpace::CreateEventX(InputEventSpace::TouchReleased);
	InputEventData data;
	data.MState.X.Absoulate = mousePos.x;
	data.MState.Y.Absoulate = mHeight - mousePos.y;
	data.TState.X = data.MState.X;
	data.TState.Y = data.MState.Y;
	ent->SetData<InputEventData>(data);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnMiddleDown (wxMouseEvent& e)
{
	if (!mInited)
		return;

	SetFocus();
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

	if (!mActive)
		return;

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->HandleMouseWheel(this, e);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnRightDown (wxMouseEvent& e)
{
	if (!mInited)
		return;

	SetFocus();
	mRightDown = true;
	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->HandleRightDown(this, e);

	wxPoint pos = e.GetPosition();
	mRightDownScreenPos = Float2((float)pos.x, (float)(mHeight-pos.y));
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnRightUp (wxMouseEvent& e)
{
	if (!mInited)
		return;

	wxPoint popupPos = e.GetPosition();

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
				PopupMenu(mEditMenu, popupPos.x, popupPos.y);
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

	wxPoint mousePos = e.GetPosition();
	wxPoint diff = mousePos - mLastMousePoint;

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->HandleMotion(this, e);

	if (mLeftDown)
	{
		Event *ent = InputEventSpace::CreateEventX(InputEventSpace::TouchMoved);
		InputEventData data;
		data.MState.X.Absoulate = mousePos.x;
		data.MState.Y.Absoulate = mHeight - mousePos.y;
		data.TState.X = data.MState.X;
		data.TState.Y = data.MState.Y;
		ent->SetData<InputEventData>(data);
		EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
	}

	mLastMousePoint = mousePos;
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
void RenderViewWindow::OnActorSky (wxCommandEvent& e)
{
	EditSystem::GetSingleton().GetEditMap()->CreateSky();
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
void RenderViewWindow::OnCreateEffect (wxCommandEvent& e)
{
	APoint pos = ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->GetSelectPoint();
	EditSystem::GetSingleton().GetEditMap()->CreateEffect(pos);
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnCreateUIFrame (wxCommandEvent& e)
{
	Object *obj = EditSystem::GetSingleton().GetSelection()->GetObjectAt(0);
	if (!obj)
	{
		wxMessageBox(PX2_LM.GetValue("Tip2"), PX2_LM.GetValue("Tip0"), wxOK);
		return;
	}

	if (obj->IsExactly(UIFrame::TYPE))
	{
		EditSystem::GetSingleton().GetEditMap()
			->CreateUIFrame(DynamicCast<UIFrame>(obj), mRightDownScreenPos);
	}
	else
	{
		wxMessageBox(PX2_LM.GetValue("Tip2"), PX2_LM.GetValue("Tip0"), wxOK);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnCreateUIPicBox (wxCommandEvent& e)
{
	Object *obj = EditSystem::GetSingleton().GetSelection()->GetObjectAt(0);
	if (!obj)
	{
		wxMessageBox(PX2_LM.GetValue("Tip2"), PX2_LM.GetValue("Tip0"), wxOK);
		return;
	}

	if (obj->IsExactly(UIFrame::TYPE))
	{
		Texture2D *tex = DynamicCast<Texture2D>(EditSystem::GetSingleton()
			.GetSelectedResource());
		std::string filename = EditSystem::GetSingleton()
			.GetSelectedResourceName();

		if (tex)
		{
			EditSystem::GetSingleton().GetEditMap()->CreateUIPicBox(
				DynamicCast<UIFrame>(obj), mRightDownScreenPos, 
				filename);
		}
	}
	else
	{
		wxMessageBox(PX2_LM.GetValue("Tip2"), PX2_LM.GetValue("Tip0"), wxOK);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnCreateUIAnimPixBox (wxCommandEvent& e)
{
	Object *obj = EditSystem::GetSingleton().GetSelection()->GetObjectAt(0);
	if (!obj)
	{
		wxMessageBox(PX2_LM.GetValue("Tip2"), PX2_LM.GetValue("Tip0"), wxOK);
		return;
	}

	if (obj->IsExactly(UIFrame::TYPE))
	{
		EditSystem::GetSingleton().GetEditMap()
			->CreateUIAnimPicBox(DynamicCast<UIFrame>(obj), mRightDownScreenPos);
	}
	else
	{
		wxMessageBox(PX2_LM.GetValue("Tip2"), PX2_LM.GetValue("Tip0"), wxOK);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnCreateUIStaticText (wxCommandEvent& e)
{
	Object *obj = EditSystem::GetSingleton().GetSelection()->GetObjectAt(0);
	if (!obj)
	{
		wxMessageBox(PX2_LM.GetValue("Tip2"), PX2_LM.GetValue("Tip0"), wxOK);
		return;
	}

	if (obj->IsExactly(UIFrame::TYPE))
	{
		EditSystem::GetSingleton().GetEditMap()
			->CreateUIStaticText(DynamicCast<UIFrame>(obj), mRightDownScreenPos);
	}
	else
	{
		wxMessageBox(PX2_LM.GetValue("Tip2"), PX2_LM.GetValue("Tip0"), wxOK);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnCreateUIButton (wxCommandEvent& e)
{
	Object *obj = EditSystem::GetSingleton().GetSelection()->GetObjectAt(0);
	if (!obj)
	{
		wxMessageBox(PX2_LM.GetValue("Tip2"), PX2_LM.GetValue("Tip0"), wxOK);
		return;
	}

	if (obj->IsExactly(UIFrame::TYPE))
	{
		EditSystem::GetSingleton().GetEditMap()
			->CreateUIButton(DynamicCast<UIFrame>(obj), mRightDownScreenPos);
	}
	else
	{
		wxMessageBox(PX2_LM.GetValue("Tip2"), PX2_LM.GetValue("Tip0"), wxOK);
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::OnCloneShare (wxCommandEvent& e)
{
	Object *obj = EditSystem::GetSingleton().GetSelection()->GetObjectAt(0);
	Actor *actor = DynamicCast<Actor>(obj);
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
	Object *obj = EditSystem::GetSingleton().GetSelection()->GetObjectAt(0);
	Actor *actor = DynamicCast<Actor>(obj);
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

	if (mBoundCtrl)
		mBoundCtrl->UpdateCtrl();

	CamMoveUpdate(detalSeconds);

	if (mCtrlScene)
		mCtrlScene->Update();
}
//----------------------------------------------------------------------------
void RenderViewWindow::CamMoveUpdate (double detalSeconds)
{
	if (!mScene)
		return;

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

	EditSystem::GetSingleton().SetShiftDown(shiftDown);

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
		moveValue_W = moveValue_W * 4.0f;
		moveValue_S = moveValue_S * 4.0f;
		moveValue_A = moveValue_A * 4.0f;
		moveValue_D = moveValue_D * 4.0f;
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
		MoveCamera(moveValueH, 0.0f);
	}
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

	bool isShowProjectInfo = false;
	bool isShowSceneBound = true;
	bool isSceneWired = false;
	bool isShowUI = true;
	bool isUIWired = false;
	bool isShowUIRange = true;
	bool isShowGrid = true;
	Project *proj = Project::GetSingletonPtr();
	if (proj)
	{
		mRenderer->SetClearColor(proj->GetColor());
		isShowProjectInfo = proj->IsShowProjectInfo();
		isShowSceneBound = proj->IsShowSceneBound();
		isSceneWired = proj->IsSceneWired();
		isShowUI = proj->IsShowUI();
		isUIWired = proj->IsUIWired();
		isShowUIRange = proj->IsShowUIRange();
		isShowGrid = proj->IsShowGrid();
	}

	mBoundCtrl->GetCtrlsGroup()->Culling = Movable::CULL_DYNAMIC;
	if (!isShowSceneBound)
	{
		mBoundCtrl->GetCtrlsGroup()->Culling = Movable::CULL_ALWAYS;
	}

	UIView *uiView = UIManager::GetSingleton().GetDefaultView();
	if (uiView)
	{
		uiView->ComputeVisibleSet();
	}

	if (mRenderer->PreDraw())
	{
		mRenderer->ClearBuffers();

		// scene
		if (mScene)
		{
			if (isSceneWired)
			{
				mRenderer->SetOverrideWireProperty(mSceneWireOverride);
			}
			else
			{
				mRenderer->SetOverrideWireProperty(0);
			}

			if (isShowGrid)
				mRenderer->Draw(mGridCuller.GetVisibleSet());
			
			mRenderer->Draw(mCuller.GetVisibleSet().Sort());
			mRenderer->SetOverrideWireProperty(0);
		}

		// ui
		Camera *uiCamera = UIManager::GetSingleton().GetDefaultView()
			->GetCamera();
		Culler &uiCuller = UIManager::GetSingleton().GetDefaultView()
			->GetCuller();
		mRenderer->SetCamera(uiCamera);
		if (isUIWired)
		{
			mRenderer->SetOverrideWireProperty(mUIWireOverride);
		}
		else
		{
			mRenderer->SetOverrideWireProperty(0);
		}
		if (isShowUI && Project::GetSingletonPtr())
		{
			mRenderer->Draw(uiCuller.GetVisibleSet());
		}
		mRenderer->SetOverrideWireProperty(0);
		if (Project::GetSingletonPtr())
		{
			if (isShowUIRange && isShowUI)
			{
				mRenderer->Draw(mProjRangeSegment);
			}
		}
		else
		{
			mRenderer->Draw(mPicBox);
		}
		mRenderer->SetCamera(mCamera);

		// help
		mRenderer->ClearDepthBuffer();
		mRenderer->Draw(mHelpCuller.GetVisibleSet());
		mRenderer->Draw(mCtrlCuller.GetVisibleSet().Sort());

		mRenderer->PostDraw();

		mRenderer->DisplayColorBuffer();
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::UpdateProjectTrans ()
{
	Project *proj = Project::GetSingletonPtr();
	if (!proj)
		return;

	float width = (float)proj->GetWidth();
	float height = (float)proj->GetHeight();

	float posX = 10.0f;
	float posZ = 10.0f;

	if (width < mWidth)
	{
		posX = ((float)mWidth - width)/2.0f;
	}

	if (height < mHeight)
	{
		posZ = ((float)mHeight - height)/2.0f;
	}

	APoint pos(posX, 0.0f, posZ);

	UIFrame *frame = UIManager::GetSingleton().GetDefaultView()
		->GetMainFrame();
	if (frame)
	{
		frame->LocalTransform.SetTranslate(pos);
	}

	if (mProjRangeSegment)
	{
		mProjRangeSegment->WorldTransform.SetTranslate(pos);
		mProjRangeSegment->WorldBoundIsCurrent = true;
	}
}
//----------------------------------------------------------------------------
void RenderViewWindow::UpdateProjectRange ()
{
	Project *proj = Project::GetSingletonPtr();
	if (!proj)
		return;

	float width = (float)proj->GetWidth();
	float height = (float)proj->GetHeight();

	VertexBufferAccessor vba(mProjRangeVFormat, mProjRangeVBuffer);
	vba.Position<Float3>(0) = Float3(0.0f, 0.0f, 0.0f);
	vba.Position<Float3>(1) = Float3(width, 0.0f, 0.0f);
	vba.Position<Float3>(2) = Float3(width, 0.0f, height);
	vba.Position<Float3>(3) = Float3(0.0f, 0.0f, height);
	vba.Position<Float3>(4) = Float3(0.0f, 0.0f, 0.0f);
	vba.Color<Float4>(0, 0) = Float4::RED;
	vba.Color<Float4>(0, 1) = Float4::RED;
	vba.Color<Float4>(0, 2) = Float4::RED;
	vba.Color<Float4>(0, 3) = Float4::RED;
	vba.Color<Float4>(0, 4) = Float4::RED;

	Renderer::UpdateAll(mProjRangeVBuffer);
}
//----------------------------------------------------------------------------
void RenderViewWindow::AdjustUICameraPercent ()
{
	float uiCameraPercent = 1.0f;
	Project *proj = Project::GetSingletonPtr();
	if (proj)
	{
		uiCameraPercent = proj->GetUICameraPercent();
	}

	UIManager::GetSingleton().GetDefaultView()->SetSize(mWidth*uiCameraPercent,
		mHeight*uiCameraPercent);
}
//----------------------------------------------------------------------------
void RenderViewWindow::CreateEditMenu ()
{
	mEditMenu = new wxMenu();

	//-- create
	wxMenu *createMenu = new wxMenu();
	mEditMenu->AppendSubMenu(createMenu, PX2_LM.GetValue("Create"));

	createMenu->Append(ID_CREATE_BOX, PX2_LM.GetValue("Box"));
	createMenu->Append(ID_CREATE_SPHERE, PX2_LM.GetValue("Sphere"));
	createMenu->Append(ID_CREATE_EFFECT, PX2_LM.GetValue("Effect"));
	wxMenu *uiMenu = new wxMenu();
	createMenu->AppendSubMenu(uiMenu, PX2_LM.GetValue("UI"));
	uiMenu->Append(ID_CREATE_UI_PICTUREBOX, PX2_LM.GetValue("PictureBox"));
	uiMenu->Append(ID_CREATE_UI_ANIMPICBOX, PX2_LM.GetValue("AnimPictureBox"));
	uiMenu->Append(ID_CREATE_UI_STATICTEXT, PX2_LM.GetValue("StaticText"));
	uiMenu->AppendSeparator();
	uiMenu->Append(ID_CREATE_UI_FRAME, PX2_LM.GetValue("Frame"));
	uiMenu->Append(ID_CREATE_UI_BUTTON, PX2_LM.GetValue("Button"));
	uiMenu->Append(ID_CREATE_UI_CHECKBOX, PX2_LM.GetValue("CheckBox"));
	uiMenu->Append(ID_CREATE_UI_EDITBOX, PX2_LM.GetValue("EditBox"));
	uiMenu->Append(ID_CREATE_UI_SLIDER, PX2_LM.GetValue("Slider"));
	uiMenu->Append(ID_CREATE_UI_PROGRESSBAR, PX2_LM.GetValue("ProgressBar"));

	//-- add
	wxMenu *addActorMenu = new wxMenu();
	mEditMenu->AppendSubMenu(addActorMenu, PX2_LM.GetValue("AddActor"));

	addActorMenu->Append(ID_ADDACTOR_MODEL, PX2_LM.GetValue("AddActorModel"));
	addActorMenu->Append(ID_ADDACTOR_EFFECT,PX2_LM.GetValue("AddActorEffect"));

	wxMenu *addActorMenu_Light = new wxMenu();
	addActorMenu->AppendSubMenu(addActorMenu_Light, PX2_LM.GetValue("AddActorLight"));
	addActorMenu_Light->Append(ID_ADDACTOR_LIGHT_POINT, PX2_LM.GetValue("AddActorLightPoint"));
	addActorMenu_Light->Append(ID_ADDACTOR_LIGHT_SPOT, PX2_LM.GetValue("AddActorLightSpot"));

	addActorMenu->Append(ID_ADDACTOR_SKY, PX2_LM.GetValue("AddActorSky"));

	//-- clone
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

	VertexColor4MaterialPtr mtl = new0 VertexColor4Material();
	mtl->GetAlphaProperty(0, 0)->BlendEnabled = true;
	mGrid->SetMaterialInstance(mtl->CreateInstance());
	mGridAxis->SetMaterialInstance(mtl->CreateInstance());

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
	if (mScene)
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

	UIView *uiView = UIManager::GetSingleton().GetDefaultView();
	if (uiView)
	{
		bool ctrlDown = wxGetKeyState(WXK_CONTROL);
		if (ctrlDown)
		{
			float uiCameraPercent = 1.0f;
			Project *proj = Project::GetSingletonPtr();
			if (proj)
			{
				uiCameraPercent = proj->GetUICameraPercent();
			}

			uiCameraPercent += Mathf::Sign(zoom)*0.1f;
			if (uiCameraPercent>=0.1f && uiCameraPercent<=10.0f)
			{
				if (proj)
				{
					proj->SetUICameraPercent(uiCameraPercent);
					AdjustUICameraPercent();
				}
			}
		}
	}
	
	CameraChangedSimplyTerrain();
}
//----------------------------------------------------------------------------
void RenderViewWindow::PanCamera (const float &horz, const float &vert)
{
	if (mScene)
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
	
	CameraChangedSimplyTerrain();
}
//----------------------------------------------------------------------------
void RenderViewWindow::MoveCamera (const float &horz, const float &vert)
{
	if (mScene)
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
	
	CameraChangedSimplyTerrain();
}
//----------------------------------------------------------------------------
void RenderViewWindow::RolateCamera (const float &horz, const float &vert)
{
	if (mScene)
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

	CameraChangedSimplyTerrain();
}
//----------------------------------------------------------------------------
void RenderViewWindow::CameraChangedSimplyTerrain ()
{
	//TerrainActor *terActor = Project::GetSingleton().GetScene()
	//	->GetTerrainActor();
	//if (terActor)
	//{
	//	bool useLod = terActor->IsUseLod();
	//	LODTerrain *lodTer = terActor->GetLODTerrain();
	//	if (useLod && lodTer)
	//	{
	//		lodTer->Simplify();
	//	}
	//}
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

	if (EditorEventSpace::IsEqual(event, EditorEventSpace::NewProject))
	{
		UpdateProjectRange();
		UpdateProjectTrans();
		AdjustUICameraPercent();

		mRenderer->SetClearColor(Project::GetSingleton().GetColor());
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::LoadedProject))
	{
		UpdateProjectRange();
		UpdateProjectTrans();
		AdjustUICameraPercent();

		mRenderer->SetClearColor(Project::GetSingleton().GetColor());
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::UICameraPercentChanged))
	{
		AdjustUICameraPercent();
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::ClosedProject))
	{
		mRenderer->SetClearColor(mBackGroundColor);
		AdjustUICameraPercent();
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::NewScene)
		|| EditorEventSpace::IsEqual(event, EditorEventSpace::LoadedScene))
	{
		Scene *scene = 0;
		
		if (Project::GetSingletonPtr())
			scene = Project::GetSingleton().GetScene();

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
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::CloseScene))
	{
		SetScene(0);
		SetHelpScene(0);
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