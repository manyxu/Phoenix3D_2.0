/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_P_Accelerate.hpp
*
*/

#ifndef PX2EM_P_ACCELERATE_HPP
#define PX2EM_P_ACCELERATE_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_Accelerate : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_Accelerate);

	public:
		EM_P_Accelerate ();
		virtual ~EM_P_Accelerate ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_Accelerate);
	typedef Pointer0<EM_P_Accelerate> EM_P_AcceleratePtr;

}

#endif