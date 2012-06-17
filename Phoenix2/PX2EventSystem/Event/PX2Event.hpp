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

#ifndef PX2EVENT_HPP
#define PX2EVENT_HPP

#include "PX2EventSystemPrerequisites.hpp"
#include "PX2EventChannel.hpp"
#include "PX2EventHandler.hpp"
#include "PX2EventData.hpp"

namespace PX2
{

	/// 系统事件
	enum SystemEvent
	{
		EVENT_NONE = -1,
	};

	/// 事件对象
	class Event
	{
	public:
		typedef int EventType;

	public:
		Event ();
		Event (const Event& event);
		~Event ();

		// 赋值
		Event& operator= (const Event& event);

		// 事件
		void SetEventType (EventType eventType);
		EventType GetEventType ();

		// 通道
		void SetChannel (const EventChannel& eventChannel);
		const EventChannel &GetChannel ();

		// 数据
		template <class DType>
		void SetData (DType data);

		template <class DType>
		DType GetData ();

		// 发送/接收者
		void SetSender (EventHandler *handler);
		EventHandler* GetSender ();
		void SetReceiver (EventHandler *handler);
		EventHandler* GetReceiver ();

public_internal:
		bool IsSystemEvent () const;
		void SetBeSystemEvent (); //< mEventChannel为0消息
		void Initlize (const Event &event);

		EventChannel mEventChannel;
		EventType mEventType;
		EventData mEventData;
		
		EventHandler* mSender;
		EventHandler* mReceiver;
	};

#include "PX2Event.inl"

}

#endif