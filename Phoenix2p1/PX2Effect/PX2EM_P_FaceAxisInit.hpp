/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EM_P_FaceAxisInit.hpp
*
*/

#ifndef PX2EM_P_FACEAXISINIT_HPP
#define PX2EM_P_FACEAXISINIT_HPP

#include "PX2EffectModule.hpp"

namespace PX2
{

	class EM_P_FaceAxisInit : public EffectModule
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EM_P_FaceAxisInit);

	public:
		EM_P_FaceAxisInit ();
		virtual ~EM_P_FaceAxisInit ();

		virtual void UpdateParticle (Particle &particle, double ctrlTime);
	};

	PX2_REGISTER_STREAM(EM_P_FaceAxisInit);
	typedef Pointer0<EM_P_FaceAxisInit> EM_P_FaceAxisInitPtr;

}

#endif