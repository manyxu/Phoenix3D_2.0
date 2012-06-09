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

#ifndef PX2BTDYNAMICRAYCASTVEHICLE_HPP
#define PX2BTDYNAMICRAYCASTVEHICLE_HPP

#include "PX2BtPreRequisites.hpp"
#include "PX2BtDynamicConstraint.hpp"

namespace TdBt
{

	class DynamicWorld;
	class WheeledRigidBody;

	class VehicleRayCaster
	{
	public:
		VehicleRayCaster (DynamicWorld *world);
		virtual ~VehicleRayCaster ();

		btVehicleRaycaster *GetBulletVehicleRayCaster();

	private:
		btDefaultVehicleRaycaster *mBulletVehicleRayCaster;        
	};

	typedef PX2::Pointer0<VehicleRayCaster> VehicleRayCasterPtr;

	class VehicleTuning
	{
	public:
		VehicleTuning(const float suspensionStiffness,
			const float suspensionCompression, const float suspensionDamping,
			const float maxSuspensionTravelCm, const float frictionSlip);
		virtual ~VehicleTuning();

		btRaycastVehicle::btVehicleTuning *GetBulletVehicleTuning();

	private:
		btRaycastVehicle::btVehicleTuning *mBulletVehicleTuning;        
	};

	typedef PX2::Pointer0<VehicleTuning> VehicleTuningPtr;

	class WheelInfo
	{
	public:
		WheelInfo (btWheelInfo &wheel);
		virtual ~WheelInfo ();

		btWheelInfo *GetBulletWheelInfo ();

	protected:
		btWheelInfo *mWheel;
	};

	typedef PX2::Pointer0<WheelInfo> WheelInfoPtr;

	class RaycastVehicle : public ActionInterface
	{
	public:
		RaycastVehicle (WheeledRigidBody *body, VehicleTuning *vehicleTuning,
			VehicleRayCaster *caster=0);
		virtual ~RaycastVehicle ();

		// bullet vehicle
		btRaycastVehicle *GetBulletVehicle ();

		void SetCoordinateSystem (int rightIndex,int upIndex,int forwardIndex);

		// 轮子
		void AddWheel (PX2::Movable *movable, const PX2::Vector3f &connectPoint,
			const PX2::Vector3f &wheelDirection, const PX2::Vector3f wheelAxle,
			const float suspensionRestLength, const float wheelRadius,
			const bool isFrontWheel, const float wheelFriction,
			const float roolInfluence);

		void SetWheelsAttached ();

		// 更新物理引擎方位到场景中
		void UpdateTransform ();

		void ApplyEngineForce (float engineForce, int wheelIndex);
		void SetSteeringValue (float steering, int wheelIndex);

	protected:
		VehicleTuning *mVehicleTuning;
		VehicleRayCaster *mRayCaster;
		std::vector<btWheelInfo*> mWheelInfos;
		std::vector<PX2::Movable*> mWheelNodes;
		WheeledRigidBody *mWheelledBody;
	};

	typedef PX2::Pointer0<RaycastVehicle> RaycastVehiclePtr;
#include "PX2BtDynamicRaycastVehicle.inl"

}

#endif