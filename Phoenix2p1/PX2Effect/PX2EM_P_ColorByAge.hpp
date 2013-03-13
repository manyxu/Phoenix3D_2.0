/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_P_Color.hpp
*
*/

#ifndef PX2EM_P_COLORBYAGE_HPP
#define PX2EM_P_COLORBYAGE_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_ColorByAge : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_ColorByAge);

	public:
		EM_P_ColorByAge ();
		virtual ~EM_P_ColorByAge ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_ColorByAge);
	typedef Pointer0<EM_P_ColorByAge> EM_P_ColorByAgePtr;

}

#endif