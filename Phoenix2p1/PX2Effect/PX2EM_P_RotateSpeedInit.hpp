/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_P_RotateSpeedInit.hpp
*
*/

#ifndef PX2EM_P_ROTATESPEEDINIT_HPP
#define PX2EM_P_ROTATESPEEDINIT_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_RotateSpeedInit : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_RotateSpeedInit);

	public:
		EM_P_RotateSpeedInit ();
		virtual ~EM_P_RotateSpeedInit ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_RotateSpeedInit);
	typedef Pointer0<EM_P_RotateSpeedInit> EM_P_RotateSpeedInitPtr;

}

#endif