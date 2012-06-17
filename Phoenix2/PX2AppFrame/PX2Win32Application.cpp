/*
*
* 文件名称	：	PX2Win32Application.cpp
*
*/

#include "PX2Win32Application.hpp"

#ifdef PX2_USE_DX9
#include "PX2Dx9RendererInput.hpp"
#include "PX2Dx9RendererData.hpp"
#endif

#ifdef PX2_USE_OPENGL
#include "PX2WglRendererInput.hpp"
#include "PX2WglRendererData.hpp"
#endif

using namespace PX2;

LRESULT CALLBACK MsWindowEventHandler (HWND handle, UINT message,
									   WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			break;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}
//----------------------------------------------------------------------------
Win32Application::Win32Application ()
:
mWindowTitle("TdWin32Application"),
mClearColor(Float4(1.0f, 0.0f, 0.0f, 1.0f)),
mXPosition(0),
mYPosition(0),
mWidth(800),
mHeight(600),
mAllowResize(true),
mColorFormat(Texture::TF_A8R8G8B8),
mDepthStencilFormat(Texture::TF_D24S8),
mNumMultisamples(0),
mLastTime(-1.0),
mAccumulatedTime(0.0),
mFrameRate(0.0),
mFrameCount(0),
mAccumulatedFrameCount(0),
mTimer(30),
mMaxTimer(30)
{
}
//----------------------------------------------------------------------------
Win32Application::~Win32Application ()
{
}
//----------------------------------------------------------------------------
void Win32Application::Run ()
{
	Initlize ();
	OnInitlize ();

	// 预清除背景色
	mRenderer->ClearBuffers();

	// 显示窗口
	ShowWindow(mhWnd, SW_SHOWNORMAL);
	UpdateWindow(mhWnd);

	// 消息循环
	bool applicationRunning = true;
	while (applicationRunning)
	{
		MSG msg;
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				applicationRunning = false;
				continue;
			}

			HACCEL accel = 0;
			if (!TranslateAccelerator(mhWnd, accel, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}
		else
		{
			if (OISEventAdapter::GetSingletonPtr())
				OISEventAdapter::GetSingletonPtr()->Update();

			if (EventWorld::GetSingletonPtr())
				EventWorld::GetSingletonPtr()->Update();

			OnIdle();
		}
	}

	OnTernamate ();
	Ternamate ();
}
//----------------------------------------------------------------------------
bool Win32Application::Initlize ()
{
	Application::Initlize();

	// === 创建渲染窗口 ===

	// 注册窗口类
	static char sWindowClass[] = "Phoenix2 Application";
	WNDCLASS wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = MsWindowEventHandler;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = 0;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = sWindowClass;
	wc.lpszMenuName  = 0;
	RegisterClass(&wc);

	DWORD dwStyle;
	if (mAllowResize)
	{
		dwStyle = WS_OVERLAPPEDWINDOW;
	}
	else
	{
		dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	}

	// 请求特定客户区大小的窗口大小
	RECT rect = { 0, 0, mWidth-1, mHeight-1 };
	AdjustWindowRect(&rect, dwStyle, FALSE);

	// 创建窗口
	mhWnd = CreateWindow(sWindowClass, mWindowTitle.c_str(),
		dwStyle, mXPosition, mYPosition,
		rect.right - rect.left + 1, rect.bottom - rect.top + 1, 0, 0, 0, 0);

	// === 渲染器 ===

#ifdef PX2_USE_DX9
	// 创建渲染器
	mInput.mWindowHandle = mhWnd;
	mInput.mDriver = Direct3DCreate9(D3D_SDK_VERSION);
	assertion(mInput.mDriver != 0, "Failed to create Direct3D9\n");
	mRenderer = new0 Renderer(mInput, mWidth, mHeight,
		mColorFormat, mDepthStencilFormat, mNumMultisamples);
#endif

#ifdef PX2_USE_OPENGL
	RendererInput input;
	input.mWindowHandle = mhWnd;
	input.mPixelFormat = 0;
	input.mRendererDC = 0;
	input.mDisableVerticalSync = true;
	mRenderer = new0 Renderer(input, mWidth, mHeight,
		mColorFormat, mDepthStencilFormat, mNumMultisamples);

	int numMultisamples = mRenderer->GetNumMultisamples();
	if (numMultisamples > 0)
	{
		int attributes[256], pos = 0;
		attributes[pos++] = WGL_SUPPORT_OPENGL_ARB;
		attributes[pos++] = 1;
		attributes[pos++] = WGL_DRAW_TO_WINDOW_ARB;
		attributes[pos++] = 1;
		attributes[pos++] = WGL_ACCELERATION_ARB;
		attributes[pos++] = WGL_FULL_ACCELERATION_ARB;
		attributes[pos++] = WGL_PIXEL_TYPE_ARB;
		attributes[pos++] = WGL_TYPE_RGBA_ARB;
		attributes[pos++] = WGL_RED_BITS_ARB;
		attributes[pos++] = 8;
		attributes[pos++] = WGL_GREEN_BITS_ARB;
		attributes[pos++] = 8;
		attributes[pos++] = WGL_BLUE_BITS_ARB;
		attributes[pos++] = 8;
		attributes[pos++] = WGL_ALPHA_BITS_ARB;
		attributes[pos++] = 8;
		attributes[pos++] = WGL_DEPTH_BITS_ARB;
		attributes[pos++] = 24;
		attributes[pos++] = WGL_STENCIL_BITS_ARB;
		attributes[pos++] = 8;
		attributes[pos++] = WGL_DOUBLE_BUFFER_ARB;
		attributes[pos++] = 1;
		attributes[pos++] = WGL_SAMPLE_BUFFERS_ARB;
		attributes[pos++] = 1;
		attributes[pos++] = WGL_SAMPLES_ARB;
		attributes[pos++] = numMultisamples;
		attributes[pos++] = 0; // list is zero-terminated

		unsigned int numFormats = 0;
		BOOL successful = wglChoosePixelFormatARB(input.mRendererDC,
			attributes, 0, 1, &input.mPixelFormat, &numFormats);
		if (successful && numFormats > 0)
		{
			delete0(mRenderer);

			input.mWindowHandle = mhWnd;
			mRenderer = new0 Renderer(input, mWidth, mHeight, mColorFormat,
				mDepthStencilFormat, mNumMultisamples);
		}
	}
#endif

	mRenderer->SetClearColor(mClearColor);

	mCamera = new0 Camera();
	mRenderer->SetCamera(mCamera);

	// 事件系统
	mEventWorld = new0 EventWorld();
	mOISEventAdapter = new0 OISEventAdapter();
	mOISEventAdapter->AddParam(PtrToInt(mhWnd));
	mOISEventAdapter->Initlize(mWidth, mHeight);

	mResManager = new0 ResourceManager();

	// UI
	mUIManager = new0 UIManager(mEventWorld, (float)mWidth, (float)mHeight);
	
	mEventWorld->ComeIn(mUIManager);

	return true;
}
//----------------------------------------------------------------------------
bool Win32Application::OnInitlize ()
{
	return true;
}
//----------------------------------------------------------------------------
bool Win32Application::OnTernamate ()
{
	return true;
}
//----------------------------------------------------------------------------
bool Win32Application::Ternamate ()
{
	mCamera = 0;

	delete0(mRenderer);
#ifdef PX2_USE_DX9
	mInput.mDriver->Release();
#endif

	mEventWorld->GoOut(mUIManager);

	if (mOISEventAdapter)
		mOISEventAdapter->Ternamate();
	mEventWorld = 0;

	// handlers 需要在消息世界Ternamate之后释放内存
	mUIManager = 0;
	mOISEventAdapter = 0;

	if (mResManager)
		delete0(mResManager);

	Application::Ternamate();

	return true;
}
//----------------------------------------------------------------------------
void Win32Application::OnIdle ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 渲染性能衡量
//----------------------------------------------------------------------------
void Win32Application::ResetTime ()
{
    mLastTime = -1.0f;
}
//----------------------------------------------------------------------------
void Win32Application::MeasureTime ()
{
    // start performance measurements
    if (mLastTime == -1.0)
    {
        mLastTime = GetTimeInSeconds();
        mAccumulatedTime = 0.0;
        mFrameRate = 0.0;
        mFrameCount = 0;
        mAccumulatedFrameCount = 0;
        mTimer = mMaxTimer;
    }

    // accumulate the time only when the miniature time allows it
    if (--mTimer == 0)
    {
        double dCurrentTime = GetTimeInSeconds();
        double dDelta = dCurrentTime - mLastTime;
        mLastTime = dCurrentTime;
        mAccumulatedTime += dDelta;
        mAccumulatedFrameCount += mFrameCount;
        mFrameCount = 0;
        mTimer = mMaxTimer;
    }
}
//----------------------------------------------------------------------------
void Win32Application::UpdateFrameCount ()
{
    mFrameCount++;
}
//----------------------------------------------------------------------------
void Win32Application::DrawFrameRate (int x, int y, const Float4& color)
{
    if (mAccumulatedTime > 0.0)
    {
        mFrameRate = mAccumulatedFrameCount/mAccumulatedTime;
    }
    else
    {
        mFrameRate = 0.0;
    }

    char message[256];
    sprintf(message, "fps: %.1lf", mFrameRate);
    mRenderer->Draw(x, y, color, message);
}
//----------------------------------------------------------------------------
