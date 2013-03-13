/*
*
* ÎÄ¼þÃû³Æ	£º	PX2PreViewWindow.cpp
*
*/

#include "PX2PreViewWindow.hpp"
#include "PX2EditEventType.hpp"
using namespace PX2Editor;
using namespace PX2;

//----------------------------------------------------------------------------
#define ID_PREVIEWTIMERR wxID_HIGHEST+3501
//----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC_CLASS(PX2Editor::PreViewWindow, wxWindow)
BEGIN_EVENT_TABLE(PreViewWindow, wxWindow)
	EVT_TIMER(ID_PREVIEWTIMERR, PreViewWindow::OnTimer)
	EVT_PAINT(PreViewWindow::OnPaint)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
PreViewWindow::PreViewWindow ()
	:wxWindow(0, wxID_ANY),
	mInited(false),
	mPreViewType(PVT_NONE),
	mRenderer(0)
{
}
//----------------------------------------------------------------------------
PreViewWindow::PreViewWindow (wxWindow *parent)
	:
wxWindow(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 150)),
	mInited(false),
	mPreViewType(PVT_NONE),
	mRenderer(0)
{
}
//----------------------------------------------------------------------------
PreViewWindow::~PreViewWindow ()
{
	if (mRenderer)
	{
		delete0(mRenderer);
		mRenderer = 0;
	}
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
		mPreViewType = PVT_TEXTURE;
		SetTexture(d2Tex);
	}
	else
	{	
		mPreViewType = PVT_NONE;
	}
}
//----------------------------------------------------------------------------
void PreViewWindow::OnTimer (wxTimerEvent& event)
{
	Update();
	DrawScene();
}
//----------------------------------------------------------------------------
void PreViewWindow::OnPaint (wxPaintEvent& e)
{
	wxPaintDC dc(this);
}
//----------------------------------------------------------------------------
void PreViewWindow::OnSize (wxSizeEvent& e)
{
	if (!mInited)
		return;

	wxSize sz = GetClientSize();
	mWidth = sz.GetX();
	mHeight = sz.GetY();
	mRenderer->ResizeWindow(mWidth, mHeight);
}
//----------------------------------------------------------------------------
void PreViewWindow::DoEnter ()
{
}
//----------------------------------------------------------------------------
void PreViewWindow::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::SetPreView))
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
void PreViewWindow::Initlize ()
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

	mCamera = new0 Camera();
	mPreViewTextureCamera = ScreenTarget::CreateCamera();

	mVFormat = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);
	mScreenMesh = ScreenTarget::CreateRectangle(mVFormat, mWidth, mHeight,
		0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	mPreViewMaterial = new Texture2DMaterial();
	mPreViewMaterial->GetAlphaProperty(0, 0)->BlendEnabled = true;

	mPreViewTimer.SetOwner(this, ID_PREVIEWTIMERR);
	mPreViewTimer.Start(100);

	mInited = true;
}
//----------------------------------------------------------------------------
void PreViewWindow::SetTexture (PX2::Texture2D *texture)
{
	mPreViewTexture = texture;
	mScreenMesh->SetMaterialInstance(mPreViewMaterial
		->CreateInstance(texture));

	mScene = mScreenMesh;
}
//----------------------------------------------------------------------------
void PreViewWindow::SetModel (PX2::Movable *object)
{
	mPreViewObject = object;
	mScene = object;
}
//----------------------------------------------------------------------------
void PreViewWindow::Update ()
{

}
//----------------------------------------------------------------------------
void PreViewWindow::DrawScene ()
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
		if (mScene)
		{
			mCuller.ComputeVisibleSet(mScene);
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