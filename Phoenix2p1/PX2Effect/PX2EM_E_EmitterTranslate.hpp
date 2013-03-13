/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_E_EmitterTranslate.hpp
*
*/

#ifndef PX2EM_E_EMITTERTRANSLATE_HPP
#define PX2EM_E_EMITTERTRANSLATE_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_E_EmitterTranslate : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_E_EmitterTranslate);

	public:
		EM_E_EmitterTranslate ();
		virtual ~EM_E_EmitterTranslate ();

		virtual void UpdateParticleEmitter (ParticleEmitterController &ctrl,
			double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_E_EmitterTranslate);
	typedef Pointer0<EM_E_EmitterTranslate> EM_E_EmitterTranslatePtr;

}

#endif