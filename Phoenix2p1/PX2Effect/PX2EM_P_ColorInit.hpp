/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_P_ColorInit.hpp
*
*/

#ifndef PX2EM_P_COLORINIT_HPP
#define PX2EM_P_COLORINIT_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_ColorInit : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_ColorInit);

	public:
		EM_P_ColorInit ();
		virtual ~EM_P_ColorInit ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_ColorInit);
	typedef Pointer0<EM_P_ColorInit> EM_P_ColorInitPtr;

}

#endif