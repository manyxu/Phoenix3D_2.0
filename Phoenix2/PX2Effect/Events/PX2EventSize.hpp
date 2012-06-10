/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EventSize.hpp
*
* 版本		:	1.0 (2011/12/17)
*
* 作者		：	more
*
*/

#ifndef PX2EVENTSIZE_HPP
#define PX2EVENTSIZE_HPP

#include "PX2EffectPrerequisites.hpp"
#include "PX2EffectEvent.hpp"

namespace PX2
{

	// 粒子大小改变事件
	class ParticleEvent_Size : public EffectEvent
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(ParticleEvent_Size);

	public:
		ParticleEvent_Size ();
		virtual ~ParticleEvent_Size ();

		void SetSizeURange (TRange<float> range);
		TRange<float> GetSizeURange () const;
		void SetSizeRRange (TRange<float> range);
		TRange<float> GetSizeRRange () const;

		bool FadeAllowed ();
		virtual void UpdateParticle (Particle &particle);

	protected:
		TRange<float> mSizeURange;
		TRange<float> mSizeRRange;
	};

	PX2_REGISTER_STREAM(ParticleEvent_Size);
	typedef Pointer0<ParticleEvent_Size> ParticleEvent_SizePtr;
#include "PX2EventSize.inl"

}

#endif