/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_P_LifeInit.hpp
*
*/

#ifndef PX2EM_P_LIFEINIT_HPP
#define PX2EM_P_LIFEINIT_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_LifeInit : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_LifeInit);

	public:
		EM_P_LifeInit ();
		virtual ~EM_P_LifeInit ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_LifeInit);
	typedef Pointer0<EM_P_LifeInit> EM_P_LifeInitPtr;

}

#endif