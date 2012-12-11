/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainActor.hpp
*
*/

#ifndef PX2TERRAINACTOR_HPP
#define PX2TERRAINACTOR_HPP

#include "PX2Actor.hpp"
#include "PX2Terrain.hpp"

namespace PX2
{

	class TerrainActor : public Actor
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(TerrainActor);

	public:
		TerrainActor ();
		virtual ~TerrainActor ();

		void SetTerrain (Terrain *terrain);
		Terrain *GetTerrain ();

		virtual void DoEnter ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

	protected:
		TerrainPtr mTerrain;
	};

	PX2_REGISTER_STREAM(TerrainActor);
	typedef Pointer0<TerrainActor> TerrainActorPtr;
#include "PX2TerrainActor.inl"

}

#endif