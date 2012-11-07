/*
* Phoenix 3D 引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Noncopyable.hpp
*
* 版本		:	1.0 (2011/01/30)
*
* 作者		：	more
*
*/

#ifndef PX2NONCOPYABLE_HPP
#define PX2NONCOPYABLE_HPP

namespace PX2
{

	/// 从此类派生类的对象将不可被拷贝
	class Noncopyable
	{
	protected:
		Noncopyable () {}
		~Noncopyable () {}

	private:
		Noncopyable (const Noncopyable &);
		Noncopyable &operator = (const Noncopyable &);
	};

}

#endif