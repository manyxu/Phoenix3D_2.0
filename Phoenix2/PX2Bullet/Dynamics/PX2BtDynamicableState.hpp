/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2BtDynamicable.hpp
*
* 版本		:	1.0 (2011/03/07)
*
* 作者		：	more
*
*/

#ifndef PX2BTDYNAMICABLESTATE_HPP
#define PX2BTDYNAMICABLESTATE_HPP

#include "PX2BtPreRequisites.hpp"

namespace TdBt
{

	class RigidBody;

	class DynamicableState : public btMotionState
	{
	public:
		DynamicableState (RigidBody *body);
		virtual ~DynamicableState ();

		virtual void getWorldTransform (btTransform& worldTrans ) const;
		virtual void setWorldTransform (const btTransform& worldTrans);

	protected:
		RigidBody *mBody;
	};

	typedef PX2::Pointer0<DynamicableState> DynamicableStatePtr;

}

#endif