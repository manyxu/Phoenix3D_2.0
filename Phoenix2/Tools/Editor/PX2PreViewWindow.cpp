/*
*
* 文件名称	：	PX2PreViewWindow.cpp
*
*/

#include "PX2PreViewWindow.hpp"
using namespace PX2Editor;
using namespace PX2;

#define ID_TIMERR wxID_HIGHEST+1000
//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC_CLASS(PX2Editor::PreViewWindow, wxWindow)
BEGIN_EVENT_TABLE(PreViewWindow, wxWindow)
EVT_TIMER(ID_TIMERR, PreViewWindow::OnTimer)
EVT_SIZE(PreViewWindow::OnSize)
EVT_MOVE(PreViewWindow::OnMove)
EVT_PAINT(PreViewWindow::OnPaint)
EVT_KEY_DOWN(PreViewWindow::OnKeyDown)
EVT_KEY_UP(PreViewWindow::OnKeyUp)
EVT_CHAR(PreViewWindow::OnChar)
EVT_LEFT_DOWN(PreViewWindow::OnLeftDown)
EVT_LEFT_UP(PreViewWindow::OnLeftUp)
EVT_MIDDLE_DOWN(PreViewWindow::OnMiddleDown)
EVT_MIDDLE_UP(PreViewWindow::OnMiddleUp)
EVT_MOUSEWHEEL(PreViewWindow::OnMouseWheel)
EVT_RIGHT_DOWN(PreViewWindow::OnRightDown)
EVT_RIGHT_UP(PreViewWindow::OnRightUp)
EVT_MOTION(PreViewWindow::OnMotion)
EVT_ENTER_WINDOW(PreViewWindow::OnEnterWindow)
EVT_LEAVE_WINDOW(PreViewWindow::OnLeaveWindow)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
PreViewWindow::PreViewWindow()
{
}	
//-----------------------------------------------------------------------------
PreViewWindow::PreViewWindow(wxWindow* parent)
:
wxWindow(parent, -1, wxDefaultPosition, wxSize(200, 150)),
mCamera(0),
mLeftDown(false),
mMiddleDown(false),
mRightDown(false),
mActive(false),
mInited(false),
mWindowIndex(-1)
{
	mTimer.SetOwner(this, ID_TIMERR);
	mTimer.Start(33);
}
//-----------------------------------------------------------------------------
PreViewWindow::~PreViewWindow()
{
	//#ifdef PX2_USE_DX9
	delete0(mRenderer);
	mInput.mDriver->Release();
	//#endif
}
//----------------------------------------------------------------------------
void PreViewWindow::Initialize()
{
	// Renderer
	mWidth = 200;
	mHeight = 150;
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
	mBackGroundColor = Float4(0.4f, 0.4f, 0.4f, 0.0f);
	mRenderer->SetClearColor(mBackGroundColor);

	// 相机
	mCamera = new0 Camera();
	mPreViewTextureCamera = ScreenTarget::CreateCamera();

	// Texture
	mVFormat = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);
	mScreenMesh = ScreenTarget::CreateRectangle(mVFormat, mWidth, mHeight,
		0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	mPreViewMaterial = new Texture2DMaterial();

	mInited = true;
}
//----------------------------------------------------------------------------
void PreViewWindow::SetObject (PX2::Object *obj)
{
	if (!obj)
	{
		mPreViewType = PVT_NONE;
		return;
	}

	Texture2DPtr d2Tex = DynamicCast<Texture2D>(obj);
	if (d2Tex)
	{
		SetTexture(d2Tex);
	}
	else
	{	
		mPreViewType = PVT_NONE;
	}
}
//----------------------------------------------------------------------------
void PreViewWindow::SetTexture (PX2::Texture2D *texture)
{
	mPreViewTexture = texture;
	mPreViewType = PVT_TEXTURE;
	mScreenMesh->SetMaterialInstance(mPreViewMaterial
		->CreateInstance(texture));
	mGraphicsScene = mScreenMesh;
}
//----------------------------------------------------------------------------
void PreViewWindow::SetModel (PX2::Movable *object)
{
	mPreViewObject = object;
	mPreViewType = PVT_MODEL;

	mGraphicsScene = object;
}
//----------------------------------------------------------------------------
void PreViewWindow::Update ()
{
}
//----------------------------------------------------------------------------
void PreViewWindow::Draw ()
{
	if (!mInited)
		return;

	if (PVT_TEXTURE == mPreViewType)
	{
		mRenderer->SetCamera(mPreViewTextureCamera);
	}
	else
	{
		mCuller.SetCamera(mCamera);
		mRenderer->SetCamera(mCamera);
		if (mGraphicsScene)
		{
			mCuller.ComputeVisibleSet(mGraphicsScene);
		}
	}

	if (mRenderer->PreDraw())
	{
		mRenderer->ClearBuffers();

		if (PVT_TEXTURE == mPreViewType)
		{
			mRenderer->Draw(mScreenMesh);
		}
		else
		{
			mRenderer->Draw(mCuller.GetVisibleSet().Sort());
		}

		mRenderer->PostDraw();
		mRenderer->DisplayColorBuffer();
	}
}
//----------------------------------------------------------------------------
void PreViewWindow::OnSize(wxSizeEvent& e)
{
	if (!mInited)
		return;

	wxSize sz = GetClientSize();

	mWidth = sz.GetX();
	mHeight = sz.GetY();
	mRenderer->ResizeWindow(sz.x, sz.y);
}
//----------------------------------------------------------------------------
void PreViewWindow::OnMove(wxMoveEvent& e)
{
}
//----------------------------------------------------------------------------
void PreViewWindow::OnPaint(wxPaintEvent& e)
{
	// Keep wxWidgets happy
	wxPaintDC dc(this);
}
//----------------------------------------------------------------------------
void PreViewWindow::OnLeftDown(wxMouseEvent& e)
{
	mLeftDown = true;
}
//----------------------------------------------------------------------------
void PreViewWindow::OnLeftUp(wxMouseEvent& e)
{
	mLeftDown = false;
}
//----------------------------------------------------------------------------
void PreViewWindow::OnMiddleDown(wxMouseEvent& e)
{
	mMiddleDown = true;
}
//----------------------------------------------------------------------------
void PreViewWindow::OnMiddleUp(wxMouseEvent& e)
{
	mMiddleDown = false;
}
//----------------------------------------------------------------------------
void PreViewWindow::OnMouseWheel(wxMouseEvent& e)
{
}
//----------------------------------------------------------------------------
void PreViewWindow::OnRightDown(wxMouseEvent& e)
{
	mRightDown = true;
}
//----------------------------------------------------------------------------
void PreViewWindow::OnRightUp(wxMouseEvent& e)
{
	mRightDown = false;
}
//----------------------------------------------------------------------------
void PreViewWindow::OnMotion(wxMouseEvent& e)
{
	wxPoint point = e.GetPosition();
	wxPoint diff = point - mLastMousePoint;

	mLastMousePoint = point;
}
//----------------------------------------------------------------------------
void PreViewWindow::OnKeyDown(wxKeyEvent& e)
{
}
//----------------------------------------------------------------------------
void PreViewWindow::OnKeyUp(wxKeyEvent& e)
{
}
//----------------------------------------------------------------------------
void PreViewWindow::OnChar(wxKeyEvent& e)
{
}
//----------------------------------------------------------------------------
void PreViewWindow::OnEnterWindow(wxMouseEvent& e)
{
	SetFocus();
	mActive = true;
}
//----------------------------------------------------------------------------
void PreViewWindow::OnLeaveWindow(wxMouseEvent& e)
{
	mActive = false;
}
//----------------------------------------------------------------------------
void PreViewWindow::OnMouseCaptureLost(wxMouseCaptureLostEvent& e)
{

}
//----------------------------------------------------------------------------
void PreViewWindow::DoEnter ()
{

}
//----------------------------------------------------------------------------
void PreViewWindow::DoUpdate ()
{

}
//----------------------------------------------------------------------------
void PreViewWindow::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, 
		EditorEventSpace::SetPreViewObject) ||
		EditorEventSpace::IsEqual(event, 
		EditorEventSpace::SetTerrainTexturePreView))
	{
		PX2::Object *obj = event->GetData<PX2::Object*>();
		SetObject(obj);
	}
}
//----------------------------------------------------------------------------
void PreViewWindow::DoLeave ()
{

}
//----------------------------------------------------------------------------
void PreViewWindow::OnTimer (wxTimerEvent& event)
{
	Update();

	Draw();
}
//----------------------------------------------------------------------------