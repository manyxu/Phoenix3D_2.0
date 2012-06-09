/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2BtCollisionableState.hpp
*
* 版本		:	1.0 (2011/03/09)
*
* 作者		：	more
*
*/

#ifndef PX2BTCOLLISIONABLESTATE_HPP
#define PX2BTCOLLISIONABLESTATE_HPP

#include "PX2BtPreRequisites.hpp"

namespace TdBt
{

	class Collisionable;

	/// 碰撞状态
	/**
	* bullet使用碰撞状态改变几何物体的方位。getWorldTransform用来初始化物理碰撞
	* 体的方位。当物理世界更新时，setWorldTransform更新碰撞对象的方位。
	*/
	class CollisionableState : public btMotionState
	{
	public:
		CollisionableState (Collisionable *object);
		virtual ~CollisionableState ();

		virtual void getWorldTransform (btTransform& worldTrans ) const;
		virtual void setWorldTransform (const btTransform& worldTrans);

	private:
		Collisionable *mCollisionable;
		btTransform mWorldTrans;
	};

	typedef PX2::Pointer0<CollisionableState> CollisionableStatePtr;

}

#endif