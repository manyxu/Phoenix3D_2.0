/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_E_SizeInit.hpp
*
*/

#ifndef PX2EM_P_SIZEINIT_HPP
#define PX2EM_P_SIZEINIT_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_SizeInit : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_SizeInit);

	public:
		EM_P_SizeInit ();
		virtual ~EM_P_SizeInit ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_SizeInit);
	typedef Pointer0<EM_P_SizeInit> EM_P_SizeInitPtr;

}

#endif