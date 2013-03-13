/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIView.cpp
*
*/

#include "PX2UIView.hpp"
#include "PX2Picker.hpp"
#include "PX2InputEvent.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
UIView::UIView (int id)
	:
mID(id),
mRenderer(0)
{
	mSize.Width = 1024;
	mSize.Height = 768;

	mCamera = new0 Camera(false);
	mUIMainFrame = new0 UIFrame();
	mCuller.SetCamera(mCamera);

	OnSizeChange();
}
//----------------------------------------------------------------------------
UIView::~UIView ()
{
}
//----------------------------------------------------------------------------
void UIView::SetSize (float width, float height)
{
	mSize.Width = width;
	mSize.Height = height;

	OnSizeChange();
}
//----------------------------------------------------------------------------
void UIView::SetSize (const Sizef &size)
{
	mSize = size;

	OnSizeChange();
}
//----------------------------------------------------------------------------
void UIView::SetWidth (float width)
{
	mSize.Width = width;

	OnSizeChange();
}
//----------------------------------------------------------------------------
void UIView::SetHeight (float height)
{
	mSize.Height = height;

	OnSizeChange();
}
//----------------------------------------------------------------------------
void UIView::Update (double appSeconds, double elapsedSeconds)
{
	if (mUIMainFrame)
		mUIMainFrame->Update(appSeconds, false);
}
//----------------------------------------------------------------------------
void UIView::ComputeVisibleSet ()
{
	if (mUIMainFrame)
		mCuller.ComputeVisibleSet(mUIMainFrame);
	else
		mCuller.GetVisibleSet().Clear();
}
//----------------------------------------------------------------------------
void UIView::DoExecute (Event *event)
{
	if (InputEventSpace::IsEqual(event, InputEventSpace::TouchPressed))
	{
		InputEventData data = event->GetData<InputEventData>();
		int id = data.ViewID;
		
		if (id == mID)
		{
			float x = (float)data.TState.X.Absoulate;
			float y = (float)data.TState.Y.Absoulate;

			DoPick(mPickedPicBoxes, x, y, 1);
		}
	}
	else if (InputEventSpace::IsEqual(event, InputEventSpace::TouchReleased))
	{
		InputEventData data = event->GetData<InputEventData>();
		int id = data.ViewID;

		if (id == mID)
		{
			float x = (float)data.TState.X.Absoulate;
			float y = (float)data.TState.Y.Absoulate;

			DoPick(mPickedPicBoxes, x, y, 2);
		}
	}

	if (mUIMainFrame)
		mUIMainFrame->OnEvent(event);
}
//----------------------------------------------------------------------------
void UIView::OnSizeChange ()
{
	float helfWidth = mSize.Width/2.0f;
	float helfHeight = mSize.Height/2.0f;

	mCamera->SetFrustum(0.1f, 1000.0f, -helfHeight, helfHeight, -helfWidth,
		helfWidth);

	mCamera->SetFrame(APoint(helfWidth, -100.0f, helfHeight), AVector::UNIT_Y, 
		AVector::UNIT_Z, AVector::UNIT_X);
}
//----------------------------------------------------------------------------
void UIView::DoPick (std::vector<UIPicBoxPtr> &vec, float x, float y,
	int pickInfo)
{
	if (!mRenderer)
		return;

	Camera *camBefore = mRenderer->GetCamera();
	mRenderer->SetCamera(mCamera);

	vec.clear();

	Picker pick(true, pickInfo);
	APoint origin;
	AVector direction;
	mRenderer->GetPickRay((int)x, (int)y, origin, direction);
	pick.Execute(mUIMainFrame, origin, direction, 0.0f, Mathf::MAX_REAL);

	for (int i=0; i<(int)pick.Records.size(); i++)
	{
		Movable *mov = pick.Records[i].Intersected;
		UIPicBox *picBox = DynamicCast<UIPicBox>(mov);
		if (picBox)
		{
			vec.push_back(picBox);
		}
	}

	for (int i=0; i<(int)vec.size(); i++)
	{
		vec[i]->UIAfterPicked(pickInfo);
	}

	mRenderer->SetCamera(camBefore);
}
//----------------------------------------------------------------------------