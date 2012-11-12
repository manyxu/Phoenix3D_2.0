/*
*
* 文件名称	：	PX2Application.cpp
*
*/

#include "PX2Application.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Application::AppInitlizeFun Application::msAppInitlizeFun = 0;
Application::AppTernamateFun Application::msAppTernamateFun = 0;
Application* Application::msApplication = 0;
Application::EntryPoint Application::msEntry = 0;
//----------------------------------------------------------------------------
Application::Application ()
	:
mClearColor(Float4(1.0f, 0.0f, 0.0f, 1.0f)),
	mColorFormat(Texture::TF_A8R8G8B8),
	mRenderer(0),
	mDepthStencilFormat(Texture::TF_D24S8),
	mNumMultisamples(0),
	mRoot(0),
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
Application::~Application ()
{
}
//----------------------------------------------------------------------------
bool Application::Initlize ()
{
#ifdef PX2_USE_MEMORY
	Memory::Initialize();
#endif

	mRoot = new0 GraphicsRoot();
	if (mRoot)
		mRoot->Initlize();

	OnInitlize();

	return true;
}
//----------------------------------------------------------------------------
bool Application::OnInitlize ()
{
	return true;
}
//----------------------------------------------------------------------------
void Application::OnIdle ()
{
}
//----------------------------------------------------------------------------
bool Application::OnResume()
{
	return true;
}
//----------------------------------------------------------------------------
bool Application::OnPause()
{
	return true;
}
//----------------------------------------------------------------------------
bool Application::Ternamate ()
{
	OnTernamate();

	if (mRoot)
		mRoot->Terminate();

	delete0(mRoot);

#ifdef PX2_USE_MEMORY
	Memory::Terminate("MemoryReport.txt");
#endif

	return true;
}
//----------------------------------------------------------------------------
bool Application::OnTernamate ()
{
	return true;
}
int Application::Main (int numArguments, char** arguments)
{
	return 1;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 渲染性能衡量
//----------------------------------------------------------------------------
void Application::ResetTime ()
{
	mLastTime = -1.0f;
}
//----------------------------------------------------------------------------
void Application::MeasureTime ()
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
void Application::UpdateFrameCount ()
{
	mFrameCount++;
}
//----------------------------------------------------------------------------
void Application::DrawFrameRate (int x, int y, const Float4& color)
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
int main (int numArguments, char* arguments[])
{
	Application::msAppInitlizeFun();

	int exitCode = Application::msEntry(numArguments, arguments);

	Application::msAppTernamateFun();

	return exitCode;
}
//----------------------------------------------------------------------------
