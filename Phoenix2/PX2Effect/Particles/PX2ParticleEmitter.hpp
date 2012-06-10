/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Particle.hpp
*
* 版本		:	1.0 (2011/02/23)
*
* 作者		：	more
*
*/

#ifndef PX2PARTICLEEMITTER_HPP
#define PX2PARTICLEEMITTER_HPP

#include "PX2EffectPrerequisites.hpp"
#include "PX2EffectMaterial.hpp"

namespace PX2
{

	class ParticleEmitterController;

	class ParticleEmitter : public TriMesh
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(ParticleEmitter);

	public:
		ParticleEmitter ();
		virtual ~ParticleEmitter ();

		void SetTexture (Texture2D *texture);
		void SetTexture (std::string filename);
		Texture2D *GetTexture ();

		ParticleEmitterController *GetParticleEmitterControl ();

public_internal:
		void GenerateParticles (const Camera* camera);

	protected:
		Pointer0<ParticleEmitterController> mEmitterControl;
		EffectMaterialPtr mMaterial;
		MaterialInstancePtr mMaterialInstance;
		Texture2DPtr mTexture;
	};

	PX2_REGISTER_STREAM(ParticleEmitter);
	typedef Pointer0<ParticleEmitter> ParticleEmitterPtr;
#include "PX2ParticleEmitter.inl"

}

#endif