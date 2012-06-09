/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2BtCollisionWorld.hpp
*
* 版本		:	1.0 (2011/03/09)
*
* 作者		：	more
*
*/

#ifndef PX2BTCOLLISIONWORLD_HPP
#define PX2BTCOLLISIONWORLD_HPP

#include "PX2BtPreRequisites.hpp"

namespace TdBt
{

	class Collisionable;
	class DebugLines;
	class DebugDrawer;
	class C_RayResultCallback;

	class CollisionWorld
	{
	public:
		CollisionWorld (const PX2::AxisAlignedBox3f &bound, bool init=true,
			bool set32bitsAxisSweep=true, unsigned int maxHandles=1500000);
		virtual ~CollisionWorld ();

		// 碰撞体
		void AddCollisionable (Collisionable *collisionable, 
			short int filterGroup=1, short int collisionFilter=-1);
		bool RemoveCollisionable (Collisionable *collisionable);
		void DiscreteCollide ();
		bool IsIn (Collisionable *collisionable) const;
		Collisionable *Find (PX2::Movable *movable) const;
		Collisionable *Find (btCollisionObject *object) const;

		// 调试
		void SetShowDebugContactPoints (bool show);
		bool IsShowDebugContactPoints () const;
		void SetDebugContactPoints (DebugLines *debugContacts);
		DebugLines *GetDebugContactPoints ();

		void SetShowDebugShapes (bool show);
		bool IsShowDebugShapes () const;

		// DebugDrawer
		void SetDebugDrawer (DebugDrawer *debugDrawer);
		DebugDrawer *GetDebugDrawer ();

		// bullet 碰撞世界
		btCollisionWorld *GetBulletCollisionWorld () const;

		// 射线
		void LaunchRay (C_RayResultCallback &ray, 
			short int collisionFilterMask=-1);

	protected:
		btVector3 mAABBMin;
		btVector3 mAABBMax;
		btCollisionWorld *mWorld;
		btCollisionDispatcher *mDispatcher;
		btBroadphaseInterface *mBroadphase;
		btDefaultCollisionConfiguration mDefaultCollisionConfiguration;
		PX2::AxisAlignedBox3f mBound;
		std::vector<Collisionable*> mCollisionables;
		bool mShowDebugShapes;
		DebugLines *mDebugContactPoints;
		bool mShowDebugContactPoints;
		DebugDrawer *mDebugDrawer;
	};

	typedef PX2::Pointer0<CollisionWorld> CollisionWorldPtr;
#include "PX2BtCollisionWorld.inl"

}

#endif