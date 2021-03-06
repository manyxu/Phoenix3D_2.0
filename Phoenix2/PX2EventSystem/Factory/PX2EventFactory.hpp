/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EventChannel.hpp
*
* 版本		:	1.0 (2011/02/01)
*
* 作者		：	more
*
*/

#ifndef PX2EVENTFACTORY_HPP
#define PX2EVENTFACTORY_HPP

#include "PX2EventFactoryImplement.hpp"

namespace PX2
{
	
	/// 事件工厂
	/**
	*
	*/
	class EventFactory
	{
	public:
		// 单件
		static EventFactory &GetInstance ();
		static EventFactory* GetInstancePtr ();

		// 事件
		Event* CreateEvent ();
		void DestoryEvent (Event* event);

		// 事件空间
		void RegisterEventSpace (EventSpace* eventSpace);
		void UnRegisterEventSpace (const std::string &name);
		EventSpace* GetEventSpace (const std::string &name) const;
		EventSpace* FindEventSpace (Event* event) const;

	private:
		EventFactory ();
		~EventFactory ();

		EventFactoryImplement* mEventImplement;
	};

}

#endif