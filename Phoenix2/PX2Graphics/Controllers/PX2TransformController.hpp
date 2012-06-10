/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2TransformController.hpp
*
* 版本		:	1.0 (2011/02/01)
*
* 作者		：	more
*
*/

#ifndef PX2TRANSFORMCONTROLLER_HPP
#define PX2TRANSFORMCONTROLLER_HPP

#include "PX2GraphicsPrerequisites.hpp"
#include "PX2Controller.hpp"
#include "PX2Transform.hpp"

namespace PX2
{

	class PX2_GRAPHICS_ENTRY TransformController : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(TransformController);

	public:
		TransformController (const Transform& localTransform);
		virtual ~TransformController ();

		// 成员访问
		inline void SetTransform (const Transform& localTransform);
		inline const Transform& GetTransform () const;

		// 动画更新
		/**
		* 以“毫秒”为单位。更新知识简单的将mLocalTransform拷贝到mObject的
		* LocalTransform中。
		*/
		virtual bool Update (double applicationTime);

	protected:
		Transform mLocalTransform;
	};

	PX2_REGISTER_STREAM(TransformController);
	typedef Pointer0<TransformController> TransformControllerPtr;
#include "PX2TransformController.inl"

}

#endif
