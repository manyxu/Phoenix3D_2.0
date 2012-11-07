/*
* Phoenix 3D 引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ScopedCS.hpp
*
* 版本		:	1.0 (2011/01/30)
*
* 作者		：	more
*
*/

#ifndef PX2SCOPEDCS_HPP
#define PX2SCOPEDCS_HPP

#include "PX2CorePre.hpp"
#include "PX2Mutex.hpp"

namespace PX2
{

	/// 区域范围类：Scoped critial section
	/**
	* 当进入一个范围，这个类的局部临时对象创建一个mutex，当退出区域时，自动释放
	* 这个mutex。
	*/
	class ScopedCS
	{
	public:
		ScopedCS (Mutex* mutex);
		~ScopedCS ();

	private:
		Mutex* mMutex;
	};

}

#endif
