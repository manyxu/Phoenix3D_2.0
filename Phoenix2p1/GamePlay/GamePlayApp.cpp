/*
*
* Filename	:	GamePlayApp.cpp
*
*/

#include "GamePlayApp.hpp"

PX2_IMPLEMENT_APPLICATION(GamePlayApp)
//----------------------------------------------------------------------------
GamePlayApp::GamePlayApp ()
{
	mWindowTitle = std::string("GamePlayApp");
	mInited = false;
}
//----------------------------------------------------------------------------
GamePlayApp::~GamePlayApp ()
{
	// 所有内存释放,必须在析构函数之前释放
}
//----------------------------------------------------------------------------
bool GamePlayApp::OnInitlize ()
{
	Application::OnInitlize();

	CreateScene();

	return true;
}
//----------------------------------------------------------------------------
bool GamePlayApp::OnTernamate ()
{
	mScene = 0;
	mSceneGraph = 0;
	mCamera = 0;
	mWireProperty = 0;
	mCullProperty = 0;

	Application::OnTernamate();

	return true;
}
//----------------------------------------------------------------------------
bool GamePlayApp::OnResume()
{
	return true;
}
//----------------------------------------------------------------------------
bool GamePlayApp::OnPause()
{
	return true;
}
//----------------------------------------------------------------------------
void GamePlayApp::OnIdle ()
{
	if (!mInited)
		return;

	mRenderer->SetCamera(mCamera);

	MeasureTime();

	if (mSceneGraph)
	{
		mSceneGraph->Update();
		mCuller.ComputeVisibleSet(mSceneGraph);
	}

	if (mRenderer->PreDraw())
	{
		mRenderer->ClearBuffers();

		mRenderer->Draw(mCuller.GetVisibleSet().Sort());

		DrawFrameRate(8, mHeight-8, mTextColor);

		mRenderer->PostDraw();
		mRenderer->DisplayColorBuffer();
	}

	UpdateFrameCount();
}
//----------------------------------------------------------------------------
void GamePlayApp::CreateScene ()
{
	mRenderer->SetClearColor(Float4(0.5f, 0.5f, 0.0f, 1.0f));

	mWireProperty = new0 WireProperty();
	mWireProperty->Enabled = true;
	mCullProperty = new0 CullProperty();
	mCullProperty->Enabled = false;

	std::string mapName = GameManager::GetSingleton().GetMapName();
	std::string fullMapName = "Data/maps/"+mapName+".pxof";

	InStream inStream;
	if (inStream.Load(fullMapName.c_str()))
	{
		Object *object = inStream.GetObjectAt(0);
		Scene *scene = DynamicCast<Scene>(object);
		if (scene)
		{
			mScene = scene;
			mSceneGraph = scene->GetSceneNode();
			mCamera = scene->GetDefaultCameraActor()->GetCamera();
			mRenderer->SetCamera(mCamera);
			mCuller.SetCamera(mCamera);
		}
		else
		{
			mSceneGraph = new0 Node();
			mSceneGraph->Update();
			mCamera->SetFrustum(60.0f, ((float)mWidth)/(float)mHeight, 1.0f, 100.0f);
			AVector camDVector(0.0f, 0.0f, 1.0f);
			AVector camUVector(0.0f,1.0f,0.0f);
			AVector camRVector = camDVector.Cross(camUVector);
			APoint camPosition = APoint::ORIGIN -
				2.0f*mSceneGraph->WorldBound.GetRadius()*camDVector;
			mCamera->SetFrame(camPosition, camDVector, camUVector, camRVector);

			mCuller.SetCamera(mCamera);
			mRenderer->SetCamera(mCamera);
		}
	}

	std::string writeablePath = FileIO::GetWriteablePath();
	PX2_LOG_INFO("GamePlay writeablePath is %s\n", writeablePath.c_str());
	PX2_LOG_INFO("CreateScene successful!\n");

	mInited = true;
}
//----------------------------------------------------------------------------