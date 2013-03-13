/*
*
* 文件名称	：	PX2ParticleEmitter.hpp
*
*/

#ifndef PX2PARTICLEEMITTER_HPP
#define PX2PARTICLEEMITTER_HPP

#include "PX2EffectPre.hpp"
#include "PX2TriMesh.hpp"
#include "PX2Texture2D.hpp"
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

		void SetEffectPlayType (EffectPlayType type);
		EffectPlayType GetEffectPlayType ();
		
		// 设置生命时间，如果EffectPlayType==EPT_FOREVER，生命时间无效
		void SetEffectPlayLife (float life);
		float GetEffectPlayLife ();

		void Play ();
		bool IsPlaying ();
		void Stop ();

		void SetFixedBound (bool fixed);
		bool IsFixedBound ();
		void SetFixedBoundCenter (const APoint &center);
		APoint GetFixedBoundCenter ();
		void SetFixedBoundRadius (float radius);
		float GetFixedBoundRadius ();

		void SetLocal (bool l);
		bool IsLocal ();

		enum FaceType
		{
			FT_CAMERA,
			FT_SPEEDDIR,
			FT_FREE,
			FT_MAX_TYPE
		};
		void SetFaceType (FaceType type);
		FaceType GetFaceType ();

		enum RotateAxisType
		{
			RAT_D,
			RAT_U,
			RAT_R,
			RAT_MAX_TYPE
		};
		void SetRotateAxisType (RotateAxisType type);
		RotateAxisType GetRotateAxisType ();

		// 0 
		// BlendEnabled = false
		// CompareEnabled = false
		//
		// 1
		// BlendEnabled = false
		// CompareEnabled = true
		// Reference = 0.33f
		// Compare = CM_GEQUAL
		//
		// 2
		// BlendEnabled = true
		// SrcBlend = SBM_SRC_ALPHA
		// DstBlend = DBM_ONE_MINUS_SRC_ALPHA
		// CompareEnabled = true
		// Reference = 0.0f
		// Compare = CM_GREATER
		//
		// 3
		// BlendEnabled = true
		// SrcBlend = SBM_ONE
		// DstBlend = DBM_ONE_MINUS_SRC_ALPHA
		// CompareEnabled = false
		// 
		// 4
		// BlendEnabled = true
		// SrcBlend = SBM_ONE
		// DestBlend = DBM_ONE
		// CompareEnabled = false
		//
		// 5
		// BlendEnabled = true
		// SrcBlend = SBM_DST_COLOR
		// DestBlend = DBM_ZERO
		// CompareEnabled = false
		//
		// 6
		// BlendEnabled = true
		// SrcBlend = SBM_DST_COLOR
		// DestBlend = DBM_SRC_COLOR
		// CompareEnabled = false
		void SetBlendMode (int mode);
		int GetBlendMode ();

		void SetTexture (Texture2D *texture);
		void SetTexture (std::string filename);
		Texture2D *GetTexture ();

		ParticleEmitterController *GetParticleEmitterControl ();

public_internal:
		void GenerateParticles ();

	protected:
		Pointer0<ParticleEmitterController> mEmitterControl;
		EffectPlayType mEffectPlayType;
		float mEffectPlayLife;
		bool mIsPlaying;
		bool mIsFixedBound;
		APoint mFixedCenter;
		float mFixedBoundRadius;
		bool mIsLocal;
		FaceType mFaceType;
		RotateAxisType mRotateAxisType;

		EffectMaterialPtr mMaterial;
		MaterialInstancePtr mMaterialInstance;
		int mBlendMode;
		Texture2DPtr mTexture;
	};

	PX2_REGISTER_STREAM(ParticleEmitter);
	typedef Pointer0<ParticleEmitter> ParticleEmitterPtr;
#include "PX2ParticleEmitter.inl"

}

#endif