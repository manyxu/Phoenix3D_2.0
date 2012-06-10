/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2TerrainActorPropertyGrid.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2TERRAINACTORPROPERTYGRID_HPP
#define PX2TERRAINACTORPROPERTYGRID_HPP

#include "PX2ObjectPropertyGrid.hpp"
#include "PX2RawTerrainActor.hpp"

namespace PX2Editor
{

	class TerrainActorPropertyGrid : public ObjectPropertyGrid
	{
	public:
		TerrainActorPropertyGrid (wxWindow *parent);
		~TerrainActorPropertyGrid ();

		DECLARE_DYNAMIC_CLASS(TerrainActorPropertyGrid)

		virtual void OnSetObject(PX2::Object *object);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()
		
		TerrainActorPropertyGrid ();
		void RefreshOnRawTerrainActor ();

		bool mDoPhysicsSimulateion;
	};

}

#endif