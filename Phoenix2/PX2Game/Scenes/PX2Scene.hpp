/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Scene.hpp
*
* 版本		:	1.0 (2011/04/02)
*
* 作者		：	more
*
*/

#ifndef PX2SCENE_HPP
#define PX2SCENE_HPP

#include "PX2GamePrerequisites.hpp"
#include "PX2Node.hpp"
#include "PX2Actor.hpp"
#include "PX2LODTerrainActor.hpp"
#include "PX2RawTerrainActor.hpp"
#include "PX2AmbientRegionActor.hpp"
#include "PX2LightActor.hpp"

namespace PX2
{

	class Scene : public Netable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Scene);

	public:
		Scene ();
		virtual ~Scene ();

		// 物理初始化，默认构造函数激活
		void InitPhysics (const PX2::AxisAlignedBox3f bounds, 
			const PX2::Vector3f gravity);
		void TermPhysics ();
		void EnablePhysicsSimulation (bool play);
		bool IsPhysicsSimulateion ();

		TdBt::DynamicWorld *GetDynamicWorld ();
		TdBt::DebugDrawer *GetDebugDrawer ();

		void SetSceneID (int id);
		int GetSceneID ();

		virtual void DoUpdate ();

		// 场景节点获取
		PX2::Node *GetSceneNode ();

		// 角色
		void AddActor (Actor *actor);
		bool RemoveActor (Actor *actor);
		ActorPtr SetActor (int i, Actor* actor);
		bool IsActorIn (Actor *actor);
		int GetActorQuantity ();
		Actor *GetActor (int i);
		Actor *GetActor (PX2::Movable *object);

		// 缺省光源
		PX2::Light *GetDefaultLight ();

		// 环境角色
		AmbientRegionActor *GetDefaultARActor ();
		int GetARActorNum ();
		AmbientRegionActor *GetARActor (int i);

		// 地形Actor
		PX2::LODTerrainActor *GetLODTerrainActor () { return mLODTerrainActor; }
		PX2::RawTerrainActor *GetRawTerrainActor () { return mRawTerrainActor; }

	protected:
		void Update ();

		CameraPtr mCamera;

		int mSceneID;
		bool mIsFirstFrame;
		double mLastFrameTime;
		bool mPlayPhysicsSimulation;

		NodePtr mSceneNode;
		PX2::LODTerrainActorPtr mLODTerrainActor;
		PX2::RawTerrainActorPtr mRawTerrainActor;

		// Ambient
		PX2::AmbientRigionActorPtr mDefaultARActor;
		PX2::AmbientRigionActorPtr mTwoAmbientRigion[2];
		float mAmbientBlend;
		std::vector<AmbientRigionActorPtr> mARActors;

		// Light
		PX2::LightPtr mDefaultLight;

		// Actors
		std::vector<ActorPtr> mActors;

		// Physics
		TdBt::DynamicWorldPtr mBulletDynamicWorld;
		TdBt::DebugDrawerPtr mDebugDrawer;
	};

	PX2_REGISTER_STREAM(Scene);
	typedef Pointer0<Scene> ScenePtr;

#include "PX2Scene.inl"

}

#endif