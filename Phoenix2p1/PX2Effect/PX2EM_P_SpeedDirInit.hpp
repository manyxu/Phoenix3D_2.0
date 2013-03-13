/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_E_SpeedDirInit.hpp
*
*/

#ifndef PX2EM_P_SPEEDDIRINIT_HPP
#define PX2EM_P_SPEEDDIRINIT_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_SpeedDirInit : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_SpeedDirInit);

	public:
		EM_P_SpeedDirInit ();
		virtual ~EM_P_SpeedDirInit ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_SpeedDirInit);
	typedef Pointer0<EM_P_SpeedDirInit> EM_P_SpeedDirInitPtr;

}

#endif