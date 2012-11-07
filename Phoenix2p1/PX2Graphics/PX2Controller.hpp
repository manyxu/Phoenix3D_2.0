/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Controller.hpp
*
* 版本		:	1.0 (2011/02/01)
*
* 作者		：	more
*
*/

#ifndef PX2CONTROLLER_HPP
#define PX2CONTROLLER_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Object.hpp"

namespace PX2
{

	class Controlledable;

	class Controller : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Controller);

	protected:
		Controller ();
	public:
		virtual ~Controller ();

		// 成员访问
		inline Controlledable* GetObject () const;
		inline void SetApplicationTime (double applicationTime);
		inline double GetApplicationTime () const;

		// 动画更新，applicationTime是以毫秒作计算单位的
		virtual bool Update (double applicationTime);

		/// 动画更新类型
		enum RepeatType
		{
			RT_CLAMP,
			RT_WRAP,
			RT_CYCLE
		};
		
		// 成员访问
		RepeatType Repeat;  //< default = RT_CLAMP
		double MinTime;     //< default = 0
		double MaxTime;     //< default = 0
		double Phase;       //< default = 0
		double Frequency;   //< default = 1
		bool Active;        //< default = true

public_internal:
		/// 设置被控制的对象
		virtual void SetObject (Controlledable* object);

	protected:
		/// 将应用程序的时间转换到控制器的当前时间。派生类在更新自己的时候会
		/// 用到此函数。
		double GetControlTime (double applicationTime);

		/// 使用一个常规指针指向被控制的对象。这样避免controller和mObject之间
		/// smart指针的循环依赖
		Controlledable* mObject;

		/// 以毫秒作单位的应用程序事件
		double mApplicationTime;
	};

	PX2_REGISTER_STREAM(Controller);
	typedef Pointer0<Controller> ControllerPtr;
#include "PX2Controller.inl"

}

#endif