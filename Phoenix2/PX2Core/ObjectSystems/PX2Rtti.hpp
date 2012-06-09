/*
* Phoenix 3D 引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Rtti.hpp
*
* 版本		:	1.0 (2011/01/30)
*
* 作者		：	more
*
*/

#ifndef PX2RTTI_H
#define PX2RTTI_H

#include "PX2CorePrerequisites.hpp"

namespace PX2
{

	/// 运行识别机制类
	/**
	* 在系统所有的Object中，acName名称必须不同。在PX2的名字空间中，一个名叫Poo的
	* 类的名称为PX2.Poo。如果应用程序有其他的名字空间，如SomeName，那么这个名称
	* 为"SomeName.Poo"。
	*/
	class PX2_CORE_ENTRY Rtti
	{
	public:
		Rtti (const char* name, const Rtti* baseType);
		~Rtti ();

		inline const char* GetName () const;
		inline bool IsExactly (const Rtti& type) const;
		bool IsDerived (const Rtti& type) const;

	private:
		const char* mName;
		const Rtti* mBaseType;
	};

#include "PX2Rtti.inl"

}

//----------------------------------------------------------------------------
#define PX2_DECLARE_RTTI \
public: \
	static const Rtti TYPE; \
	\
	virtual const Rtti& GetRttiType () const \
{ \
	return TYPE; \
}
//----------------------------------------------------------------------------
#define PX2_IMPLEMENT_RTTI(nsname, baseclassname, classname) \
	const Rtti classname::TYPE(#nsname"."#classname, &baseclassname::TYPE)
//----------------------------------------------------------------------------

#endif
