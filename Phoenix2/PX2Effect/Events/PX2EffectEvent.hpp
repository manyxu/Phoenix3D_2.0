/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EffectEvent.hpp
*
* 版本		:	1.0 (2011/12/17)
*
* 作者		：	more
*
*/

#ifndef PX2EFFECTEVENT_HPP
#define PX2EFFECTEVENT_HPP

#include "PX2EffectPrerequisites.hpp"
#include "PX2TRange.hpp"
#include "PX2Particle.hpp"

namespace PX2
{

	class ParticleEmitterController;

	class EffectEvent : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EffectEvent);

	public:
		virtual ~EffectEvent ();

		// 时间
		TRange<float> GetTimeRange () const;
		void SetTimeRange (const TRange<float> range);

		// 激活时间
		/*
		* 粒子发射器启动时会从TimeRange抓取一个随机时间，作为粒子系统启动的确
		* 切时间。
		*/
		float GetActivateTime () const;
		void SetActivateTime (float actTime);

		// 改变
		bool IsFadeTo () const;
		void SetBeFadeTo (bool fade);

		// 更新粒子
		virtual void UpdateParticleEmitter (ParticleEmitterController &ctrl);
		virtual void UpdateParticle (Particle &particle);

		// 下一个事件
		EffectEvent *NextEvent;

	protected:
		EffectEvent ();
		TRange<float> mTimeRange;

		float mActivateTime;
		bool mIsFadeTo;
	};

	PX2_REGISTER_STREAM(EffectEvent);
	typedef Pointer0<EffectEvent> EffectEventPtr;
#include "PX2EffectEvent.inl"

	//----------------------------------------------------------------------------
	// 粒子事件比较函数
	class EffectEvent_CompareFun :
		public std::binary_function <EffectEvent*, EffectEvent*, bool >
	{
	public:
		bool operator()( const EffectEvent *lhs, const EffectEvent *rhs ) const
		{
			return lhs->GetActivateTime() < rhs->GetActivateTime();
		}
	};
	//----------------------------------------------------------------------------

}

#endif