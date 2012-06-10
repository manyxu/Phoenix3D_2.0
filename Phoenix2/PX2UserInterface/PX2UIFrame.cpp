/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIFrame.cpp
*
*/

#include "PX2UIFrame.hpp"
#include "PX2UIElement.hpp"
#include "PX2UIPictureBox.hpp"
#include "PX2UIManager.hpp"
#include "PX2UIButton.hpp"
using namespace PX2;
using namespace std;

PX2_IMPLEMENT_RTTI(PX2, UIElement, UIFrame);
PX2_IMPLEMENT_DEFAULT_NAMES(UIElement, UIFrame);

//----------------------------------------------------------------------------
UIFrame::UIFrame (UIFrame *parentContainer, int ID,  string name,
						  float deltaX, float deltaY,
						  float width, float height,
						  bool visible)
						  :
UIElement(parentContainer, ID, name, deltaX, deltaY, width, height, true, visible)
{
	mUIType = UIElement::UT_GROUP;
}
//----------------------------------------------------------------------------
UIFrame::~UIFrame()
{
	RemoveAllElements();
}
//----------------------------------------------------------------------------
void UIFrame::SetPosition (float offsetParentX, float offsetParentY)
{
	UIElement::SetPosition(offsetParentX, offsetParentY);

	for (int i=0; i<(int)mElements.size(); ++i)
	{
		mElements[i]->Move(0.0f, 0.0f);
	}
}
//----------------------------------------------------------------------------
void UIFrame::Move (float deltaX, float deltaY)
{
	UIElement::Move(deltaX, deltaY);

	for (int i=0; i<(int)mElements.size(); ++i)
	{
		mElements[i]->Move(0.0f, 0.0f);
	}
}
//----------------------------------------------------------------------------
UIElement* UIFrame::GetElement (const std::string name) const
{
	for (int i=0; i<(int)mElements.size(); ++i)
	{
		if (mElements[i]->GetName() == name)
			return mElements[i];
	}

	return 0;
}
//----------------------------------------------------------------------------
UIElement* UIFrame::GetElement (int ID) const
{
	for (int i=0; i<(int)mElements.size(); ++i)
	{
		if (mElements[i]->GetID() == ID)
			return mElements[i];
	}

	return 0;
}
//----------------------------------------------------------------------------
UIElement *UIFrame::CreateAndAddElement (UIElement::UIType type)
{
	UIElement *element = 0;
	int ID = UIManager::GetSingleton().GetNextID();
	string name = Help::IntToString(ID);

	switch (type)
	{
	case UT_GROUP:
		element = new0 UIFrame(this, ID, name);
		break;

	case UT_PICTUREBOX:
		element = new0 UIPictureBox(this, ID, name);
		break;

	case UT_BUTTON:
		element = new0 UIButton(this, ID, name);
		break;

	default:
		break;
	}

	if (element)
		mElements.push_back(element);

	return element;
}
//----------------------------------------------------------------------------
void UIFrame::AddElement (UIElement *element)
{
	if (element)
		mElements.push_back(element);
}
//----------------------------------------------------------------------------
bool UIFrame::RemoveElement (int ID)
{
	vector<UIElementPtr>::iterator it = mElements.begin();
	for ( ; it!=mElements.end(); ++it)
	{
		if ((*it)->GetID() == ID)
		{
			(*it) = 0;
			mElements.erase(it);
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
bool UIFrame::RemoveElement (const std::string &name)
{
	vector<UIElementPtr>::iterator it = mElements.begin();
	for ( ; it!=mElements.end(); ++it)
	{
		if ((*it)->GetName() == name)
		{
			(*it) = 0;
			mElements.erase(it);
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
void UIFrame::RemoveAllElements ()
{
	for (int i=0; i<(int)mElements.size(); i++)
	{
		mElements[i] = 0;
	}

	mElements.clear();
}
//----------------------------------------------------------------------------
void UIFrame::OnEvent (Event *event)
{
	for (int i=0; i<(int)mElements.size(); i++)
	{
		mElements[i]->OnEvent(event);
	}
}
//----------------------------------------------------------------------------
void UIFrame::GetVisibleSet (VisibleSet &set)
{
	for (int i=0; i<(int)mElements.size(); i++)
	{
		mElements[i]->GetVisibleSet(set);
	}
}
//----------------------------------------------------------------------------
void UIFrame::Draw (Renderer *renderer)
{
	for (int i=0; i<(int)mElements.size(); i++)
	{
		mElements[i]->Draw(renderer);
	}
}
//----------------------------------------------------------------------------