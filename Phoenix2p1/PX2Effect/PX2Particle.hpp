/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Particle.hpp
*
*/

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "PX2EffectPre.hpp"
#include "PX2APoint.hpp"
#include "PX2AVector.hpp"

namespace PX2
{

	class ParticleEmitter;

	class Particle
	{
	public:
		Particle ();
		~Particle ();

		float		SizeUInit;
		float		SizeRInit;
		float		SizeDInit;
		float		SizeU;
		float		SizeR;
		float		SizeD;

		float		Life;
		float		Age;

		Float3		ColorInit;
		Float3		Color;
		float		AlphaInit;
		float		Alpha;

		APoint		Pos;
		APoint		PrePos;

		AVector		DVectorInit;
		AVector		UVectorInit;
		AVector		RVectorInit;
		AVector		DVector;
		AVector		UVector;
		AVector		RVector;

		float		RotSpeedInit;
		float		RotSpeed;
		float		RotDegreeInit;
		float		RotDegree;

		float		SpeedInit;
		float		Speed;
		AVector		SpeedDirInit;
		AVector		SpeedDir;

		float		Accelerate;
		AVector		AccelerateDir;

		bool Update (ParticleEmitter *emitter, float elapsedTime);
	};

}

#endif