/*
*
* 文件名称	：	PX2Scene.hpp
*
*/

#ifndef PX2SCENE_HPP
#define PX2SCENE_HPP

#include "PX2GamePre.hpp"
#include "PX2Node.hpp"
#include "PX2Actor.hpp"
#include "PX2CameraActor.hpp"

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

		void SetSceneID (int id);
		int GetSceneID ();

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

		CameraActor *GetDefaultCameraActor ();

	protected:
		void Update ();

		int mSceneID;
		NodePtr mSceneNode;
		std::vector<ActorPtr> mActors;
		CameraActorPtr mDefaultCameraActor;
	};

	PX2_REGISTER_STREAM(Scene);
	typedef Pointer0<Scene> ScenePtr;

#include "PX2Scene.inl"

}

#endif