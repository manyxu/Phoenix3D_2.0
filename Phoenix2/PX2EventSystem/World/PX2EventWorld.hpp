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

#ifndef PX2EVENTWORLD_HPP
#define PX2EVENTWORLD_HPP

#include "PX2EventSystemPrerequisites.hpp"
#include "PX2EventHandler.hpp"
#include "PX2Singleton.hpp"

namespace PX2
{

	/// 消息世界
	class EventWorld : public Singleton<EventWorld>
	{
	public:
		EventWorld ();
		~EventWorld ();

		// 初始化/释放
		bool Initlize ();
		bool Ternamate (); //< 消息世界释放，把剩余消息广播完毕

		// 消息句柄
		void ComeIn (EventHandler *handler);
		void GoOut (EventHandler *handler);

		/// 更新
		/**
		* 1.为每个事件句柄添加一个新的更新消息
		* 2.分发各个事件，对事件进行相应处理
		*/
		void Update ();

		/// 广播本地消息
		/**
		* 该消息只能广播非系统消息，如果是一个系统消息，会出现一个断言失败。
		*/
		void BroadcastingLocalEvent (Event* event);

		/// 广播网络消息
		/**
		*
		*/
		void BroadcastingNetEvent (Event* event);

	private:
		bool AddHandler (EventHandler* handler);
		void RemoveHandler (EventHandler* handler);
		void UpdateEvent ();
		void _BroadcastingEvent (Event* event);
		void SwapEventList ();

		typedef std::vector<Event*> EventList;
		typedef std::vector<EventHandler*> EventHandlerList;

		EventList* mNowEventList;
		EventList* mNextEventList;
		EventHandlerList mHandlers;
	};

	typedef Pointer0<EventWorld> EventWorldPtr;

}

#endif