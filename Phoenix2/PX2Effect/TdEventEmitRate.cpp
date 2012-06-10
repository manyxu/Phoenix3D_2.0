/*
*
* ÎÄ¼þÃû³Æ	£º	TdEventEmitRate.cpp
*
*/

#include "TdEventEmitRate.hpp"
#include "TdParticleEmitterControl.hpp"
using namespace Td;

//----------------------------------------------------------------------------
ParticleEvent_EmitRate::ParticleEvent_EmitRate ()
{
	mEmitRateRange.Value0 = 0;
	mEmitRateRange.Value1 = 0;
}
//----------------------------------------------------------------------------
ParticleEvent_EmitRate::~ParticleEvent_EmitRate ()
{

}
//----------------------------------------------------------------------------
void ParticleEvent_EmitRate::UpdateParticleEmitter (ParticleEmitterController
													&ctrl)
{
	int rate = 0;

	if (!IsFade())
	{
		rate = mEmitRateRange.GetRandomInRange();
		ctrl.SetEmitRate((float)rate);
	}

	if (NextEvent)
	{
		ParticleEvent_EmitRate *nextEmitEvent 
			= DynamicCast<ParticleEvent_EmitRate>(NextEvent);

		int nextRate = nextEmitEvent->GetRateRange().GetRandomInRange();

		float timeDelta = nextEmitEvent->GetActivateTime() - GetActivateTime();
		if (timeDelta == 0.0f)
			timeDelta = 1.0f;

		float emitStep = ((float)nextRate - (float)rate)/timeDelta;
		ctrl.SetEmitRateStep(emitStep);
	}
}
//----------------------------------------------------------------------------