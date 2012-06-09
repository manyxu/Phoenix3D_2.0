/*
*
* 文件名称	：	PX2BtDynamicableRigidBody.cpp
*
*/

#include "PX2Controlledable.hpp"
#include "PX2BtCollisionShape.hpp"
#include "PX2BtCollisionableState.hpp"
#include "PX2BtCollisionWorld.hpp"
#include "PX2BtDynamicWorld.hpp"
#include "PX2BtDynamicableRigidBody.hpp"
#include "PX2BtDynamicRaycastVehicle.hpp"
using namespace TdBt;
using namespace PX2;

RigidBody::RigidBody(DynamicWorld *world, const short collisionGroup,
					 const short collisionMask)
					 :
Collisionable(world, false)
{
	mCollisionGroup = collisionGroup;
	mCollisionMask = collisionMask;
}
//----------------------------------------------------------------------------
RigidBody::~RigidBody()
{
}  
//----------------------------------------------------------------------------
void RigidBody::SetShape(PX2::Movable *movable, CollisionShape *shape, 
						 float bodyRestitution, float bodyFriction, 
						 float bodyMass, const PX2::Vector3f &pos, 
						 const PX2::HQuaternion &quat)
{
	// Movable
	mMovable = movable;
	mMovable->WorldTransform.SetTranslate(pos);
	HMatrix rotMat;
	quat.ToRotationMatrix(rotMat);
	mMovable->WorldTransform.SetRotate(rotMat);

	// State
	mState = new CollisionableState(this);

	// Shape
	mShape = shape;
	btVector3 localInertiaTensor = btVector3(0.0f,0.0f,0.0f);
	if (bodyMass > 0.0f)
		mShape->GetBulletShape()->calculateLocalInertia(bodyMass, 
		localInertiaTensor);

	// Body
	btRigidBody *body = new btRigidBody(bodyMass, mState,
		mShape->GetBulletShape(), localInertiaTensor);
	body->setRestitution(bodyRestitution);
	body->setFriction(bodyFriction);

	// 动态不需要设置
	//body->getWorldTransform().setOrigin(btVector3(pos.X(),
	//	pos.Y(), pos.Z()));
	//body->getWorldTransform().setRotation(btQuaternion(quat.X(),
	//	quat.Y(), quat.Z(), quat.W()));

	mBtCollisionObject = body;

	GetDynamicWorld()->AddRigidBody(this, mCollisionGroup, mCollisionMask);

	//SetKinematicObject(true);
}
//----------------------------------------------------------------------------
void RigidBody::SetStaticShape(PX2::Movable *movable, CollisionShape *shape,
							   const float bodyRestitution, const float bodyFriction, 
							   const float bodyMass, const PX2::Vector3f &pos,
							   const PX2::HQuaternion &quat)
{
	// Movable
	mMovable = movable;
	mMovable->WorldTransform.SetTranslate(pos);
	HMatrix rotMat;
	quat.ToRotationMatrix(rotMat);
	mMovable->WorldTransform.SetRotate(rotMat);

	// State
	mState = new CollisionableState(this);

	// Shape
	mShape = shape;
	btVector3 localInertiaTensor = btVector3(0.0f,0.0f,0.0f);
	if (bodyMass > 0.0f)
		mShape->GetBulletShape()->calculateLocalInertia(bodyMass, 
		localInertiaTensor);

	// Body
	btRigidBody *body = new btRigidBody((btScalar)0, mState,
		mShape->GetBulletShape(), localInertiaTensor);
	body->setRestitution(bodyRestitution);
	body->setFriction(bodyFriction);
	body->getWorldTransform().setOrigin(btVector3(pos.X(),
		pos.Y(), pos.Z()));
	body->getWorldTransform().setRotation(btQuaternion(quat.X(),
		quat.Y(), quat.Z(), quat.W()));

	mBtCollisionObject = body;

	GetDynamicWorld()->AddRigidBody(this, mCollisionGroup, mCollisionMask);

	//SetKinematicObject(true);
}
//----------------------------------------------------------------------------
void RigidBody::SetStaticShape(CollisionShape *shape, 
							   const float bodyRestitution,
							   const float bodyFriction, 
							   const PX2::Vector3f &pos, 
							   const PX2::HQuaternion &quat)
{
	// Body
	btRigidBody *body = new btRigidBody((btScalar)0, 0, 
		shape->GetBulletShape());
	body->setRestitution(bodyRestitution);
	body->setFriction(bodyFriction);
	body->getWorldTransform().setOrigin(btVector3(pos.X(), pos.Y(), pos.Z()));
	body->getWorldTransform().setRotation(btQuaternion(quat.X(), quat.Y(),
		quat.Z(), quat.W()));

	mBtCollisionObject = body;

	GetDynamicWorld()->AddRigidBody(this, mCollisionGroup, mCollisionMask);

	//SetKinematicObject(true);
}
//----------------------------------------------------------------------------
void RigidBody::SetLinearVelocity (const PX2::Vector3f &vel)
{
	GetBulletRigidBody()->setLinearVelocity(btVector3(vel.X(), vel.Y(), 
		vel.Z()));
}
//----------------------------------------------------------------------------
void RigidBody::SetLinearVelocity (const float x, const float y, const float z)
{
	GetBulletRigidBody()->setLinearVelocity(btVector3(x,y,z));
}
//----------------------------------------------------------------------------
PX2::Vector3f RigidBody::GetLinearVelocity ()
{
	const btVector3 vel = GetBulletRigidBody()->getLinearVelocity();
	return Converter::Vector3fConvertFrom(vel);
}
//----------------------------------------------------------------------------
void RigidBody::ApplayImpulse(const Vector3f &impulse, const Vector3f &position)
{
	GetBulletRigidBody()->applyImpulse(Converter::ConvertFrom(impulse),
		Converter::ConvertFrom(position));
}
//----------------------------------------------------------------------------
void RigidBody::ApplayForce (const Vector3f &impulse, const Vector3f &position)
{
	GetBulletRigidBody()->applyForce(Converter::ConvertFrom(impulse),
		Converter::ConvertFrom(position));
}
//----------------------------------------------------------------------------
void RigidBody::SetKinematicObject (bool kinematic)
{
	if (IsKinematicObject() != kinematic)
	{
		GetBulletRigidBody()->setCollisionFlags(GetBulletRigidBody()
			->getCollisionFlags()^btCollisionObject::CF_KINEMATIC_OBJECT);
	}
} 
//----------------------------------------------------------------------------
bool RigidBody::IsStaticObject() const 
{
	return GetBulletRigidBody()->isStaticObject();
}
//----------------------------------------------------------------------------
bool RigidBody::IsKinematicObject() const 
{
	return GetBulletRigidBody()->isKinematicObject();
};
//----------------------------------------------------------------------------
void RigidBody::DisableDeactivation()
{
	GetBulletRigidBody()->setActivationState(DISABLE_DEACTIVATION);
}
//----------------------------------------------------------------------------
void RigidBody::EnableActiveState()
{
	GetBulletRigidBody()->setActivationState(ACTIVE_TAG);
}
//----------------------------------------------------------------------------
void RigidBody::ForceActivationState()
{
	GetBulletRigidBody()->forceActivationState(ACTIVE_TAG);
}
//----------------------------------------------------------------------------
void RigidBody::SetDeactivationTime(const float time)
{
	GetBulletRigidBody()->setDeactivationTime(time);
}
//----------------------------------------------------------------------------
const btTransform &RigidBody::GetCenterOfMassTransform() const
{
	return GetBulletRigidBody()->getCenterOfMassTransform();
}
//----------------------------------------------------------------------------
PX2::HQuaternion RigidBody::GetCenterOfMassOrientation() const
{
	return Converter::ConvertFrom(GetCenterOfMassTransform().getRotation());
}
//----------------------------------------------------------------------------
inline PX2::Vector3f RigidBody::GetCenterOfMassPosition() const
{
	return Converter::Vector3fConvertFrom(GetBulletRigidBody()->
		getCenterOfMassPosition());
}
//----------------------------------------------------------------------------   
Vector3f RigidBody::GetCenterOfMassPivot(const PX2::Vector3f &pivotPosition) 
const
{
	const btVector3 centerOfMassPivot(GetCenterOfMassTransform().inverse() *
		Converter::ConvertFrom(pivotPosition));

	return Converter::Vector3fConvertFrom(centerOfMassPivot);
}
//----------------------------------------------------------------------------
void RigidBody::SetDamping (const float linearDamping,
							const float angularDamping)
{
	GetBulletRigidBody()->setDamping(linearDamping, angularDamping);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// WheeledRigidBody
//----------------------------------------------------------------------------
WheeledRigidBody::WheeledRigidBody(DynamicWorld *world)
								   :
RigidBody(world)
{
	mVehicle = 0;
}
//----------------------------------------------------------------------------
WheeledRigidBody::~WheeledRigidBody ()
{

}
//----------------------------------------------------------------------------