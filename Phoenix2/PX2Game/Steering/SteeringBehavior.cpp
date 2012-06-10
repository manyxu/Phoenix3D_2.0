/*
*
* ÎÄ¼þÃû³Æ	£º	SteeringBehavior.cpp
*
*/

#include "SteeringBehavior.hpp"
#include "TdActor.hpp"
using namespace Td;

AVector SteeringBehavior::Seek (APoint toPosition)
{
	AVector desiredVelocity = mActor->GetPosition() - actorPosition;
	desiredVelocity.Normalize();

	desiredVelocity *= mActor->GetMaxSpeed();

	return (desiredVelocity - mActor->GetVelocity());
}
//----------------------------------------------------------------------------
AVector SteeringBehavior::Flee (APoint fromPosition)
{
	AVector desiredVelocity = mActor->GetPosition() - fromPosition;
	desiredVelocity.Normalize();

	return (desiredVelocity - mActor->GetVelocity());
}
//----------------------------------------------------------------------------
AVector SteeringBehavior::Arrive (APoint toPosition, DecelerateMode mode)
{
	AVector toTarget = toPosition - mActor->GetPosition();
	float dist = toTarget.Length();

	if (dist > 0)
	{
		const double decelerationTweaker = 0.3f;
		double speed = dist / ((double)mode * decelerationTweaker);
		speed = min(speed, mActor->GetMaxSpeed());

		AVector desiredVelocity = toTarget * speed/dist;

		return (desiredVelocity - mActor->GetVelocity());
	}

	return AVector();
}
//----------------------------------------------------------------------------
AVector SteeringBehavior::Wander ()
{
	double jitterThisTimeSlice = mWanderJitter * mActor->TimeElapsed();

	mWanderTarget += AVector(Mathf::SymmetricRandom()*jitterThisTimeSlice,
		Mathf::SymmetricRandom()*jitterThisTimeSlice,
		Mathf::SymmetricRandom()*jitterThisTimeSlice);
	mWanderTarget.Normalize();

	mWanderTarget *= mWanderRadius;

	AVector target = mWanderTarget + AVector();

	return target - mActor->GetPosition();
}
//----------------------------------------------------------------------------
AVector SteeringBehavior::FollowPath ()
{
	AVector dist = mPath->GetCurrentWayPoint() - mActor->GetPosition();
	float length = dist.Length();

	if (length < mWayPointSeekDistSq)
		mPath->SetNextWayPoint();

	if (!mPath->IsFinished())
	{
		return Seek(mPath->GetCurrentWayPoint());
	}
	else
	{
		return Arrive(mPath->GetCurrentWayPoint(), DM_NORMAL);
	}
}
//----------------------------------------------------------------------------