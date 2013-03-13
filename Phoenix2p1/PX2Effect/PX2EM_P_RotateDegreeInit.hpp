/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_P_RotateDegreeInit.hpp
*
*/

#ifndef PX2EM_P_ROTATEDEGREEINIT_HPP
#define PX2EM_P_ROTATEDEGREEINIT_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_RotateDegreeInit : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_RotateDegreeInit);

	public:
		EM_P_RotateDegreeInit ();
		virtual ~EM_P_RotateDegreeInit ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_RotateDegreeInit);
	typedef Pointer0<EM_P_RotateDegreeInit> EM_P_RotateDegreeInitPtr;

}


#endif