/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_P_AlphaInit.hpp
*
*/

#ifndef PX2EM_P_ALPHAINIT_HPP
#define PX2EM_P_ALPHAINIT_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_AlphaInit : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_AlphaInit);

	public:
		EM_P_AlphaInit ();
		virtual ~EM_P_AlphaInit ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_AlphaInit);
	typedef Pointer0<EM_P_AlphaInit> EM_P_AlphaInitPtr;

}

#endif