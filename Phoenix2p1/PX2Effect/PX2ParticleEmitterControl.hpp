/*
*
* 文件名称	：	PX2ParticleEmitterControl.hpp
*
*/

#ifndef PX2PARTICLEEMITTERCONTROL_HPP
#define PX2PARTICLEEMITTERCONTROL_HPP

#include "PX2EffectPre.hpp"
#include "PX2Controller.hpp"
#include "PX2Particle.hpp"
#include "PX2TRecyclingArray.hpp"
#include "PX2EffectModule.hpp"

namespace PX2
{

	/// 粒子发射器控制器
	/**
	* 用户不需要调用AttachController(...)将控制器加入粒子发射器，
	* 粒子发射器创建时候，会默认创建该控制器。
	*/
	class ParticleEmitterController : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(ParticleEmitterController);

	public:
		ParticleEmitterController ();
		virtual ~ParticleEmitterController ();

		enum DrawType
		{
			DT_NORMAL,
			DT_OBJECT,
			DT_MAX_TYPE
		};
		void SetDrawType (DrawType type);
		DrawType GetDrawType ();

		enum PlacerType
		{
			PT_BOX,
			PT_SPHERE,
			PT_COLUMN,
			PT_MAX_TYPE
		};
		void SetPlacerType (PlacerType type);
		PlacerType GetPlacerType ();
		void SetPlacerInLength (float val);
		void SetPlacerOutLength (float val);
		void SetPlacerInWidth (float val);
		void SetPlacerOutWidth (float val);
		void SetPlacerInHeight (float val);
		void SetPlacerOutHeight (float val);
		float GetPlacerInLength ();
		float GetPlacerOutLength ();
		float GetPlacerInWidth ();
		float GetPlacerOutWidth ();
		float GetPlacerInHeight ();
		float GetPlacerOutHeight ();

		void SetMaxNumParticles (int num);
		int GetMaxNumParticles () const;
		TRecyclingArray<Particle>* &GetArray ();

		// Event
		void AddModule (EffectModule *module);
		void RemoveModule (EffectModule *module);
		EffectModule *GetModule (int i);
		int GetNumModules ();
		bool IsHasModule (std::string moduleRttiName);

		void Reset ();

		// 秒
		virtual bool Update (double applicationTime);

public_internal:
		void SetCurEmitRate (float rate);
		float GetCurEmitRate ();

	protected:
		void NewAParticle (double ctrlTime);
		void UpdateEmitterEvents (double ctrlTime);
		void UpdateParticleEvents (Particle &particle, double ctrlTime);

		TRecyclingArray<Particle> *mParticleArray;
		int mMaxNumParticles; // 需要持久化

		int mCreatedParticlesQuantity; //< 总共创建过的粒子数(活着+已死去)
		float mNumNewParticlesExcess;
		float mCurEmitRate;

		PlacerType mPlacerType;
		float mPlacerInLength;
		float mPlacerOutLength;
		float mPlacerInWidth;
		float mPlacerOutWidth;
		float mPlacerInHeight;
		float mPlacerOutHeight;

		typedef std::vector<EffectModulePtr> ModuleList;
		ModuleList mModules;
	};

	PX2_REGISTER_STREAM(ParticleEmitterController);
	typedef Pointer0<ParticleEmitterController> ParticleEmitterControllerPtr;
#include "PX2ParticleEmitterControl.inl"

}

#endif