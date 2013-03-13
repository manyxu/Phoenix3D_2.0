/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectActor.hpp
*
*/

#ifndef PX2EFFECTACTOR_HPP
#define PX2EFFECTACTOR_HPP

#include "PX2Actor.hpp"
#include "PX2EffectNode.hpp"

namespace PX2
{

	class EffectActor : public Actor
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EffectActor);

	public:
		EffectActor (EffectNode *effect=0);
		virtual ~EffectActor ();

		void SetEffect (EffectNode *effect);
		EffectNode *GetEffect ();

		virtual void DoEnter ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

	protected:
		EffectNodePtr mEffect;
	};

	PX2_REGISTER_STREAM(EffectActor);
	typedef Pointer0<EffectActor> EffectActorPtr;
#include "PX2EffectActor.inl"

}

#endif