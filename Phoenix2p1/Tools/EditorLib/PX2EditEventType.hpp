/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditEventType.hpp
*
*/

#ifndef PX2EDITEVENTTYPE_HPP
#define PX2EDITEVENTTYPE_HPP

#include "PX2EditorLibPre.hpp"
#include "PX2EventSpace.hpp"
#include "PX2Event.hpp"

namespace PX2
{

	PX2_DECLARE_EVENT_BEGIN(EditorEventSpace)
	// EditCommond
	PX2_EVENT(PushUnDo)
	PX2_EVENT(UnDo)
	PX2_EVENT(ReDo)
	PX2_EVENT(NoUnDo)
	PX2_EVENT(NoReDo)
	// Project
	PX2_EVENT(NewProject)
	PX2_EVENT(LoadedProject)
	PX2_EVENT(SavedProject)
	PX2_EVENT(ClosedProject)
	// Scene
	PX2_EVENT(NewScene)
	PX2_EVENT(LoadedScene)
	PX2_EVENT(SavedScene)
	PX2_EVENT(CloseScene)
	PX2_EVENT(AddActor)
	PX2_EVENT(RemoveActor)
	// UI
	PX2_EVENT(AddUI)
	PX2_EVENT(RemoveUI)
	// Select
	PX2_EVENT(AddSelectObject)
	PX2_EVENT(RemoveSelectObject)
	PX2_EVENT(ClearSelectObject)
	// Edit
	PX2_EVENT(SetEditMode)
	PX2_EVENT(SetPreView)
	// Actor
	PX2_EVENT(ObjectTransformChanged)
	PX2_EVENT(ObjectNameChanged)
	// ActorEdit
	PX2_EVENT(SceneNodeDrag) // data==1 drag; data==0 no drag
	// Terrain
	PX2_EVENT(SelectTerrainPage)
	// Effect
	PX2_EVENT(CurveChangedByGrid)
	PX2_EVENT(CurveChangedByEditor)
	// ProjSceneUI
	PX2_EVENT(SelectPSU)
	PX2_EVENT(UICameraPercentChanged)
	PX2_DECLARE_EVENT_END(EditorEventSpace)

}

#endif