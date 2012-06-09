/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionableState.cpp
*
*/

#include "PX2BtConverter.hpp"
#include "PX2BtCollisionable.hpp"
#include "PX2BtCollisionWorld.hpp"
#include "PX2BtCollisionShape.hpp"
#include "PX2BtCollisionableState.hpp"
using namespace TdBt;
using namespace PX2;

Collisionable::Collisionable (CollisionWorld *world, bool init)
:
mWorld(world),
mState(0),
mShape(0),
mBtCollisionObject(0)
{
	if (init)
	{
		mBtCollisionObject = new btCollisionObject();
		mState = new CollisionableState(this);
	}
}
//----------------------------------------------------------------------------
Collisionable::~Collisionable ()
{
	GetBulletCollisionWorld()->removeCollisionObject(mBtCollisionObject);
	GetCollisionWorld()->RemoveCollisionable(this);

	mBtCollisionObject = 0;
	mState = 0;
}
//----------------------------------------------------------------------------
void Collisionable::SetPosition (const PX2::APoint &point)
{
	mMovable->WorldBoundIsCurrent = true;
	mMovable->WorldTransform.SetTranslate(point);

	mBtCollisionObject->getWorldTransform().setOrigin(btVector3(point.X(),
		point.Y(), point.Z()));
}
//----------------------------------------------------------------------------
PX2::APoint Collisionable::GetPosition () const
{
	return mMovable->WorldTransform.GetTranslate();
}
//----------------------------------------------------------------------------
void Collisionable::SetRotation (const PX2::HQuaternion &quat)
{
	HMatrix rolateMatrix;
	quat.ToRotationMatrix(rolateMatrix);
	mMovable->WorldTransformIsCurrent = true;
	mMovable->WorldTransform.SetRotate(rolateMatrix);

	mBtCollisionObject->getWorldTransform().setRotation(btQuaternion(quat.X(),
		quat.Y(), quat.Z(), quat.W()));
}
//----------------------------------------------------------------------------
PX2::HQuaternion Collisionable::GetRotation ()
{
	return HQuaternion(mMovable->WorldTransform.GetRotate());
}
//----------------------------------------------------------------------------
void Collisionable::SetPosition (const btVector3 &pos)
{
	SetPosition(PX2::APoint(pos[0], pos[1], pos[2]));
}
//----------------------------------------------------------------------------
void Collisionable::SetRotation (const btQuaternion &quat)
{
	SetRotation(HQuaternion(quat.getW(), quat.getX(), quat.getY(), 
		quat.getZ()));
}
//----------------------------------------------------------------------------
void Collisionable::SetTransform (const btVector3 &pos, 
								  const btQuaternion &quat)
{
	SetPosition(pos);
	SetRotation(quat);
}
//----------------------------------------------------------------------------
void Collisionable::SetTransform (const btTransform& worldTrans)
{
	SetPosition(worldTrans.getOrigin());
	SetRotation(worldTrans.getRotation());
}
//----------------------------------------------------------------------------
void Collisionable::SetShape (CollisionShape *shape, const PX2::APoint &pos,
			   const PX2::HQuaternion &quat)
{
	// Movable
	SetPosition(pos);
	SetRotation(quat);

	// shape
	mShape = shape;
	mBtCollisionObject->setCollisionShape(shape->GetBulletShape());
}
//----------------------------------------------------------------------------
btCollisionWorld *Collisionable::GetBulletCollisionWorld() const
{
	return mWorld->GetBulletCollisionWorld();
}
//----------------------------------------------------------------------------