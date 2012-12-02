/*
*
* 文件名称	：	PX2Application.cpp
*
*/

#include "PX2Application.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
ApplicationBase::AppInitlizeFun ApplicationBase::msAppInitlizeFun = 0;
ApplicationBase::AppTernamateFun ApplicationBase::msAppTernamateFun = 0;
ApplicationBase* ApplicationBase::msApplication = 0;
ApplicationBase::EntryPoint ApplicationBase::msEntry = 0;
//----------------------------------------------------------------------------
ApplicationBase::ApplicationBase ()
	:
	mWindowTitle("Application"),
	mXPosition(0),
	mYPosition(0),
	mWidth(800),
	mHeight(600),
	mAllowResize(true),
	mClearColor(Float4(1.0f, 0.0f, 0.0f, 1.0f)),
	mColorFormat(Texture::TF_A8R8G8B8),
	mRenderer(0),
	mDepthStencilFormat(Texture::TF_D24S8),
	mNumMultisamples(0),
	mRoot(0),
	mEventWorld(0),
	mResMan(0),
	mGameMan(0),
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
ApplicationBase::~ApplicationBase ()
{
}
//----------------------------------------------------------------------------
bool ApplicationBase::Initlize ()
{
#ifdef PX2_USE_MEMORY
	Memory::Initialize();
#endif

	LogInitlize();
	//LogAddFileHandler("PX2Application_Log.txt", 1, LT_ENGINE|LT_INFO);
	LoadAddOutputWindowHandler(1, LT_ENGINE|LT_INFO);

	mResMan = new0 ResourceManager();

	mEventWorld = new0 EventWorld();
	PX2_UNUSED(mEventWorld);

	mRoot = new0 GraphicsRoot();
	mRoot->Initlize();

	mGameMan = new0 GameManager();
	mGameMan->LoadBoost("Data/boost.xml");
	int width = mGameMan->GetBoostWidth();
	int height = mGameMan->GetBoostHeight();
	if (0!=width && 0!=height)
	{
		mWidth = width;
		mHeight = height;
	}

	OnInitlizeApp();
	OnInitlize();

	return true;
}
//----------------------------------------------------------------------------
void ApplicationBase::OnIdle ()
{
}
//----------------------------------------------------------------------------
bool ApplicationBase::OnResume()
{
	return true;
}
//----------------------------------------------------------------------------
bool ApplicationBase::OnPause()
{
	return true;
}
//----------------------------------------------------------------------------
bool ApplicationBase::Ternamate ()
{
	OnTernamate();

	if (mResMan)
	{
		delete0(mResMan);
		ResourceManager::Set(0);
	}

	if (mGameMan)
	{
		delete0(mGameMan);
		GameManager::Set(0);
	}

	if (mRoot)
	{
		mRoot->Terminate();
		delete0(mRoot);
		GraphicsRoot::Set(0);
	}

	if (mEventWorld)
	{
		delete0(mEventWorld);
		EventWorld::Set(0);
	}

	OnTernamateApp();

	LogShutdown();

#ifdef PX2_USE_MEMORY
	Memory::Terminate("PX2Application_MemoryReport.txt", false);
#endif

	return true;
}
//----------------------------------------------------------------------------
bool ApplicationBase::OnInitlize ()
{
	return true;
}
//----------------------------------------------------------------------------
bool ApplicationBase::OnTernamate ()
{
	return true;
}
//----------------------------------------------------------------------------
int ApplicationBase::Main (int numArguments, char** arguments)
{
	return 1;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 渲染性能衡量
//----------------------------------------------------------------------------
void ApplicationBase::ResetTime ()
{
	mLastTime = -1.0f;
}
//----------------------------------------------------------------------------
void ApplicationBase::MeasureTime ()
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
void ApplicationBase::UpdateFrameCount ()
{
	mFrameCount++;
}
//----------------------------------------------------------------------------
void ApplicationBase::DrawFrameRate (int x, int y, const Float4& color)
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
