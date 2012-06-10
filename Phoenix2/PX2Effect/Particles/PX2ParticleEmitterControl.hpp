/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ParticleEmitterControl.hpp
*
* 版本		:	1.0 (2011/12/19)
*
* 作者		：	more
*
*/

#ifndef PX2PARTICLEEMITTERCONTROL_HPP
#define PX2PARTICLEEMITTERCONTROL_HPP

#include "PX2GraphicsPrerequisites.hpp"
#include "PX2Controller.hpp"
#include "PX2TRecyclingArray.hpp"
#include "PX2TRange.hpp"
#include "PX2Particle.hpp"
#include "PX2EffectEvent.hpp"

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

		enum EmitterType
		{
			ET_PLANE = 0,
			ET_SPHERE,
			ET_CIRCLE,
			ET_COLUMN,
			ET_MAX_TYPE
		};

		void SetEmitterType (EmitterType type);
		EmitterType GetEmitterType ();

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
			PT_PLANE = 0,
			PT_SPHERE,
			PT_SPHEREFACE,
			PT_CIRCLE,
			PT_COLUMNSSPREAD,
			PT_COLUMNUP
		};
		void SetPlacerType (PlacerType type);
		PlacerType GetPlacerType ();

		enum AxisType
		{
			AT_LOCAL,
			AT_GLOBAL,
			AT_MAX_TYPE
		};
		void SetAxisType (AxisType type);
		AxisType GetAxisType ();

		void SetMaxQuantity (int quantity);
		int GetMaxQuantity () const;
		int GetActivateParticleQuantity ();
		TRecyclingArray<Particle>* &GetArray ();

		// Event
		int AttachEffectEvent (EffectEvent *event);
		int DetachEffectEvent (EffectEvent *event);
		EffectEvent *DetachEffectEventAt (int i);
		EffectEvent *SetEffectEvent (int i, EffectEvent *event);
		EffectEvent *GetEffectEvent (int i);
		int GetNumEvents ();

		void Reset ();

		void ConfigeAllEvents ();

		// 毫秒
		virtual bool Update (double applicationTime);

public_internal:
		void SetEmitRate (float rate);
		float GetEmitRate ();
		void SetEmitRateStep (float step);
		float GetEmitRateStep ();

	protected:
		void SortEvents ();
		void CreateEventList ();
		void NailDowmRandTime (); //< 把所有事件的TimeRange变为ActivateTime
		void NewAParticle ();
		void UpdateEmitterEvents ();
		void UpdateParticleEvents (Particle &particle);

		TRecyclingArray<Particle> *mParticleArray;
		int mMaxQuantity; // 需要持久化

		int mCreatedParticlesQuantity; //< 总共创建过的粒子数(活着+已死去)
		float mNumNewParticlesExcess;
		double mLastApplicationTime;
		bool mbFirstFrame; //< 第一帧不发射粒子
		float mEmitRate;
		float mEmitRateStep;

		typedef std::vector<EffectEventPtr> EventList;
		typedef std::vector<EffectEventPtr>::iterator EventIt;
		EventList mEvents;
	};

	PX2_REGISTER_STREAM(ParticleEmitterController);
	typedef Pointer0<ParticleEmitterController> ParticleEmitterControllerPtr;
#include "PX2ParticleEmitterControl.inl"

}

#endif