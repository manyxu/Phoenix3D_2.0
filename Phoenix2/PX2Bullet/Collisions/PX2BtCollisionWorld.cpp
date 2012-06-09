/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionWorld.cpp
*
*/

#include "PX2BtCollisionWorld.hpp"
#include "PX2BtCollisionable.hpp"
#include "PX2BtConverter.hpp"
#include "PX2BtCollisionDebugLines.hpp"
#include "PX2BtCollisionDebugDrawer.hpp"
#include "PX2BtCollisionRay.hpp"
using namespace TdBt;
using namespace PX2;

//----------------------------------------------------------------------------
CollisionWorld::CollisionWorld (const PX2::AxisAlignedBox3f &bound, bool init,
								bool set32bitsAxisSweep, unsigned int maxHandles)
								:
mBound(bound),
mShowDebugShapes(false),
mShowDebugContactPoints(false),
mDebugContactPoints(0),
mDebugDrawer(0)
{
	mDispatcher = new btCollisionDispatcher(&mDefaultCollisionConfiguration);

	if (set32bitsAxisSweep)
	{
		Vector3f min = Vector3f(bound.Min[0], bound.Min[1], bound.Min[2]);
		Vector3f max = Vector3f(bound.Max[0], bound.Max[1], bound.Max[2]);
		mAABBMin = Converter::ConvertFrom(min);
		mAABBMax = Converter::ConvertFrom(max);

		mBroadphase = new bt32BitAxisSweep3(mAABBMin, mAABBMax, maxHandles);
	}
	else
	{
		if (maxHandles > USHRT_MAX)
		{
			maxHandles = USHRT_MAX;
		}

		Vector3f min = Vector3f(bound.Min[0], bound.Min[1], bound.Min[2]);
		Vector3f max = Vector3f(bound.Max[0], bound.Max[1], bound.Max[2]);
		mAABBMin = Converter::ConvertFrom(min);
		mAABBMax = Converter::ConvertFrom(max);

		mBroadphase = new btAxisSweep3(mAABBMin, mAABBMax, 
			(unsigned short)maxHandles);
	}

	if (init)
	{
		mWorld = new btCollisionWorld(mDispatcher, mBroadphase, 
			&mDefaultCollisionConfiguration);

		btCollisionDispatcher *dispatcher =
			static_cast<btCollisionDispatcher*>(mWorld->getDispatcher());
		btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
	}
}
//----------------------------------------------------------------------------
CollisionWorld::~CollisionWorld ()
{
	if (mWorld)
		delete mWorld;

	if (mBroadphase)
		delete mBroadphase;

	if (mDispatcher)
		delete mDispatcher;
}
//----------------------------------------------------------------------------
void CollisionWorld::AddCollisionable (Collisionable *collisionable,
									   short int filterGroup, 
									   short int collisionFilter)
{
	mCollisionables.push_back(collisionable);
	mWorld->addCollisionObject(collisionable->GetBulletObject(), filterGroup,
		collisionFilter);
}
//----------------------------------------------------------------------------
bool CollisionWorld::RemoveCollisionable (Collisionable *collisionable)
{
	std::vector<Collisionable*>::iterator it = find(mCollisionables.begin(),
		mCollisionables.end(), collisionable);

	if (it == mCollisionables.end())
		return false;

	mCollisionables.erase(it);

	return true;
}
//----------------------------------------------------------------------------
void CollisionWorld::DiscreteCollide ()
{
	if (mDebugDrawer) 
		mDebugDrawer->Clear();
	if (mDebugContactPoints) 
		mDebugContactPoints->Clear();

	mWorld->performDiscreteCollisionDetection();

	const unsigned int numManifolds = mWorld->getDispatcher()->getNumManifolds();
	for (unsigned int i=0; i<numManifolds; i++)
	{
		btPersistentManifold *contactManifold = mWorld->getDispatcher()
			->getManifoldByIndexInternal(i);

		btCollisionObject *objA = (btCollisionObject*)(contactManifold->getBody0());
		btCollisionObject *objB = (btCollisionObject*)(contactManifold->getBody1());

		contactManifold->refreshContactPoints(objA->getWorldTransform(), objB
			->getWorldTransform());

		const unsigned int numContacts = contactManifold->getNumContacts();
		for (unsigned int j=0; j<numContacts; j++)
		{
			btManifoldPoint &pt = contactManifold->getContactPoint(j);

			if (mShowDebugContactPoints)
			{
				btVector3 ptA = pt.getPositionWorldOnA();
				btVector3 ptB = pt.getPositionWorldOnB();
				btVector3 ptDistB = ptB + pt.m_normalWorldOnB * 100.0f;

				mDebugContactPoints->AddLine(ptA.x(), ptA.y(), ptA.z(),
					ptB.x(), ptB.y(), ptB.z());
				mDebugContactPoints->AddLine(ptB.x(), ptB.y(), ptB.z(),
					ptDistB.x(), ptDistB.y(), ptDistB.z());
			}
		}
	}

	//if (mDebugContactPoints)
	//	mDebugContactPoints->Draw();

	if (mDebugDrawer) 
	{
		const bool drawFeaturesText = 
			(mDebugDrawer->getDebugMode()
			&
			btIDebugDraw::DBG_DrawFeaturesText)!=0;

		if (drawFeaturesText)
		{
			std::vector<Collisionable*>::iterator it = mCollisionables.begin();
			while (it != mCollisionables.end())
			{
				++it;
			}
		}
	}

	//if (mDebugContactPoints)
	//	mDebugContactPoints->Draw();
}
//----------------------------------------------------------------------------
bool CollisionWorld::IsIn (Collisionable *collisionable) const
{
	std::vector<Collisionable*>::const_iterator it = std::find(
		mCollisionables.begin(), mCollisionables.end(), collisionable);

	if (it != mCollisionables.end())
		return true;

	return false;
}
//----------------------------------------------------------------------------
Collisionable *CollisionWorld::Find (PX2::Movable *movable) const
{
	std::vector<Collisionable*>::const_iterator it = mCollisionables.begin();

	while (it != mCollisionables.end())
	{
		if ((*it)->GetMovable() == movable)
			return (*it);

		++it;
	}

	return 0;
}
//----------------------------------------------------------------------------
Collisionable *CollisionWorld::Find (btCollisionObject *object) const
{
	std::vector<Collisionable*>::const_iterator it = mCollisionables.begin();

	while (it != mCollisionables.end())
	{
		if ((*it)->GetBulletObject() == object)
			return (*it);

		++it;
	}

	return 0;
}
//----------------------------------------------------------------------------
void CollisionWorld::SetShowDebugContactPoints (bool show)
{
	if (show && !mShowDebugContactPoints)
	{
		assertion(mDebugContactPoints==0, "mDebugContactPoints should be 0.");

		mDebugContactPoints = new0 DebugLines();
		mShowDebugContactPoints = true;

		return;
	}

	if (!show && mShowDebugContactPoints)
	{
		assertion(mDebugContactPoints!=0, "mDebugContactPoints should not be 0.");

		mShowDebugContactPoints = false;

		return;
	}
}
//----------------------------------------------------------------------------
bool CollisionWorld::IsShowDebugContactPoints () const
{
	return mShowDebugContactPoints;
}
//----------------------------------------------------------------------------
void CollisionWorld::SetDebugContactPoints (DebugLines *debugContacts)
{
	mDebugContactPoints = debugContacts;
}
//----------------------------------------------------------------------------
DebugLines *CollisionWorld::GetDebugContactPoints ()
{
	return mDebugContactPoints; 
}
//----------------------------------------------------------------------------
void CollisionWorld::SetShowDebugShapes (bool show)
{
	if (mShowDebugShapes != show)
	{
		std::vector<Collisionable*>::iterator it = mCollisionables.begin();
		while (it != mCollisionables.end())
		{

			++it;
		}

		mShowDebugShapes = show;
	}
}
//----------------------------------------------------------------------------
bool CollisionWorld::IsShowDebugShapes () const
{
	return mShowDebugShapes;
}
//----------------------------------------------------------------------------
void CollisionWorld::SetDebugDrawer (DebugDrawer *debugDrawer)
{
	mDebugDrawer = debugDrawer;
	mDebugDrawer->SetDrawWireframe(true);

	((btCollisionWorld*)mWorld)->setDebugDrawer(mDebugDrawer);
}
//----------------------------------------------------------------------------
btCollisionWorld *CollisionWorld::GetBulletCollisionWorld () const
{
	return mWorld;
}
//----------------------------------------------------------------------------
void CollisionWorld::LaunchRay (C_RayResultCallback &ray, 
								short int collisionFilterMask)
{
	mWorld->rayTest(Converter::ConvertFrom(ray.GetRayStartPoint()),
		Converter::ConvertFrom(ray.GetRayEndPoint()),
		*ray.GetBulletRayResultCallback());
	PX2_UNUSED(collisionFilterMask);
}
//----------------------------------------------------------------------------