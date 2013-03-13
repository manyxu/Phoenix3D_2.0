/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_P_AlphaByAge.hpp
*
*/

#ifndef PX2EM_P_ALPHABYAGE_HPP
#define PX2EM_P_ALPHABYAGE_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_AlphaByAge : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_AlphaByAge);

	public:
		EM_P_AlphaByAge ();
		virtual ~EM_P_AlphaByAge ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_AlphaByAge);
	typedef Pointer0<EM_P_AlphaByAge> EM_P_AlphaByAgePtr;

}

#endif