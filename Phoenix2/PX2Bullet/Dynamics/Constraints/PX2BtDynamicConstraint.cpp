/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtDynamicConstraint.cpp
*
*/

#include "PX2BtDynamicConstraint.hpp"
#include "PX2BtDynamicWorld.hpp"
#include "PX2BtDynamicableRigidBody.hpp"
using namespace TdBt;

TypedConstraint::TypedConstraint (DynamicWorld *world)
:
mWorld(world),
mConstraint(0),
mBodyA(0),
mBodyB(0)
{
}
//----------------------------------------------------------------------------
TypedConstraint::TypedConstraint (RigidBody *bodyA)
:
mConstraint(0),
mBodyA(bodyA),
mBodyB(0)
{
	mWorld = bodyA->GetDynamicWorld();
}
//----------------------------------------------------------------------------
TypedConstraint::TypedConstraint (RigidBody *bodyA, RigidBody *bodyB)
:
mConstraint(0),
mBodyA(bodyA),
mBodyB(bodyB)
{
	mWorld = bodyA->GetDynamicWorld();

	assertion(bodyA->GetDynamicWorld() == bodyB->GetDynamicWorld(),
		"bodyA and bodyB must have the same world.");
}
//----------------------------------------------------------------------------
TypedConstraint::~TypedConstraint ()
{
	if (mConstraint)
	{
		assertion(mWorld->IsConstraintIn(this)==false,
			"");

		delete mConstraint;
		mConstraint = 0;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ActionInterface
//----------------------------------------------------------------------------
ActionInterface::ActionInterface (DynamicWorld *world)
{
	mActionInterface = 0;
	mBodyA = 0;
	mBodyB = 0;
	mWorld = world;
}
//----------------------------------------------------------------------------
ActionInterface::ActionInterface (RigidBody *bodyA)
{
	mActionInterface = 0;
	mBodyA = bodyA;
	mBodyB = 0;
	mWorld = mBodyA->GetDynamicWorld();
}
//----------------------------------------------------------------------------
ActionInterface::ActionInterface (RigidBody *bodyA, RigidBody *bodyB)
{
	mActionInterface = 0;
	mBodyA = bodyA;
	mBodyB = bodyB;
	assertion(mBodyA->GetDynamicWorld() == mBodyB->GetDynamicWorld(),
		"bodyA and bodyB must have the same world.");
	mWorld = mBodyA->GetDynamicWorld();
}
//----------------------------------------------------------------------------
ActionInterface::~ActionInterface()
{
	if (mActionInterface)
		delete mActionInterface;
}
//----------------------------------------------------------------------------