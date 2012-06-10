/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ControllerManager.cpp
*
*/

#include "PX2ControllerManager.hpp"
#include "PX2DefaultControllerInstance.hpp"
#include "PX2MultiItemControllerInstance.hpp"
using namespace PX2Editor;
using namespace PX2;

const std::string ControllerManager::DEFAULT_CONTROLLER_NAME = "Default";
const std::string ControllerManager::MULTIITEM_CONTROLLER_NAME = "Multi";
//-----------------------------------------------------------------------------
ControllerManager::ControllerManager ()
:
mCurrentControllerInstance(0)
{
	mDefaultControllerInstance = new DefaultControllerInstance();
	mMultiControllerInstance = new MultiItemControllerInstance();

	RegisterControllerInstance(DEFAULT_CONTROLLER_NAME, 
		mDefaultControllerInstance);
	RegisterControllerInstance(MULTIITEM_CONTROLLER_NAME,
		mMultiControllerInstance);

	SwitchControllers(DEFAULT_CONTROLLER_NAME);
}
//-----------------------------------------------------------------------------
ControllerManager::~ControllerManager ()
{

}
//-----------------------------------------------------------------------------
void ControllerManager::RegisterControllerInstance(const std::string &name, 
												   ControllerInstance *instance)
{
	mControllerInstanceMap[name] = instance;
}
//-----------------------------------------------------------------------------
void ControllerManager::RegisterControllerInstance (const std::string &name)
{
	ControllerInstanceMap::iterator it = mControllerInstanceMap.find(name);
	if (it != mControllerInstanceMap.end())
	{
		mControllerInstanceMap.erase(it);
	}
}
//-----------------------------------------------------------------------------
void ControllerManager::SwitchControllers (const std::string& typeName)
{
	if (typeName != mCurrentControllerType)
	{
		ControllerInstance *oldControllerInstance = mCurrentControllerInstance;

		if (mCurrentControllerInstance)
			mCurrentControllerInstance->DeActivate();
		
		ControllerInstanceMap::iterator it = 
			mControllerInstanceMap.find(typeName);

		if (it == mControllerInstanceMap.end())
		{
			mCurrentControllerInstance = mDefaultControllerInstance;
			mCurrentControllerType = DEFAULT_CONTROLLER_NAME;
		}
		else
		{
			mCurrentControllerInstance = it->second;
			mCurrentControllerType = typeName;
		}

		mCurrentControllerInstance->Activate();

		if (oldControllerInstance && oldControllerInstance->GetInteractionMode()!=
			IM_SELECT)
		{
			mCurrentControllerInstance->SetInteractionMode(oldControllerInstance
				->GetInteractionMode());
		}
		else
		{
			mCurrentControllerInstance->SetInteractionMode(IM_SELECT);
		}

	}
}
//-----------------------------------------------------------------------------