/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ApplicationBase.cpp
*
*/

#include "PX2Application.hpp"
#include "PX2ToLua.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
bool ApplicationBase::msIsInitlized = false;
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
	mScriptMan(0),
	mInputEventAdapter(0),
	mGameMan(0),
	mUIManager(0),
	mProject(0),
	mResMan(0),
	mFrameRate(0.0f),
	mNumFrames(0),
	mFrameTime(0.0f),
	mApplicationTime(0.0f),
	mLastApplicationTime(0.0f),
	mElapsedTime(0.0f),
	mIsTimeInited(false)
{
}
//----------------------------------------------------------------------------
ApplicationBase::~ApplicationBase ()
{
}
//----------------------------------------------------------------------------
bool ApplicationBase::IsInitlized ()
{
	return msIsInitlized;
}
//----------------------------------------------------------------------------
bool ApplicationBase::Initlize ()
{
	if (msIsInitlized)
		return true;

	// srand
	srand((int)GetTimeInMicroseconds());

#ifdef PX2_USE_MEMORY
	Memory::Initialize();
#endif

	LogInitlize();
#if defined(_WIN32) || defined(WIN32)
	LogAddFileHandler("PX2Application_Log.txt", 1, LT_INFO|LT_ERROR|LT_USER);
#endif
	LoadAddOutputWindowHandler(1, LT_INFO|LT_ERROR|LT_USER);

	PX2_LOG_INFO("Begin ApplicationBase::Initlize.\n");

	mResMan = new0 ResourceManager();

	mEventWorld = new0 EventWorld();
	mEventWorld->ComeIn(this);

#if defined (PX2_LUA)
	mScriptMan = ScriptManager::Create(ScriptManager::ST_LUA);
	LuaManager *luaMan = (LuaManager*)mScriptMan;
	tolua_PX2_open(luaMan->GetLuaState());
#endif

	mScriptEventHandler = new0 ScriptEventHandler();
	mEventWorld->ComeIn(mScriptEventHandler);

	mRoot = new0 GraphicsRoot();
	mRoot->Initlize();

	mGameMan = new0 GameManager();
	mGameMan->LoadBoost("Data/boost.xml");
	int width = mGameMan->GetBoostWidth();
	int height = mGameMan->GetBoostHeight();
	std::string projPath = mGameMan->GetProjectPath();
	if (0!=width && 0!=height)
	{
		mWidth = width;
		mHeight = height;
	}

	Sizef sz((float)mWidth, (float)mHeight);
	mRoot->SetSize(sz);

	mInputEventAdapter = new0 InputEventAdapter(); // input manager created in it
	mInputEventAdapter->Convert2Touch(true);
	mInputEventAdapter->SetSize((float)mWidth, (float)mHeight);

	mUIManager = new0 UIManager();
	mEventWorld->ComeIn(mUIManager);
	UIManager::GetSingleton().GetDefaultView()->SetSize((float)mWidth,
		(float)mHeight);

	mProject = new0 Project();
	mProject->SetInGamePlay(true);
	mProject->Load(projPath);
	Float4 color = mProject->GetColor();

	OnInitlizeApp();

	//mFrameText = new0 UIStaticText();
	//mFrameText->SetFont("Data/engine/arial.ttf", 16, 16);

	//mCurTotalMemory = new0 UIStaticText();
	//mCurTotalMemory->SetFont("Data/engine/arial.ttf", 16, 16);

	//mMaxTotalMemory = new0 UIStaticText();
	//mMaxTotalMemory->SetFont("Data/engine/arial.ttf", 16, 16);

	//mDebugText = new0 UIStaticText();
	//mDebugText->SetFont("Data/engine/arial.ttf", 16, 16);

	//Float3 texColor = Float3((1.0f-color[0])*2.0f, (1.0f-color[1])*0.5f,
	//	(1.0f-color[2])*0.5f);
	//mFrameText->SetColor(texColor);
	//mCurTotalMemory->SetColor(texColor);
	//mMaxTotalMemory->SetColor(texColor);
	//mDebugText->SetColor(texColor);

	mScriptMan->SetUserTypePointer("Project", "Project", mProject);
	mScriptMan->SetUserTypePointer("DebugText", "UIStaticText", mDebugText);
	//mScriptMan->SetUserTypePointer("PX2_LM", "LanguageManager", &(PX2_LM));
	//mScriptMan->SetUserTypePointer("PX2_RM", "ResourceManager", mResMan);
	//mScriptMan->SetUserTypePointer("PX2_SM", "ScriptManager", mScriptMan);
	mScriptMan->SetUserTypePointer("PX2_UIM", "UIManager", mUIManager);
	mScriptMan->CallFile("Data/boost.lua");

	OnInitlize();

	msIsInitlized = true;

	return true;
}
//----------------------------------------------------------------------------
void ApplicationBase::SetSize (int width, int height)
{
	mWidth = width;
	mHeight = height;

	if (mRenderer)
	{
		mRenderer->Resize(mWidth, mHeight);
	}

	if (mInputEventAdapter)
	{
		mInputEventAdapter->SetSize((float)mWidth, (float)mHeight);
	}
}
//----------------------------------------------------------------------------
int ApplicationBase::GetWidth ()
{
	return mWidth;
}
//----------------------------------------------------------------------------
int ApplicationBase::GetHeight ()
{
	return mHeight;
}
//----------------------------------------------------------------------------
void ApplicationBase::OnIdle ()
{
	mApplicationTime = (float)GetTimeInSeconds();

	if (!mIsTimeInited)
	{
		mLastApplicationTime = mApplicationTime;
		mElapsedTime = 0.0f;
		mIsTimeInited = true;
	}
	else
	{
		mElapsedTime = mApplicationTime - mLastApplicationTime;
		mLastApplicationTime = mApplicationTime;
	}

	mFrameTime += mElapsedTime;
	++mNumFrames;
	if (mFrameTime > 1.0f)
	{
		mFrameRate = (float)mNumFrames/mFrameTime;
		mFrameTime = 0.0f;
		mNumFrames = 0;
	}

	if (mEventWorld)
		mEventWorld->Update(mElapsedTime);

	if (mScriptMan)
	{
		char str[256];
		sprintf(str, "OnUpdate(%f,%f)", mApplicationTime, mElapsedTime);
		mScriptMan->CallString(str);
	}
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
void ApplicationBase::DoEnter ()
{
}
//----------------------------------------------------------------------------
void ApplicationBase::DoExecute (Event *event)
{
}
//----------------------------------------------------------------------------
void ApplicationBase::DoLeave ()
{
}
//----------------------------------------------------------------------------
bool ApplicationBase::Ternamate ()
{
	PX2_LOG_INFO("Begin ApplicationBase::Ternamate.\n");

	OnTernamate();

	mFrameText = 0;
	mCurTotalMemory = 0;
	mMaxTotalMemory = 0;
	mDebugText = 0;

	if (mResMan)
	{
		mResMan->Clear();
	}

	ScenePtr scene = mProject->GetScene();
	scene = 0;

	if (mProject)
	{
		mProject->SetScene(0);
		mProject->SetUI(0);
		delete0(mProject);
		Project::Set(0);
	}

	if (mUIManager)
	{
		delete0(mUIManager);
		UIManager::Set(0);
	}

	mScriptEventHandler = 0;

	if (mScriptMan)
	{
		delete0(mScriptMan);
		ScriptManager::Set(0);
	}

	if (mInputEventAdapter)
	{
		mInputEventAdapter->Ternamate();
		delete0(mInputEventAdapter);
		InputEventAdapter::Set(0);
	}

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
		mEventWorld->GoOut(this);

		delete0(mEventWorld);
		EventWorld::Set(0);
	}

	OnTernamateApp();

	PX2_LOG_INFO("End ApplicationBase::Ternamate.\n");

	LogShutdown();

#ifdef PX2_USE_MEMORY
	Memory::Terminate("PX2Application_MemoryReport.txt", false);
#endif

	return true;
}
//----------------------------------------------------------------------------
bool ApplicationBase::OnInitlize ()
{
	PX2_LOG_INFO("ApplicationBase::OnInitlize.\n");

	return true;
}
//----------------------------------------------------------------------------
bool ApplicationBase::OnTernamate ()
{
	PX2_LOG_INFO("ApplicationBase::OnTernamate.\n");

	return true;
}
//----------------------------------------------------------------------------
void ApplicationBase::WillEnterForeground ()
{
}
//----------------------------------------------------------------------------
void ApplicationBase::DidEnterBackground ()
{
}
//----------------------------------------------------------------------------
int ApplicationBase::Main (int numArguments, char** arguments)
{
	return 1;
}
//----------------------------------------------------------------------------
void ApplicationBase::DrawInfo (int x, int y)
{
	char fpsMsg[256];
	sprintf(fpsMsg, "FPS: %.1lf", mFrameRate);
	mFrameText->SetText(fpsMsg);
	mFrameText->WorldTransform.SetTranslate(APoint((float)x, 0.0f, (float)y));
	mFrameText->WorldBoundIsCurrent = true;
	mRenderer->Draw(mFrameText);

	double toM = 1024.0*1024.0;
#ifdef _DEBUG
	double cTB = (double)Memory::GetCurTotalBytes();
	double mTB = (double)Memory::GetMaxTotalBytes();
#else
	double cTB = 0.0;
	double mTB = 0.0;
#endif
	double cTM = cTB/toM;
	double mTM = mTB/toM;

	char curTotalMemory[256];
	sprintf(curTotalMemory, "CurMemory: %d bytes(%.1lf m).", (int)cTB, (float)cTM);
	mCurTotalMemory->SetText(curTotalMemory);
	mCurTotalMemory->WorldTransform.SetTranslate(APoint((float)x, 0.0f,
		(float)y - 20.0f));
	mCurTotalMemory->WorldBoundIsCurrent = true;
#ifdef _DEBUG
	mRenderer->Draw(mCurTotalMemory);
#endif

	char maxTotalMemory[256];
	sprintf(maxTotalMemory, "MaxMemory: %d bytes(%.1lf m)", (int)mTB, (float)mTM);
	mMaxTotalMemory->SetText(maxTotalMemory);
	mMaxTotalMemory->WorldTransform.SetTranslate(APoint((float)x, 0.0f,
		(float)y - 40.0f));
	mMaxTotalMemory->WorldBoundIsCurrent = true;
#ifdef _DEBUG
	mRenderer->Draw(mMaxTotalMemory);
#endif

	mDebugText->WorldTransform.SetTranslate(APoint((float)x, 0.0f,
		(float)y - 60.0f));
	mDebugText->WorldBoundIsCurrent = true;
	mRenderer->Draw(mDebugText);
}
//----------------------------------------------------------------------------
