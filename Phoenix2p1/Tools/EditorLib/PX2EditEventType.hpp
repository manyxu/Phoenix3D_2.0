/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditEventType.hpp
*
*/

#ifndef PX2EDITEVENTTYPE_HPP
#define PX2EDITEVENTTYPE_HPP

#include "PX2EditorLibPre.hpp"

namespace PX2
{

	PX2_DECLARE_EVENT_BEGIN(EditorEventSpace)
	// EditCommond
	PX2_EVENT(PushUnDo)
	PX2_EVENT(UnDo)
	PX2_EVENT(ReDo)
	PX2_EVENT(NoUnDo)
	PX2_EVENT(NoReDo)
	// Scene
	PX2_EVENT(NewScene)
	PX2_EVENT(LoadedScene)
	PX2_EVENT(SavedScene)
	PX2_EVENT(AddActor)
	PX2_EVENT(RemoveActor)
	// Select
	PX2_EVENT(AddSelectActor)
	PX2_EVENT(RemoveSelectActor)
	PX2_EVENT(ClearSelectActor)
	// Edit
	PX2_EVENT(SetEditMode)
	PX2_EVENT(SetPreView)
	// Actor
	PX2_EVENT(ActorTransformChanged)
	// ActorEdit
	PX2_EVENT(SceneNodeDrag) // data==1 drag; data==0 no drag
	// Terrain
	PX2_EVENT(CreateTerrain)
	PX2_EVENT(SelectTerrainPage)
	PX2_DECLARE_EVENT_END(EditorEventSpace)

}

#endif