/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_P_SpeedInit.hpp
*
*/

#ifndef PX2EM_P_SPEEDINIT_HPP
#define PX2EM_P_SPEEDINIT_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_SpeedInit : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_SpeedInit);

	public:
		EM_P_SpeedInit ();
		virtual ~EM_P_SpeedInit ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_SpeedInit);
	typedef Pointer0<EM_P_SpeedInit> EM_P_SpeedInitPtr;

}

#endif