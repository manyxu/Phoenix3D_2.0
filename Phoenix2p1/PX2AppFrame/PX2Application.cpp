/*
*
* 文件名称	：	PX2Application.cpp
*
*/

#include "PX2Application.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
LRESULT CALLBACK MsWindowEventHandler (HWND handle, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		switch (wParam)
		{
		case SIZE_RESTORED:
			ApplicationBase::msApplication->WillEnterForeground();
			break;
		case SIZE_MINIMIZED:
			ApplicationBase::msApplication->DidEnterBackground();
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}
#endif
//----------------------------------------------------------------------------
Application::Application ()
{
#if defined(_WIN32) || defined(WIN32)
	mhWnd = 0;
#endif
}
//----------------------------------------------------------------------------
Application::~Application ()
{
}
//----------------------------------------------------------------------------
int Application::Entry (int numArguments, char** arguments)
{
	Application* theApp = (Application*)msApplication;
	return theApp->Main(numArguments, arguments);
}
//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
int Application::Main (int numArguments, char** arguments)
{
	PX2_UNUSED(numArguments);
	PX2_UNUSED(arguments);

	Initlize ();

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
			OnIdle();
		}
	}

	Ternamate ();

	return 0;
}
#endif
//----------------------------------------------------------------------------
void Application::OnIdle ()
{
	if (mInputEventAdapter)
	{
		mInputEventAdapter->Update();
	}

	ApplicationBase::OnIdle();
}
//----------------------------------------------------------------------------
#if defined __ANDROID__
int Application::Main (int numArguments, char** arguments)
{
	return 0;
}
#endif
//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
bool Application::OnInitlizeApp ()
{
	// === 创建渲染窗口 ===

	// 注册窗口类
	static char sWindowClass[] = "Phoenix2 ApplicationBase";
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

	// 居中
	RECT rcDesktop, rcWindow;
	GetWindowRect(GetDesktopWindow(), &rcDesktop);

	HWND hTaskBar = FindWindow(TEXT("Shell_TrayWnd"), NULL);
	if (hTaskBar != NULL)
	{
		APPBARDATA abd;

		abd.cbSize = sizeof(APPBARDATA);
		abd.hWnd = hTaskBar;

		SHAppBarMessage(ABM_GETTASKBARPOS, &abd);
		SubtractRect(&rcDesktop, &rcDesktop, &abd.rc);
	}
	GetWindowRect(mhWnd, &rcWindow);
	int offsetX = (rcDesktop.right - rcDesktop.left - (rcWindow.right - rcWindow.left)) / 2;
	offsetX = (offsetX > 0) ? offsetX : rcDesktop.left;
	int offsetY = (rcDesktop.bottom - rcDesktop.top - (rcWindow.bottom - rcWindow.top)) / 2;
	offsetY = (offsetY > 0) ? offsetY : rcDesktop.top;
	SetWindowPos(mhWnd, 0, offsetX, offsetY, 0, 0, SWP_NOCOPYBITS | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	mXPosition = offsetX;
	mYPosition = offsetY;

	// === Input ===
	mInputEventAdapter->AddParam((int)mhWnd);
	mInputEventAdapter->Initlize();
	mInputEventAdapter->GetInputManager()->SetSize(Sizef((float)mWidth, (float)mHeight));

	// === 渲染器 ===

#ifdef PX2_USE_DX9
	// 创建渲染器
	mInput.mWindowHandle = mhWnd;
	mInput.mDriver = Direct3DCreate9(D3D_SDK_VERSION);
	assertion(mInput.mDriver != 0, "Failed to create Direct3D9\n");
	mRenderer = new0 Renderer(mInput, mWidth, mHeight,
		mColorFormat, mDepthStencilFormat, mNumMultisamples);
#endif

#ifdef PX2_USE_OPENGLES2
	mInput.mWindowHandle = mhWnd;
	mInput.mRendererDC = GetDC(mhWnd);
	mRenderer = new0 Renderer(mInput, mWidth, mHeight,
		mColorFormat, mDepthStencilFormat, mNumMultisamples);
#endif

	mRenderer->SetClearColor(mClearColor);

	mCamera = new0 Camera();
	mRenderer->SetCamera(mCamera);
	mRoot->SetCamera(mCamera);
	UIManager::GetSingleton().GetDefaultView()->SetRenderer(mRenderer);

	return true;
}
#endif
//----------------------------------------------------------------------------
#ifdef __ANDROID__
bool Application::OnInitlizeApp ()
{
#ifdef PX2_USE_OPENGLES2
	mRenderer = new0 Renderer(mInput, mWidth, mHeight,
		mColorFormat, mDepthStencilFormat, mNumMultisamples);
#endif

	mRenderer->SetClearColor(mClearColor);

	mCamera = new0 Camera();
	mRenderer->SetCamera(mCamera);
	mRoot->SetCamera(mCamera);
	UIManager::GetSingleton().GetDefaultView()->SetRenderer(mRenderer);

	return true;
}
#endif
//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
bool Application::OnTernamateApp()
{
	mCamera = 0;

	if (mRenderer)
	{
		delete0(mRenderer);
#ifdef PX2_USE_DX9
		mInput.mDriver->Release();
#endif
	}
	return true;
}
#endif
//----------------------------------------------------------------------------
#ifdef __ANDROID__
bool Application::OnTernamateApp()
{
	ApplicationBase::OnTernamate();

	mCamera = 0;

	if (mRenderer)
	{
		delete0(mRenderer);
	}

	return true;
}
#endif
//----------------------------------------------------------------------------