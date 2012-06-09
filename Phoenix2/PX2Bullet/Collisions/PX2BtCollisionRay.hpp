/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2BtCollisionRay.hpp
*
* 版本		:	1.0 (2011/03/10)
*
* 作者		：	more
*
*/

#ifndef PX2BTCOLLISIONRAY_HPP
#define PX2BTCOLLISIONRAY_HPP

#include "PX2BtPreRequisites.hpp"

namespace TdBt
{

	class CollisionWorld;
	class Collisionable;

	// collision ray result callback
	class C_RayResultCallback
	{
	public:
		virtual ~C_RayResultCallback ();

		btCollisionWorld::RayResultCallback *GetBulletRayResultCallback () const;

		bool IsCollide () const;

		void SetRay (const PX2::Ray3f &ray);
		void SetWorld (CollisionWorld *world);
		void SetMaxDistance (float max_distance);

		const PX2::Ray3f &GetRay () const;
		PX2::Vector3f GetRayStartPoint() const;
		PX2::Vector3f GetRayEndPoint() const;

	protected:
		C_RayResultCallback (const PX2::Ray3f &ray,
			CollisionWorld *world, float maxDistance);

		btCollisionWorld::RayResultCallback *mRayResultCallback;
		CollisionWorld *mWorld;
		PX2::Ray3f mRay;
		float mMaxDistance;
	};

	class C_ClosestRayResultCallback : public C_RayResultCallback
	{
	public:
		C_ClosestRayResultCallback (const PX2::Ray3f &ray, CollisionWorld *world,
			 float maxDistance);
		virtual ~C_ClosestRayResultCallback();
		
		btCollisionWorld::ClosestRayResultCallback *
			GetBulletClosestRayResultCallback () const;

		Collisionable *GetCollisionable () const;
		PX2::Vector3f GetCollisionPoint () const;
		PX2::Vector3f GetCollisionNormal () const;		
	};

	typedef PX2::Pointer0<C_ClosestRayResultCallback> C_ClosestRayResultCallbackPtr;

#include "PX2BtCollisionRay.inl"

}

#endif