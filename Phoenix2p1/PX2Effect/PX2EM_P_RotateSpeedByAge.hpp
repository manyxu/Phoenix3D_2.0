/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_P_RotateSpeedByLife.hpp
*
*/

#ifndef PX2EM_P_ROTATESPEEDBYAGE_HPP
#define PX2EM_P_ROTATESPEEDBYAGE_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_RotateSpeedByAge : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_RotateSpeedByAge);

	public:
		EM_P_RotateSpeedByAge ();
		virtual ~EM_P_RotateSpeedByAge ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_RotateSpeedByAge);
	typedef Pointer0<EM_P_RotateSpeedByAge> EM_P_RotateSpeedByAgePtr;

}

#endif