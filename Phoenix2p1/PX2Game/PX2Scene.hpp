/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Scene.hpp
*
*/

#ifndef PX2SCENE_HPP
#define PX2SCENE_HPP

#include "PX2GamePre.hpp"
#include "PX2Node.hpp"
#include "PX2Actor.hpp"
#include "PX2TerrainActor.hpp"
#include "PX2CameraActor.hpp"
#include "PX2AmbientRegionActor.hpp"

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

		void Update (double appSeconds, double elapsedSeconds);

		void SetSceneID (int id);
		int GetSceneID ();

		PX2::Node *GetSceneNode ();

		void AddActor (Actor *actor);
		bool RemoveActor (Actor *actor);
		ActorPtr SetActor (int i, Actor* actor);
		bool IsActorIn (Actor *actor);
		int GetActorQuantity ();
		Actor *GetActor (int i);
		Actor *GetActor (PX2::Movable *object);

		int GetARActorNum ();
		AmbientRegionActor *GetARActor (int i);

		TerrainActor *GetTerrainActor ();

		PX2::Light *GetDefaultLight ();
		CameraActor *GetDefaultCameraActor ();
		AmbientRegionActor *GetDefaultARActor ();

	protected:
		int mSceneID;
		NodePtr mSceneNode;
		std::vector<ActorPtr> mActors;
		TerrainActorPtr mTerrainActor;

		float mAmbientBlend;
		PX2::AmbientRigionActorPtr mTwoAmbientRigion[2];
		std::vector<AmbientRigionActorPtr> mARActors;

		PX2::LightPtr mDefaultLight;
		CameraActorPtr mDefaultCameraActor;
		PX2::AmbientRigionActorPtr mDefaultARActor;
	};

	PX2_REGISTER_STREAM(Scene);
	typedef Pointer0<Scene> ScenePtr;

#include "PX2Scene.inl"

}

#endif