/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtDynamicRaycastVehicle.cpp
*
*/

#include "PX2BtDynamicRaycastVehicle.hpp"
#include "PX2BtDynamicConstraint.hpp"
#include "PX2BtDynamicWorld.hpp"
#include "PX2BtDynamicableRigidBody.hpp"
using namespace TdBt;
using namespace PX2;

//----------------------------------------------------------------------------
VehicleRayCaster::VehicleRayCaster(DynamicWorld *world)
{
	mBulletVehicleRayCaster = 0;
	mBulletVehicleRayCaster = new btDefaultVehicleRaycaster(world
		->GetBulletDynamicWorld());
}
//----------------------------------------------------------------------------
VehicleRayCaster::~VehicleRayCaster ()
{
	if (mBulletVehicleRayCaster)
	{
		delete mBulletVehicleRayCaster;
		mBulletVehicleRayCaster = 0;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// VehicleTuning
//----------------------------------------------------------------------------
VehicleTuning::VehicleTuning(const float suspensionStiffness,
			  const float suspensionCompression, const float suspensionDamping,
			  const float maxSuspensionTravelCm, const float frictionSlip)
{
	mBulletVehicleTuning = 0;
	mBulletVehicleTuning = new btRaycastVehicle::btVehicleTuning();
	mBulletVehicleTuning->m_suspensionStiffness =  suspensionStiffness;
	mBulletVehicleTuning->m_suspensionCompression = suspensionCompression;
	mBulletVehicleTuning->m_suspensionDamping = suspensionDamping;
	mBulletVehicleTuning->m_maxSuspensionTravelCm = maxSuspensionTravelCm;
	mBulletVehicleTuning->m_frictionSlip = frictionSlip;
}
//----------------------------------------------------------------------------
VehicleTuning::~VehicleTuning()
{
	if (mBulletVehicleTuning)
	{
		delete mBulletVehicleTuning;
		mBulletVehicleTuning = 0;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// WheelInfo
//----------------------------------------------------------------------------
WheelInfo::WheelInfo (btWheelInfo &wheel)
{
	mWheel = &wheel;
}
//----------------------------------------------------------------------------
WheelInfo::~WheelInfo ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// RaycastVehicle
//----------------------------------------------------------------------------
RaycastVehicle::RaycastVehicle (WheeledRigidBody *body,
								VehicleTuning *vehicleTuning,
								VehicleRayCaster *caster)
								:
ActionInterface(body),
mVehicleTuning(vehicleTuning),
mRayCaster(caster)
{
	if (!mRayCaster)
		mRayCaster = new VehicleRayCaster(mWorld);

	btRaycastVehicle *raycastVehicle = new btRaycastVehicle(
		*(mVehicleTuning->GetBulletVehicleTuning()),
		body->GetBulletRigidBody(), mRayCaster->GetBulletVehicleRayCaster());

	mActionInterface = raycastVehicle;
	mWorld->AddVehicle(this);
	body->SetVehicle(this);
}
//----------------------------------------------------------------------------
RaycastVehicle::~RaycastVehicle ()
{

}
//----------------------------------------------------------------------------
void RaycastVehicle::SetCoordinateSystem(int rightIndex, int upIndex,
										 int forwardIndex)
{
	GetBulletVehicle()->setCoordinateSystem(rightIndex, upIndex, forwardIndex);
}
//----------------------------------------------------------------------------
void RaycastVehicle::AddWheel (PX2::Movable *movable, 
							   const PX2::Vector3f &connectPoint, 
							   const PX2::Vector3f &wheelDirection, 
							   const PX2::Vector3f wheelAxle,
							   const float suspensionRestLength, 
							   const float wheelRadius,
							   const bool isFrontWheel,
							   const float wheelFriction,
							   const float roolInfluence)
{
	// ray cast
	btRaycastVehicle *vehicle = (btRaycastVehicle*)mActionInterface;

	// wheel info
	mWheelInfos.push_back(&vehicle->addWheel(Converter::ConvertFrom(
		connectPoint), Converter::ConvertFrom(wheelDirection),
		Converter::ConvertFrom(wheelAxle), suspensionRestLength, wheelRadius,
		*mVehicleTuning->GetBulletVehicleTuning(), isFrontWheel));

	const int currentWheelIndex = (int)mWheelInfos.size() - 1;
	mWheelInfos[currentWheelIndex]->m_suspensionStiffness = mVehicleTuning
		->GetBulletVehicleTuning()->m_suspensionStiffness;
	mWheelInfos[currentWheelIndex]->m_wheelsDampingRelaxation = mVehicleTuning
		->GetBulletVehicleTuning()->m_suspensionDamping;
	mWheelInfos[currentWheelIndex]->m_wheelsDampingCompression = mVehicleTuning
		->GetBulletVehicleTuning()->m_suspensionCompression;
	mWheelInfos[currentWheelIndex]->m_frictionSlip = wheelFriction;
	mWheelInfos[currentWheelIndex]->m_rollInfluence = roolInfluence;
	
	// PX2 object
	movable->WorldTransformIsCurrent = true;
	movable->WorldTransform.SetTranslate(connectPoint);
	mWheelNodes.push_back(movable);
}
//----------------------------------------------------------------------------
void RaycastVehicle::SetWheelsAttached ()
{
	btRaycastVehicle *vehicle = (btRaycastVehicle*)mActionInterface;

	for (int i=0; i<vehicle->getNumWheels(); i++)
	{
		btWheelInfo &wheel = vehicle->getWheelInfo(i);
		wheel.m_suspensionStiffness = mVehicleTuning->GetBulletVehicleTuning()
			->m_suspensionStiffness;
		wheel.m_wheelsDampingRelaxation = mVehicleTuning
			->GetBulletVehicleTuning()->m_suspensionDamping;
		wheel.m_wheelsDampingCompression = mVehicleTuning
			->GetBulletVehicleTuning()->m_suspensionCompression;
	}
}
//----------------------------------------------------------------------------
void RaycastVehicle::UpdateTransform ()
{
	for (int i=0; i<GetBulletVehicle()->getNumWheels(); i++)
	{
		GetBulletVehicle()->updateWheelTransform(i, true);

		const btTransform &trans = GetBulletVehicle()
			->getWheelInfo(i).m_worldTransform;

		mWheelNodes[i]->WorldTransformIsCurrent = true;
		mWheelNodes[i]->WorldTransform.SetTranslate(Converter::
			APointConvertFrom(trans.getOrigin()));
		HMatrix matRot;
		Converter::ConvertFrom(trans.getRotation()).ToRotationMatrix(matRot);
		mWheelNodes[i]->WorldTransform.SetRotate(matRot);
	}
}
//----------------------------------------------------------------------------
void RaycastVehicle::ApplyEngineForce (float engineForce, int wheel)
{
	GetBulletVehicle()->applyEngineForce(engineForce, wheel);
}
//----------------------------------------------------------------------------
void RaycastVehicle::SetSteeringValue(float steering, int wheel)
{
	GetBulletVehicle()->setSteeringValue (steering, wheel);
}
//----------------------------------------------------------------------------