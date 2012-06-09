/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2BtDynamicConstraint.hpp
*
* 版本		:	1.0 (2011/03/21)
*
* 作者		：	more
*
*/

#ifndef PX2BTDYNAMICCONSTRAINT_HPP
#define PX2BTDYNAMICCONSTRAINT_HPP

#include "PX2BtPreRequisites.hpp"
#include "PX2BtCollisionable.hpp"

namespace TdBt
{

	class DynamicWorld;
	class RigidBody;

	class TypedConstraint
	{
	public:
		TypedConstraint (DynamicWorld *world);
		TypedConstraint (RigidBody *bodyA);
		TypedConstraint (RigidBody *bodyA, RigidBody *bodyB);
		virtual ~TypedConstraint ();

		btTypedConstraint *GetBulletTypedConstraint () const;

	protected:
		btTypedConstraint *mConstraint;
		DynamicWorld *mWorld;
		RigidBody *mBodyA;
		RigidBody *mBodyB;
	};

	typedef PX2::Pointer0<TypedConstraint> TypedConstraintPtr;

	class ActionInterface
	{
	public:
		ActionInterface (DynamicWorld *world);
		ActionInterface (RigidBody *bodyA);
		ActionInterface (RigidBody *bodyA, RigidBody *bodyB); 
		virtual ~ActionInterface();

		btActionInterface* GetBulletActionInterface() const;

	protected:
		btActionInterface *mActionInterface;
		DynamicWorld *mWorld;
		RigidBody *mBodyA;
		RigidBody *mBodyB;
	};

	typedef PX2::Pointer0<ActionInterface> ActionInterfacePtr;
#include "PX2BtDynamicConstraint.inl"

}

#endif