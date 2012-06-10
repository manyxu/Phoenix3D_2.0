/*
* Turandot 3D 游戏引擎 Version 1.0
*
* Copyright (C) 2009-2011 http://www.Turandot3d.org/
*
* 文件名称	：	SteeringBehavior.hpp
*
* 版本		:	1.0 (2011/07/24)
*
* 作者		：	许多
*
*/

#ifndef STEERINGBEHAVIOR_HPP
#define STEERINGBEHAVIOR_HPP

namespace Td
{

	class Actor;
	
	class SteeringBehavior
	{
	public:
		SteeringBehavior ();
		~SteeringBehavior ();

		enum SummingMethod
		{
			SM_WEIGHTEDAVERAGE,
			SM_PRIORITIZED,
			SM_DITHERED,
			SM_MAX_MODE
		};

		enum BehaviorType
		{
			BT_NONE					= 0x00000,
			BT_SEEK					= 0x00002,
			BT_FLEE					= 0x00004,
			BT_ARRIVE				= 0x00008,
			BT_WANDER				= 0x00010,
			BT_COHESION				= 0x00020,
			BT_SEPARATION			= 0x00040,
			BT_ALLIGNMENT			= 0x00080,
			BT_OBSTACLE_AVOIDANCE	= 0x00100,
			BT_WALLAVOIDANCE		= 0x00200,
			BT_FOLLOWPATH			= 0x00400,
			BT_PURSUIT				= 0x00800,
			BT_EVADE				= 0x01000,
			BT_INTERPOSE			= 0x02000,
			BT_HID					= 0x04000,
			BT_FLOCK				= 0x08000,
			BT_OFFSET_PURSUIT		= 0x10000,
		};

		enum DecelerateMode
		{
			DM_SLOW = 3,
			DM_NORMAL = 2,
			DM_FAST = 1
		};

		AVector Seek (APoint toPosition);
		AVector Flee (APoint fromPosition);
		AVector Arrive (APoint toPosition, DecelerateMode mode);
		AVector Pursuit (const Actor *actor);
		AVector Wander ();
		AVector FollowPath ();

	protected:
		Actor *mActor;

		// Path
		Path *mPath;
		double mWayPointSeekDistSq;

		// Wander
		double mWanderTarget;
		double mWanderJitter;
		double mWanderRadius;
		double mWanderDistance;
	};
}

#endif