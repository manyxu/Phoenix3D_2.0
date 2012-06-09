/*
*
* 文件名称	：	PX2BtDynamicWorld.cpp
*
*/

#include "PX2BtDynamicWorld.hpp"
using namespace TdBt;
using namespace PX2;
using namespace std;

DynamicWorld::DynamicWorld (const PX2::AxisAlignedBox3f &bounds, 
							const PX2::Vector3f &gravity, bool init,
							bool set32BitAxisSweep, unsigned int maxHandles)
							:
 CollisionWorld(bounds, false, set32BitAxisSweep, maxHandles)
{
	mConstraintSolver = 0;
	mConstraintSolver = new btSequentialImpulseConstraintSolver();

	if (init)
	{
		mWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, 
			mConstraintSolver, &mDefaultCollisionConfiguration);
		((btDiscreteDynamicsWorld*)mWorld)->setGravity(Converter::ConvertFrom(gravity));
	}
}
//----------------------------------------------------------------------------
DynamicWorld::~DynamicWorld ()
{
	if (mConstraintSolver)
	{
		delete mConstraintSolver;
		mConstraintSolver = 0;
	}

	if (mWorld)
	{
		delete mWorld;
		mWorld = 0;
	}
}
//----------------------------------------------------------------------------
template <class BTDNYWORLDCLASS>
void DynamicWorld::CreateBtDynamicWorld (BTDNYWORLDCLASS *&createWorld)
{
	createWorld = new BTDNYWORLDCLASS(mDispatcher, mBroadphase, 
		mConstraintSolver, &mDefaultCollisionConfiguration);
	mWorld = createWorld;
}
//----------------------------------------------------------------------------
void DynamicWorld::AddRigidBody (RigidBody *body, short collisionGroup, 
								 short collisionMask)
{
	mCollisionables.push_back((Collisionable*)body);

	if (collisionGroup==0 && collisionMask==0)
	{
		((btDiscreteDynamicsWorld*)mWorld)->addRigidBody(body
			->GetBulletRigidBody());
	}
	else
	{
		((btDiscreteDynamicsWorld*)mWorld)->addRigidBody(body
			->GetBulletRigidBody(), collisionGroup, collisionMask);
	}
}
//----------------------------------------------------------------------------
bool DynamicWorld::RemoveRigidRody (RigidBody *body)
{
	std::vector<Collisionable*>::iterator it = find(mCollisionables.begin(),
		mCollisionables.end(), (Collisionable*)body);

	if (it == mCollisionables.end())
		return false;

	((btDiscreteDynamicsWorld*)mWorld)->removeRigidBody(body
		->GetBulletRigidBody());

	mCollisionables.erase(it);

	return true;
}
//----------------------------------------------------------------------------
void DynamicWorld::AddConstraint (TypedConstraint *constraint)
{
	GetBulletDynamicWorld()->addConstraint(constraint->GetBulletTypedConstraint());
	mConstraints.push_back(constraint);
}
//----------------------------------------------------------------------------
void DynamicWorld::RemoveConstraint (TypedConstraint *constraint)
{
	GetBulletDynamicWorld()->removeConstraint(constraint
		->GetBulletTypedConstraint());
	std::vector<TypedConstraintPtr>::iterator it = mConstraints.begin();
	while (it != mConstraints.end())
	{
		if ((*it) == constraint)
		{
			mConstraints.erase(it);
			break;
		}

		++it;
	}
}
//----------------------------------------------------------------------------
bool DynamicWorld::IsConstraintIn (TypedConstraint *constraint) const
{
	std::vector<TypedConstraintPtr>::const_iterator it = mConstraints.begin();
	while (it != mConstraints.end())
	{
		if ((*it) == constraint)
			return true;
		++it;
	}

	return false;
}
//----------------------------------------------------------------------------
void DynamicWorld::AddVehicle(RaycastVehicle *vehicle)
{
	GetBulletDynamicWorld()->addVehicle(vehicle->GetBulletVehicle());
	mActionInterfaces.push_back((ActionInterface*)vehicle);
}
//----------------------------------------------------------------------------
void DynamicWorld::StepSimulation (const float elapsedTime, int maxSubSteps, 
								   const float fixedTimeStep)
{
	// 仿真
	((btDiscreteDynamicsWorld*)mWorld)->stepSimulation(elapsedTime, 
		maxSubSteps, fixedTimeStep);

	mWorld->debugDrawWorld();
}
//----------------------------------------------------------------------------