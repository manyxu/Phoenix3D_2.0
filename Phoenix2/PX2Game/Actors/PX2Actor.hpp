/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Actor.hpp
*
* 版本		:	1.0 (2011/02/25)
*
* 作者		：	more
*
*/

#ifndef PX2ACTOR_HPP
#define PX2ACTOR_HPP

#include "PX2GamePrerequisites.hpp"
#include "PX2Netable.hpp"

namespace PX2
{

	class Scene;

	class Actor : public Netable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Actor);

	public:
		Actor ();
		~Actor ();

		// 场景
		PX2::Scene *GetScene ();

		// 方位	
		virtual void SetScale (APoint &scale);
		virtual void SetRotation (APoint &rolate);
		virtual void SetPosition (APoint &position);
		APoint GetScale ();
		APoint GetRotation ();
		APoint GetPosition ();

		// Steering
		AVector GetVelocity () { return mVelocity; }
		double GetMass () { return mMass; }
		double GetMaxSpeed () { return mMaxSpeed; }
		double GetMaxForce () { return mMaxForce; }
		double GetMaxTurnRate () { return mMaxTurnRate; }

		void SetVisible (bool visible);
		bool IsVisible ();

		void SetTransparent (float alpha);
		float GetTransparent ();

		// 模型
		void SetMovable (Movable *movable);
		Movable *GetMovable ();

		// 替身
		/*
		* 用于编辑器中
		*/
		void SetHelpMovable (Movable *movable);
		Movable *GetHelpMovable ();
		void ShowHelpMovable (bool show);
		bool IsHelpMovableShow ();

		// 物理
		void SetDoPhysicsSimulateion (bool simulate);
		bool IsDoPhysicsSimulateion ();
		void SetPhysicsStatic (bool stat);
		bool IsPhysicsStatic ();
		virtual void EnablePhysics (bool enable);
		bool IsPhysicsEnabled ();
		TdBt::RigidBody *GetRigidBody ();

		//enum PhysicsEnabledMode
		//{
		//	PEM_MODELBUILDIN, // 内建的模型，模型内部名称标记为Physics的节点
		//	PEM_MODEL, // 模型自身
		//	PEM_ATTACH, // 工具中邦迪上去的节点
		//	PEM_MAX_MODE
		//};
		//void SetPhysicsMode (PhysicsEnabledMode mode);
		//PhysicsEnabledMode GetPhysicsEnabledMode ();

public_internal:
		void SetScene (Scene *scene);

	protected:
		void _EnablePhysics ();
		void _DisablePhysics ();

		/// 使用一个常规指针指向被控制的对象。避免循环依赖
		Scene *mScene;

		// trans
		APoint mScale;
		APoint mRotation;
		APoint mPosition;
		APoint mOriginScale; // 做完物理仿真后还原
		APoint mOriginRotation;
		APoint mOriginPosition;

		// steering
		AVector mVelocity;
		double mMass;
		double mMaxSpeed;
		double mMaxForce;
		double mMaxTurnRate;

		bool mVisible;
		float mTransAlpha;

		MovablePtr mMovable;

		// 替代体
		MovablePtr mHelpMovable;
		bool mShowHelpMovable;

		// Physics
		bool mDoPhysicsSimulateion;
		bool mPhysicsStatic;
		bool mPhysicsEnabled;
		TdBt::RigidBodyPtr mRigidBody;
	};

	PX2_REGISTER_STREAM(Actor);
	typedef Pointer0<Actor> ActorPtr;
#include "PX2Actor.inl"
	
}

#endif