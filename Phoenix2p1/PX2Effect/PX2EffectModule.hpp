/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectModule.hpp
*
*/

#ifndef PX2EFFECTMODULE_HPP
#define PX2EFFECTMODULE_HPP

#include "PX2EffectPre.hpp"
#include "PX2Object.hpp"
#include "PX2TRange.hpp"
#include "PX2Particle.hpp"
#include "PX2InterpCurve.hpp"

namespace PX2
{

	class ParticleEmitterController;

	class EffectModule : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EffectModule);
		 
	public:
		virtual ~EffectModule ();

		enum ModuleType
		{
			MT_FLOAT,
			MT_FLOAT3,
			MT_MAX_TYPE
		};

		bool IsForInit ();
		ModuleType GetModuleType ();

		void SetRange (bool range);
		bool IsRange ();

		InterpCurveFloat &GetCurveFloatMin();
		InterpCurveFloat &GetCurveFloatMax();
		InterpCurveFloat3 &GetCurveFloat3Min();
		InterpCurveFloat3 &GetCurveFloat3Max();
		int GetNumKeyPoints ();
		float *GetKeyPointInVal (int i);
		float *GetKeyPointOutValFloatMin (int i);
		float *GetKeyPointOutValFloatMax (int i);
		Float3 *GetKeyPointOutValFloat3Min (int i);
		Float3 *GetKeyPointOutValFloat3Max (int i);
		float *GetKeyPointArriveTangentFloatMin (int i);
		float *GetKeyPointArriveTangentFloatMax (int i);
		float *GetKeyPointLeaveTangentFloatMin (int i);
		float *GetKeyPointLeaveTangentFloatMax (int i);
		Float3 *GetKeyPointArriveTangentFloat3Min (int i);
		Float3 *GetKeyPointArriveTangentFloat3Max (int i);
		Float3 *GetKeyPointLeaveTangentFloat3Min (int i);
		Float3 *GetKeyPointLeaveTangentFloat3Max (int i);

		virtual void UpdateParticleEmitter (ParticleEmitterController &ctrl, 
			double ctrlTime);
		virtual void UpdateParticle (Particle &particle, double ctrlTime);

public_internal:
		virtual void OnRemove (ParticleEmitterController &ctrl);

	protected:
		EffectModule (ModuleType type=MT_MAX_TYPE);

		bool mIsForInit;
		bool mIsRange;
		ModuleType mModuleType;
		InterpCurveFloat mCurveFloatMin;
		InterpCurveFloat mCurveFloatMax;
		InterpCurveFloat3 mCurveFloat3Min;
		InterpCurveFloat3 mCurveFloat3Max;
	};

	PX2_REGISTER_STREAM(EffectModule);
	typedef Pointer0<EffectModule> EffectModulePtr;
#include "PX2EffectModule.inl"

}

#endif