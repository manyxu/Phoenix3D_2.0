/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ActorSelection.hpp
*
* 版本		:	1.0 (2011/06/06)
*
* 作者		：	more
*
*/

#ifndef PX2ACTORSELECTION_HPP
#define PX2ACTORSELECTION_HPP

#include "PX2EditorLibPrerequisites.hpp"

namespace PX2Editor
{

	class ActorSelection : public PX2::Singleton<ActorSelection>
	{
	public:
		ActorSelection ();
		~ActorSelection ();

		void AddActor (PX2::Actor *actor);
		void RemoveActor (PX2::Actor *actor);
		PX2::Actor *GetActor (int i);
		int GetActorQuantity ();
		bool IsActorIn (PX2::Actor *actor);
		void Clear ();

		void Translate (PX2::AVector vec);
		void AddRolate (PX2::AVector vec);
		void AddScale (PX2::AVector vec);

	private:
		std::vector<PX2::ActorPtr> mActors;
	};
}

#endif