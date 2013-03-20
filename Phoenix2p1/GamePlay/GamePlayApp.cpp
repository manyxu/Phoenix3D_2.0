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

	//std::string writeablePath = ResourceManager::GetSingleton().GetWriteablePath();
	//PX2_LOG_INFO("GamePlay writeablePath is %s\n", writeablePath.c_str());

	CreateProject();

	return true;
}
//----------------------------------------------------------------------------
bool GamePlayApp::OnTernamate ()
{
	mCamera = 0;
	mWireProperty = 0;
	mCullProperty = 0;
	mDepthProperty = 0;

	Project::GetSingleton().SetScene(0);
	Project::GetSingleton().SetUI(0);
	PX2_RM.Clear();

	Application::OnTernamate();
	mInited = false;

	return true;
}
//----------------------------------------------------------------------------
void GamePlayApp::WillEnterForeground ()
{
	PX2_LOG_INFO("WillEnterForeground");

	OnInitlize();
}
//----------------------------------------------------------------------------
void GamePlayApp::DidEnterBackground ()
{
	PX2_LOG_INFO("DidEnterBackground");

	OnTernamate();
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
void GamePlayApp::DoEnter ()
{

}
//----------------------------------------------------------------------------
void GamePlayApp::DoExecute (Event *event)
{
	if (InputEventSpace::IsEqual(event, InputEventSpace::TouchPressed))
	{
		InputEventData data = event->GetData<InputEventData>();

		float absX = (float)data.TState.X.Absoulate;
		float absY = (float)data.TState.Y.Absoulate;
		mTouchPos[0] = absX;
		mTouchPos[1] = absY;
	}
	else if (InputEventSpace::IsEqual(event, InputEventSpace::TouchReleased))
	{
		InputEventData data = event->GetData<InputEventData>();

		float absX = (float)data.TState.X.Absoulate;
		float absY = (float)data.TState.Y.Absoulate;
		mTouchPos[0] = absX;
		mTouchPos[1] = absY;
	}
	else if (InputEventSpace::IsEqual(event, InputEventSpace::TouchMoved))
	{
		InputEventData data = event->GetData<InputEventData>();

		float absX = (float)data.TState.X.Absoulate;
		float absY = (float)data.TState.Y.Absoulate;
		//float relX = (float)data.TState.X.Relative;
		//float relY = (float)data.TState.Y.Relative;
		//float relZ = (float)data.TState.Z.Relative;

		float relX = absX - mTouchPos[0];
		float relY = absY - mTouchPos[1];

		RolateCamera(relX/mWidth*360.0f, relY/mWidth*180.0f);

	//	ZoomCamera(relZ/10.0f);

		mTouchPos[0] = absX;
		mTouchPos[1] = absY;
	}
}
//----------------------------------------------------------------------------
void GamePlayApp::DoLeave ()
{

}
//----------------------------------------------------------------------------
void GamePlayApp::OnIdle ()
{
	Application::OnIdle();

	Project *proj = Project::GetSingletonPtr();
	if (!proj)
		return;

	float moveHor = 0.0f;
	float moveVer = 0.0f;
	float moveVal = 0.05f;
	Keyboard *keyboard = InputEventAdapter::GetSingleton().GetKeyboard();
	if (keyboard)
	{
		if (keyboard->IsKeyDown(KC_W))
		{
			moveVer = moveVal;
		}
		if (keyboard->IsKeyDown(KC_S))
		{
			moveVer = -moveVal;
		}
		if (keyboard->IsKeyDown(KC_A))
		{
			moveHor = -moveVal;
		}
		if (keyboard->IsKeyDown(KC_D))
		{
			moveHor = moveVal;
		}
	}
	MoveCamera(moveHor, moveVer);

	if (!mInited)
		return;

	Scene *scene = Project::GetSingleton().GetScene();
	if (scene)
	{
		scene->Update(mApplicationTime, mElapsedTime);		
		mCuller.ComputeVisibleSet(scene->GetSceneNode());
	}

	UIView *uiView = UIManager::GetSingleton().GetDefaultView();
	if (uiView)
	{
		uiView->Update(mApplicationTime, mElapsedTime);
		uiView->ComputeVisibleSet();
	}

	if (mRenderer->PreDraw())
	{
		ResetRenderStates();
		mRenderer->ClearBuffers();
		mRenderer->Draw(mCuller.GetVisibleSet().Sort());

		// ui
		if (uiView)
		{
			Camera *uiCamera = uiView->GetCamera();
			Culler &uiCuller = uiView->GetCuller();
			mRenderer->SetCamera(uiCamera);
			mRenderer->Draw(uiCuller.GetVisibleSet());
			if (proj->IsShowProjectInfo())
			{
			//	DrawInfo(10, mHeight-20);
			}
			mRenderer->SetCamera(mCamera);
		}

		mRenderer->PostDraw();
		mRenderer->DisplayColorBuffer();
	}
}
//----------------------------------------------------------------------------
void GamePlayApp::CreateProject ()
{
	PX2_LOG_INFO("Begin CreateProject.\n");

	mWireProperty = new0 WireProperty();
	mWireProperty->Enabled = true;
	mCullProperty = new0 CullProperty();
	mCullProperty->Enabled = false;
	mDepthProperty = new DepthProperty();

	// clear color
	mClearColor =  Project::GetSingleton().GetColor();
	mRenderer->SetClearColor(mClearColor);

	// load scene
	PX2_LOG_INFO("Begin load scene.\n");
	std::string scenePath = Project::GetSingleton().GetSceneFilename();
	PX2_LOG_INFO("scenePath is %s\n", scenePath.c_str());
	if ("" != scenePath)
	{
		ObjectPtr sceneObj = 0;
		sceneObj = ResourceManager::GetSingleton().BlockLoad(scenePath);

		Scene *scene = DynamicCast<Scene>(sceneObj);
		if (scene)
		{
			mCamera = scene->GetDefaultCameraActor()->GetCamera();
			mRenderer->SetCamera(mCamera);
			mCuller.SetCamera(mCamera);
			GraphicsRoot::GetSingleton().SetCamera(mCamera);
			scene->ShowHelpMovables(false);
			Project::GetSingleton().SetScene(scene);

			PX2_LOG_INFO("Load scene successful.\n");
		}
		else
		{
			PX2_LOG_INFO("Load scene failed.\n");
		}
	}
	PX2_LOG_INFO("End load scene.\n");

	// ui
	PX2_LOG_INFO("Begin load UI.\n");
	std::string uiPath = Project::GetSingleton().GetUIFilename();
	PX2_LOG_INFO("uiPath is %s\n", uiPath.c_str());
	if ("" != uiPath)
	{
		ObjectPtr uiObj = 0;
		uiObj = ResourceManager::GetSingleton().BlockLoad(uiPath);

		UIFrame *ui = DynamicCast<UIFrame>(uiObj);
		if (ui)
		{
			Project::GetSingleton().SetUI(ui);

			PX2_LOG_INFO("Load ui successful.\n");
		}
		else
		{
			PX2_LOG_INFO("Load ui failed.\n");
		}
	}
	PX2_LOG_INFO("End load UI.\n");
	
	mInited = true;

	PX2_LOG_INFO("End CreateProject.\n");
}
//----------------------------------------------------------------------------
void GamePlayApp::ZoomCamera (float zoom)
{
	if (!mCamera)
		return;

	Vector3f position = mCamera->GetPosition();
	AVector dir = mCamera->GetDVector();
	dir.Normalize();

	position += dir*zoom;
	mCamera->SetPosition(position);
}
//----------------------------------------------------------------------------
void GamePlayApp::MoveCamera (const float &horz, const float &vert)
{
	if (!mCamera)
		return;

	Vector3f position = mCamera->GetPosition();
	AVector dVector = mCamera->GetDVector();
	AVector uVector = mCamera->GetUVector();
	AVector rVector = mCamera->GetRVector();

	dVector.Z() = 0.0f;
	dVector.Normalize();
	rVector.Z() = 0.0f;
	rVector.Normalize();
	position += dVector * vert;
	position += rVector * horz;

	mCamera->SetPosition(position);
}
//----------------------------------------------------------------------------
void GamePlayApp::RolateCamera (const float &horz, const float &vert)
{
	if (!mCamera)
		return;

	AVector dVector = mCamera->GetDVector();
	AVector uVector = mCamera->GetUVector();
	AVector rVector = mCamera->GetRVector();

	// horz
	HMatrix incrH(AVector::UNIT_Z, -horz*Mathf::DEG_TO_RAD);
	dVector = incrH * dVector;
	uVector = incrH * uVector;
	rVector = incrH * rVector;

	// vert
	Matrix3f kIncrV(rVector, vert*Mathf::DEG_TO_RAD);
	dVector = kIncrV * dVector;
	uVector = kIncrV * uVector;

	AVector::Orthonormalize(dVector, uVector, rVector);
	mCamera->SetAxes(dVector, uVector, rVector);

	SimplifyTerrain();
}
//----------------------------------------------------------------------------
void GamePlayApp::SimplifyTerrain ()
{
	Scene *scene = Project::GetSingleton().GetScene();
	if (scene)
	{
		TerrainActor *terActor = Project::GetSingleton().GetScene()
			->GetTerrainActor();
		if (terActor)
		{
			bool useLod = terActor->IsUseLod();
			LODTerrain *lodTer = terActor->GetLODTerrain();
			if (useLod && lodTer)
			{
				lodTer->Simplify();
			}
		}
	}
}
//----------------------------------------------------------------------------