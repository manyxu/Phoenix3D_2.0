/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ControllerManager.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2CONTROLLERMANAGER_HPP
#define PX2CONTROLLERMANAGER_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2Singleton.hpp"

namespace PX2Editor
{

	class ControllerInstance;

	class ControllerManager : public PX2::Singleton<ControllerManager>
	{
	public:
		ControllerManager ();
		virtual ~ControllerManager ();
		
		void RegisterControllerInstance (const std::string &name, 
			ControllerInstance *instance);
		void RegisterControllerInstance (const std::string &name);

		ControllerInstance *GetCurrentControllerInstance ();

		static const std::string DEFAULT_CONTROLLER_NAME;
		static const std::string MULTIITEM_CONTROLLER_NAME;

	protected:
		void SwitchControllers (const std::string& typeName);

		typedef std::map<std::string, ControllerInstance*>
			ControllerInstanceMap;
		ControllerInstanceMap mControllerInstanceMap;

		ControllerInstance *mCurrentControllerInstance;
		std::string mCurrentControllerType;
		ControllerInstance *mDefaultControllerInstance;
		ControllerInstance *mMultiControllerInstance;
	};

#include "PX2ControllerManager.inl"

}

#endif