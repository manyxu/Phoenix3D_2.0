/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_P_AccelerateDir.hpp
*
*/

#ifndef PX2EM_P_ACCELERATEDIR_HPP
#define PX2EM_P_ACCELERATEDIR_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_AccelerateDir : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_AccelerateDir);

	public:
		EM_P_AccelerateDir ();
		virtual ~EM_P_AccelerateDir ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_AccelerateDir);
	typedef Pointer0<EM_P_AccelerateDir> EM_P_AccelerateDirPtr;

}

#endif