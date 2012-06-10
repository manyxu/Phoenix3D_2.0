/*
*
* 文件名称	：	PX2UIManager.cpp
*
*/

#include "PX2UIManager.hpp"
#include "PX2ScreenTarget.hpp"
using namespace PX2;
using namespace std;

UIManager::UIManager (EventWorld *eventWorld)
:
mNextID(0),
mWndWidth(800.0f),
mWndHeight(600.0f),
mEventWorld(eventWorld)
{
	mVFormat = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);

	mCamera = ScreenTarget::CreateCamera();

	mUIMaterial = new0 UIMaterial();
}
//----------------------------------------------------------------------------
UIManager::UIManager (EventWorld *eventWorld, float width, float height)
:
mNextID(0),
mWndWidth(width),
mWndHeight(height),
mEventWorld(eventWorld)
{
	mVFormat = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);

	mCamera = ScreenTarget::CreateCamera();

	mUIMaterial = new0 UIMaterial();
}
//----------------------------------------------------------------------------
UIManager::~UIManager ()
{
	RemoveAllGroups();

	mVFormat = 0;
	mCamera = 0;
	mUIMaterial = 0;
	mEventWorld = 0;
}
//----------------------------------------------------------------------------
EventWorld *UIManager::GetEventWorld ()
{
	return mEventWorld;
}
//----------------------------------------------------------------------------
int UIManager::GetNextID ()
{
	return mNextID++;
}
//----------------------------------------------------------------------------
VertexFormat *UIManager::GetUIVertexFromat ()
{
	return mVFormat;
}
//----------------------------------------------------------------------------
Camera *UIManager::GetUICamera ()
{
	return mCamera;
}
//----------------------------------------------------------------------------
UIMaterial *UIManager::GetUIMaterial ()
{
	return mUIMaterial;
}
//----------------------------------------------------------------------------
float UIManager::GetWndWidth ()
{
	return mWndWidth;
}
//----------------------------------------------------------------------------
float UIManager::GetWndHeight ()
{
	return mWndHeight;
}
//----------------------------------------------------------------------------
UIFrame *UIManager::CreateAddAddUIFrame (const std::string &name, bool isForwardUI)
{
	int ID = GetNextID();

	UIFrame *group = 0;
	group = new0 UIFrame(0, ID, name);

	if (!group)
		return 0;

	if (isForwardUI)
		mForwardUIFrames.push_back(group);
	else
		mForwardUIFrames.push_back(group);

	return group;
}
//----------------------------------------------------------------------------
void UIManager::AddUIFrame (UIFrame *group, bool isForwardUI)
{
	if (!group)
		return;

	if (isForwardUI)
		mForwardUIFrames.push_back(group);
	else
		mForwardUIFrames.push_back(group);
}
//----------------------------------------------------------------------------
bool UIManager::RemoveUIFrame (const int ID)
{
	vector<UIFramePtr>::iterator it = mForwardUIFrames.begin();
	for ( ; it!=mForwardUIFrames.end(); ++it)
	{
		if (ID == (*it)->GetID())
		{
			(*it) = 0;
			mForwardUIFrames.erase(it);
			return true;
		}
	}

	it = mBackgroundUIFrames.begin();
	for ( ; it!=mBackgroundUIFrames.end(); ++it)
	{
		if (ID == (*it)->GetID())
		{
			(*it) = 0;
			mBackgroundUIFrames.erase(it);
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
bool UIManager::RemoveUIFrame (const std::string &name)
{
	vector<UIFramePtr>::iterator it = mForwardUIFrames.begin();
	for ( ; it!=mForwardUIFrames.end(); ++it)
	{
		if (name == (*it)->GetName())
		{
			(*it) = 0;
			mForwardUIFrames.erase(it);
			return true;
		}
	}

	it = mBackgroundUIFrames.begin();
	for ( ; it!=mBackgroundUIFrames.end(); ++it)
	{
		if (name == (*it)->GetName())
		{
			(*it) = 0;
			mBackgroundUIFrames.erase(it);
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
void UIManager::RemoveAllGroups ()
{
	vector<UIFramePtr>::iterator it = mForwardUIFrames.begin();
	for ( ; it!=mForwardUIFrames.end(); ++it)
	{
		(*it) = 0;
	}

	it = mBackgroundUIFrames.begin();
	for ( ; it!=mBackgroundUIFrames.end(); ++it)
	{
		(*it) = 0;
	}

	mForwardUIFrames.clear();
	mBackgroundUIFrames.clear();
}
//----------------------------------------------------------------------------
UIFrame* UIManager::GetUIFrame (const int ID)
{
	vector<UIFramePtr>::iterator it = mForwardUIFrames.begin();
	for ( ; it!=mForwardUIFrames.end(); ++it)
	{
		if (ID == (*it)->GetID())
		{
			return *it;
		}
	}

	it = mBackgroundUIFrames.begin();
	for ( ; it!=mBackgroundUIFrames.end(); ++it)
	{
		if (ID == (*it)->GetID())
		{
			return *it;
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
void UIManager::DoExecute (Event *event)
{
	vector<UIFramePtr>::iterator it = mForwardUIFrames.begin();
	for ( ; it!=mForwardUIFrames.end(); ++it)
	{
		(*it)->OnEvent(event);
	}

	it = mBackgroundUIFrames.begin();
	for ( ; it!=mBackgroundUIFrames.end(); ++it)
	{
		(*it)->OnEvent(event);
	}
}
//----------------------------------------------------------------------------
UIFrame* UIManager::GetUIFrame (const std::string &name)
{
	vector<UIFramePtr>::iterator it = mForwardUIFrames.begin();
	for ( ; it!=mForwardUIFrames.end(); ++it)
	{
		if (name == (*it)->GetName())
		{
			return *it;
		}
	}

	it = mBackgroundUIFrames.begin();
	for ( ; it!=mBackgroundUIFrames.end(); ++it)
	{
		if (name == (*it)->GetName())
		{
			return *it;
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
VisibleSet &UIManager::GetVisibleSet()
{
	vector<UIFramePtr>::iterator it = mForwardUIFrames.begin();
	for ( ; it!=mForwardUIFrames.end(); ++it)
	{
		(*it)->GetVisibleSet(mSet);
	}

	it = mBackgroundUIFrames.begin();
	for ( ; it!=mBackgroundUIFrames.end(); ++it)
	{
		(*it)->GetVisibleSet(mSet);
	}

	return mSet;
}
//----------------------------------------------------------------------------
void UIManager::DrawSorted (Renderer *renderer)
{
	mSet.Clear();

	GetVisibleSet();

	Camera *pCamera = renderer->GetCamera();

	renderer->SetCamera(mCamera);
	renderer->Draw(mSet);

	// 置回
	renderer->SetCamera(pCamera);
}
//----------------------------------------------------------------------------
void UIManager::Draw (Renderer *renderer)
{
	vector<UIFramePtr>::iterator it = mForwardUIFrames.begin();
	for ( ; it!=mForwardUIFrames.end(); ++it)
	{
		(*it)->Draw(renderer);
	}

	it = mBackgroundUIFrames.begin();
	for ( ; it!=mBackgroundUIFrames.end(); ++it)
	{
		(*it)->Draw(renderer);
	}
}
//----------------------------------------------------------------------------