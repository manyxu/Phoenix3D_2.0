/*
*
* 文件名称	：	PX2App.cpp
*
*/

#include "PX2App.hpp"

PX2App::PX2App ()
:
mTextColor(1.0f, 1.0f, 1.0f, 1.0f)
{
	mWindowTitle = std::string("PX2App");
}
//----------------------------------------------------------------------------
PX2App::~PX2App ()
{
}
//----------------------------------------------------------------------------
bool PX2App::OnInitlize ()
{
	Win32Application::OnInitlize();

	// EventSystem
	EventWorld::GetSingleton().ComeIn(this);

	CreateScene();

	mScene->Update();
	mTrnNode->LocalTransform.SetTranslate(-mScene->WorldBound.GetCenter());
	mCamera->SetFrustum(60.0f, ((float)mWidth)/(float)mHeight, 1.0f, 100.0f);
	AVector camDVector(0.0f, 0.0f, 1.0f);
	AVector camUVector(0.0f,1.0f,0.0f);
	AVector camRVector = camDVector.Cross(camUVector);
	APoint camPosition = APoint::ORIGIN -
		2.0f*mScene->WorldBound.GetRadius()*camDVector;
	mCamera->SetFrame(camPosition, camDVector, camUVector, camRVector);

	// 初始更新场景
	mScene->Update();

	// 初始裁剪场景
	mCuller.SetCamera(mCamera);
	mCuller.ComputeVisibleSet(mScene);

	UIManager::GetSingleton().CreateAddAddUIFrame("Group1");
	UIPictureBox *pictureBox = DynamicCast<UIPictureBox>(
		UIManager::GetSingleton().GetUIFrame("Group1")->CreateAndAddElement(
		UIElement::UT_PICTUREBOX));
	pictureBox->SetTexture("Data/Images/awesomium_trans_logo.bmp");
	pictureBox->SetPosition(10.0f, 200.0f);
	pictureBox->SetSize(200.0f, 200.0f);

	UIButton *button = DynamicCast<UIButton>(
		UIManager::GetSingleton().GetUIFrame("Group1")->CreateAndAddElement(
		UIElement::UT_BUTTON));
	button->SetPictureBox(UIButton::BS_NORMAL, "Data/Images/Normal.bmp");
	button->SetPictureBox(UIButton::BS_MOUSEOVER, "Data/Images/MouseOver.bmp");
	button->SetPictureBox(UIButton::BS_MOUSEDOWN, "Data/Images/MouseDown.bmp");
	button->SetPictureBox(UIButton::BS_DISABLED, "Data/Images/Disabled.bmp");
	button->SetPosition(10.0f, 20.0f);
	button->SetSize(100.0f, 100.0f);

	// Awesomium
	//mAwesomiumHandler = new0 AwesomiumHandler();
	//EventWorld::GetSingleton().ComeIn(mAwesomiumHandler);
	//mAwesomiumHandler->Initlize(512.0f, 512.0f);

	//UIPictureBox *pictureBoxAwesomium = DynamicCast<UIPictureBox>(
	//	UIManager::GetSingleton().GetUIFrame("Group1")->CreateAndAddElement(
	//	UIElement::UT_PICTUREBOX));
	//pictureBoxAwesomium->SetTexture(mAwesomiumHandler->GetTexture());
	//pictureBoxAwesomium->SetPosition(0.0f, 600.0f-512.0f);
	//pictureBoxAwesomium->SetSize(512.0f, 512.0f);

	return true;
}
//----------------------------------------------------------------------------
bool PX2App::OnTernamate ()
{
	mScene = 0;
	mTrnNode = 0;
	mWireProperty = 0;

	EventWorld::GetSingleton().GoOut(this);

	if (mAwesomiumHandler)
	{
		EventWorld::GetSingleton().GoOut(mAwesomiumHandler);
		mAwesomiumHandler = 0;
	}

	Win32Application::OnTernamate();

	return true;
}
//----------------------------------------------------------------------------
void PX2App::OnIdle ()
{
	Draw();
}
//----------------------------------------------------------------------------
void PX2App::Draw ()
{
	MeasureTime();

	mCuller.ComputeVisibleSet(mScene);

	mScene->Update();
	mCuller.ComputeVisibleSet(mScene);


	//mCore->update();

	if (mRenderer->PreDraw())
	{
		mRenderer->ClearBuffers();

		mRenderer->Draw(mCuller.GetVisibleSet().Sort());

		UIManager::GetSingleton().DrawSorted(mRenderer);

		//if (mDefaultView->isDirty())
		//{
		//	const Awesomium::RenderBuffer *renderBuffer = 
		//		mDefaultView->render();

		//	if (renderBuffer)
		//		mRenderer->Draw(renderBuffer->buffer);
		//}

		DrawFrameRate(8, mHeight-8, mTextColor);

		mRenderer->PostDraw();
		mRenderer->DisplayColorBuffer();
	}

	UpdateFrameCount();
}
//----------------------------------------------------------------------------
void PX2App::CreateScene ()
{
	mScene = new0 Node();
	mTrnNode = new0 Node();
	mScene->AttachChild(mTrnNode);
	mWireProperty = new0 WireProperty();
	mRenderer->SetOverrideWireProperty(mWireProperty);
}
//----------------------------------------------------------------------------
void PX2App::DoEnter ()
{

}
//----------------------------------------------------------------------------
void PX2App::DoUpdate ()
{

}
//----------------------------------------------------------------------------
void PX2App::DoExecute (Event *event)
{

}
//----------------------------------------------------------------------------
void PX2App::DoLeave ()
{

}
//----------------------------------------------------------------------------