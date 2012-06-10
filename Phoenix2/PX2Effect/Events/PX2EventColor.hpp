/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ParticleEvent_Color.hpp
*
* 版本		:	1.0 (2011/12/22)
*
* 作者		：	more
*
*/

#ifndef PX2EVENT_COLOR_HPP
#define PX2EVENT_COLOR_HPP

#include "PX2EffectPrerequisites.hpp"
#include "PX2EffectEvent.hpp"

namespace PX2
{

	class ParticleEvent_Color : public EffectEvent
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(ParticleEvent_Color);

	public:
		ParticleEvent_Color ();
		virtual ~ParticleEvent_Color ();

		void SetColorRange (const TRange<Float3> range);
		TRange<Float3> GetColorRange () const;

		bool FadeAllowed ();
		virtual void UpdateParticle (Particle &particle);

	protected:
		TRange<Float3> mColor;
	};

	PX2_REGISTER_STREAM(ParticleEvent_Color);
	typedef Pointer0<ParticleEvent_Color> ParticleEvent_ColorPtr;
#include "PX2EventColor.inl"

}

#endif