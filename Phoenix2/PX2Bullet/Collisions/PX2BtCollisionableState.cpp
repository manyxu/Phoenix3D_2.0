/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionableState.cpp
*
*/

#include "PX2BtCollisionableState.hpp"
#include "PX2BtCollisionable.hpp"
#include "PX2BtConverter.hpp"
using namespace TdBt;
using namespace PX2;

CollisionableState::CollisionableState (Collisionable *object)
:
mCollisionable(object)
{
}
//----------------------------------------------------------------------------
CollisionableState::~CollisionableState ()
{
}
//----------------------------------------------------------------------------
void CollisionableState::getWorldTransform (btTransform& worldTrans ) const
{
	assertion(mCollisionable!=0, "mCollisionable must not be 0.");

	worldTrans.setOrigin(Converter::ConvertFrom(mCollisionable
		->GetPosition()));
	worldTrans.setRotation(Converter::ConvertFrom(HQuaternion(mCollisionable
		->GetRotation())));
}
//----------------------------------------------------------------------------
void CollisionableState::setWorldTransform (const btTransform& worldTrans)
{
	assertion(mCollisionable!=0, "mCollisionable must not be 0.");

	mCollisionable->SetTransform(worldTrans);
	mWorldTrans = worldTrans;
}
//----------------------------------------------------------------------------