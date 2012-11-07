/*
* Phoenix 3D 引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Object.hpp
*
* 版本		:	1.0 (2011/01/30)
*
* 作者		：	more
*
*/

#ifndef PX2OBJECT_HPP
#define PX2OBJECT_HPP

#include "PX2CorePre.hpp"
#include "PX2Names.hpp"
#include "PX2Rtti.hpp"
#include "PX2SmartPointer.hpp"
#include "PX2InStream.hpp"
#include "PX2OutStream.hpp"

namespace PX2
{

	/// 对象系统根类
	/** 
	* 对系统提供：运行识别机制，控制器系统，拷贝系统，名称ID系统,以及硬盘持久化
	* 系统支持。
	*/
	class Object
	{
		// 运行识别信息
	public:
		virtual const Rtti& GetRttiType () const;
		bool IsExactly (const Rtti& type) const;
		bool IsDerived (const Rtti& type) const;
		bool IsExactlyTypeOf (const Object* object) const;
		bool IsDerivedTypeOf (const Object* object) const;
		static const Rtti TYPE;

		// 资源路径
	public:
		void SetResourcePath (const std::string& name);
		const std::string& GetResourcePath () const;

	private:
		std::string mResourcePath;

		// 名称
	public:
		void SetName (const std::string& name);
		const std::string& GetName () const;
		virtual Object* GetObjectByName (const std::string& name);
		virtual void GetAllObjectsByName (const std::string& name,
			std::vector<Object*>& objects);
	private:
		std::string mName;

		// 持久化
	public:
		typedef Object* (*FactoryFunction)(InStream& stream);
		typedef std::map<std::string, FactoryFunction> FactoryMap;
		static bool RegisterFactory ();
		static void InitializeFactory ();
		static void TerminateFactory ();
		static FactoryFunction Find (const std::string& name);
		static Object* Factory (InStream& source);
		virtual void Load (InStream& source);
		virtual void Link (InStream& source);
		virtual void PostLink ();
		virtual bool Register (OutStream& target) const;
		virtual void Save (OutStream& target) const;
		virtual int GetStreamingSize () const;
		Object* Copy (const std::string& uniqueNameAppend) const;
	protected:
		// Constructor used by the loading system.
		enum LoadConstructor { LC_LOADER };
		Object (LoadConstructor value);
		static FactoryMap* msFactories;
	private:
		static bool msStreamRegistered;

		// 抽象基类
	protected:
		Object ();
	public:
		virtual ~Object ();

		// TODO:  Allow copy constructors and assignment operators?
	};

	static bool gsStreamRegistered_Object = Object::RegisterFactory();
	typedef Pointer0<Object> ObjectPtr;
#include "PX2Object.inl"

}

#endif
