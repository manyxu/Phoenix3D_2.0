/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainActorPropertyGrid.hpp
*
*/

#ifndef PX2TERRAINACTORPROPERTYGRID_HPP
#define PX2TERRAINACTORPROPERTYGRID_HPP

#include "PX2ObjectPropertyGrid.hpp"

namespace PX2Editor
{
	
	class TerrainActorPropertyGrid : public ObjectPropertyGrid
	{
	public:
		TerrainActorPropertyGrid (wxWindow *parent);
		~TerrainActorPropertyGrid ();

		DECLARE_DYNAMIC_CLASS(TerrainActorPropertyGrid)

		void EnableTerrainEdit (bool able);
		virtual void OnSetObject(PX2::Object *object);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()

		TerrainActorPropertyGrid ();
		void RefreshOnActor ();

		std::string mActorType;
		bool mEnableTerrainEdit;
		bool mShowPageGridLine;
		float mLODPixelTolerance;
		bool mIsCloseAssumption;
	};

}

#endif