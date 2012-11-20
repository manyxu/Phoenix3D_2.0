/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ActorSelection.hpp
*
*/

#ifndef PX2ACTORSELECTION_HPP
#define PX2ACTORSELECTION_HPP

#include "PX2EditorLibPre.hpp"

namespace PX2Editor
{

	class ActorSelection
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