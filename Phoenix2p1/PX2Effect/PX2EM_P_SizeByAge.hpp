/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_P_SizeByAge.hpp
*
*/

#ifndef PX2EM_P_SIZEBYAGE_HPP
#define PX2EM_P_SIZEBYAGE_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_SizeByAge : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_SizeByAge);

	public:
		EM_P_SizeByAge ();
		virtual ~EM_P_SizeByAge ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_SizeByAge);
	typedef Pointer0<EM_P_SizeByAge> EM_P_SizeByAgePtr;

}

#endif