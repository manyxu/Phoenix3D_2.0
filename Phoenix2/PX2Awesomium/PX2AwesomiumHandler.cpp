/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Awesomium.cpp
*
*/

#include "PX2Awesomium.hpp"
#include "PX2OISEventAdapter.hpp"
using namespace Awesomium;
using namespace PX2;

AwesomiumHandler::AwesomiumHandler()
{
	mInitlized = false;
}
//----------------------------------------------------------------------------
AwesomiumHandler::~AwesomiumHandler()
{
	if (mDefaultView)
		mDefaultView->destroy();

	delete(mCore);

	mTexture = 0;
}
//----------------------------------------------------------------------------
bool AwesomiumHandler::Initlize (float width, float height)
{
	if (!mInitlized)
	{
		mCore = new WebCore();
		mDefaultView = mCore->createWebView((int)width, (int)height);
		mWebViewWidth = width;
		mWebViewHeight = height;

		#define URL	"http://www.douban.com/people/realmany/"

		mDefaultView->loadURL(URL);

		mDefaultView->focus();

		mDefaultRenderBuffer = mDefaultView->render();	

		mTexture = new0 Texture2D(Texture::TF_A8R8G8B8, (int)width,
			(int)height, 1);

		mInitlized = true;
	}

	return true;
}
//----------------------------------------------------------------------------
Awesomium::WebCore *AwesomiumHandler::GetWebCore ()
{
	return mCore;
}
//----------------------------------------------------------------------------
Awesomium::WebView *AwesomiumHandler::GetDefaultView ()
{
	return mDefaultView;
}
//----------------------------------------------------------------------------
void AwesomiumHandler::SetTexture (Texture2D *texture)
{
	mTexture = texture;
}
//----------------------------------------------------------------------------
void AwesomiumHandler::DoEnter ()
{
}
//----------------------------------------------------------------------------
void AwesomiumHandler::DoUpdate ()
{
	if (!mInitlized)
		return;

	mCore->update();

	if (!mDefaultView->isDirty())
		return;

	char *data = mTexture->GetData(0);
	int pixelSize = mTexture->GetPixelSize();
	int dimension = mTexture->GetDimension(0, 0);
	int pitch = dimension * pixelSize;
	
	mDefaultRenderBuffer->copyTo((unsigned char*)data, pitch, pixelSize, true);

	Renderer::UpdateAll(mTexture, 0);
}
//----------------------------------------------------------------------------
void AwesomiumHandler::DoExecute (Event *event)
{
	if (!OISEventSpace::IsIn(event))
		return;

	OISEventData data = event->GetData<OISEventData>();

	if (OISEventSpace::IsEqual(event, OISEventSpace::KeyPressed))
	{
		Awesomium::WebKeyboardEvent keyEvent;

		keyEvent.type = Awesomium::WebKeyboardEvent::TYPE_KEY_DOWN;

		mDefaultView->injectKeyboardEvent(keyEvent);
	}
	else if (OISEventSpace::IsEqual(event, OISEventSpace::MouseMoved))
	{
		OISEventData data = event->GetData<OISEventData>();
		mDefaultView->injectMouseMove(data.mouseState.X.abs, 
			data.mouseState.Y.abs);
	}
	else if (OISEventSpace::IsEqual(event, OISEventSpace::MousePressed))
	{
		if (data.mouseID == OIS::MB_Left)
			mDefaultView->injectMouseDown(Awesomium::LEFT_MOUSE_BTN);
		else if (data.mouseID == OIS::MB_Right)
			mDefaultView->injectMouseDown(Awesomium::RIGHT_MOUSE_BTN);
	}
	else if (OISEventSpace::IsEqual(event, OISEventSpace::MouseReleased))
	{
		if (data.mouseID == OIS::MB_Left)
			mDefaultView->injectMouseUp(Awesomium::LEFT_MOUSE_BTN);
		else if (data.mouseID == OIS::MB_Right)
			mDefaultView->injectMouseUp(Awesomium::RIGHT_MOUSE_BTN);
	}
}
//----------------------------------------------------------------------------
void AwesomiumHandler::DoLeave ()
{
}
//----------------------------------------------------------------------------