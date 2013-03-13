/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectModuleEmitterRate.hpp
*
*/

#ifndef PX2EM_E_EMITRATE_HPP
#define PX2EM_E_EMITRATE_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_E_EmitRate : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_E_EmitRate);

	public:
		EM_E_EmitRate ();
		virtual ~EM_E_EmitRate ();

		virtual void UpdateParticleEmitter (ParticleEmitterController &ctrl,
			double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_E_EmitRate);
	typedef Pointer0<EM_E_EmitRate> EM_E_EmitRatePtr;

}

#endif