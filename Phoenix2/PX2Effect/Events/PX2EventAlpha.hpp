/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EventAlpha.hpp
*
* 版本		:	1.0 (2011/12/22)
*
* 作者		：	more
*
*/

#ifndef PX2EVENT_ALPHA_HPP
#define PX2EVENT_ALPHA_HPP

#include "PX2EffectPrerequisites.hpp"
#include "PX2EffectEvent.hpp"

namespace PX2
{

	class ParticleEvent_Alpha : public EffectEvent
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(ParticleEvent_Alpha);

	public:
		ParticleEvent_Alpha ();
		virtual ~ParticleEvent_Alpha ();

		void SetAlphaRange (const TRange<float> range);
		TRange<float> GetAlphaRange () const;

		bool FadeAllowed ();
		virtual void UpdateParticle (Particle &particle);

	protected:
		TRange<float> mAlpha;
	};

	PX2_REGISTER_STREAM(ParticleEvent_Alpha);
	typedef Pointer0<ParticleEvent_Alpha> ParticleEvent_AlphaPtr;
#include "PX2EventAlpha.inl"

}

#endif