/*
*
* ÎÄ¼þÃû³Æ	£º	PX2CtrlInstMan.cpp
*
*/

#include "PX2ViewCtrlInstMan.hpp"
#include "PX2DefViewCtrlInst.hpp"
#include "PX2MultiViewCtrlInst.hpp"
using namespace PX2Editor;
using namespace PX2;

const std::string ViewCtrlInstMan::DEFAULT_CTRL_NAME = "Default";
const std::string ViewCtrlInstMan::MULTIITEM_CTRL_NAME = "Multi";
//-----------------------------------------------------------------------------
ViewCtrlInstMan::ViewCtrlInstMan ()
	:
mCurViewCtrlInst(0)
{
	mDefViewCtrlInst = new0 DefViewCtrlInst();
	mMultiViewCtrlInst = new0 MultiViewCtrlInst();

	RegisterViewCtrlInst(DEFAULT_CTRL_NAME, mDefViewCtrlInst);
	RegisterViewCtrlInst(MULTIITEM_CTRL_NAME, mMultiViewCtrlInst);

	SwitchCtrlInst(DEFAULT_CTRL_NAME);
}
//-----------------------------------------------------------------------------
ViewCtrlInstMan::~ViewCtrlInstMan ()
{
	if (mDefViewCtrlInst)
	{
		delete0(mDefViewCtrlInst);
	}
	if (mMultiViewCtrlInst)
	{
		delete0(mMultiViewCtrlInst);
	}
}
//-----------------------------------------------------------------------------
void ViewCtrlInstMan::RegisterViewCtrlInst(const std::string &name, 
	ViewCtrlInst *instance)
{
	mViewCtrlInsts[name] = instance;
}
//-----------------------------------------------------------------------------
void ViewCtrlInstMan::UnRegisterViewCtrlInst (const std::string &name)
{
	std::map<std::string, ViewCtrlInst*>::iterator it 
		= mViewCtrlInsts.find(name);

	if (it != mViewCtrlInsts.end())
	{
		mViewCtrlInsts.erase(it);
	}
}
//-----------------------------------------------------------------------------
void ViewCtrlInstMan::SwitchCtrlInst (const std::string& typeName)
{
	if (typeName != mCurViewCtrlType)
	{
		ViewCtrlInst *oldInst = mCurViewCtrlInst;

		if (mCurViewCtrlInst)
			mCurViewCtrlInst->DeActivate();

		std::map<std::string, ViewCtrlInst*>::iterator it = 
			mViewCtrlInsts.find(typeName);

		if (it == mViewCtrlInsts.end())
		{
			mCurViewCtrlInst = mDefViewCtrlInst;
			mCurViewCtrlType = DEFAULT_CTRL_NAME;
		}
		else
		{
			mCurViewCtrlInst = it->second;
			mCurViewCtrlType = typeName;
		}

		mCurViewCtrlInst->Activate();

		if (oldInst)
		{
			mCurViewCtrlInst->SetInteractionMode(oldInst->GetInteractionMode());
		}
	}
}
//-----------------------------------------------------------------------------