/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EditEventType.hpp
*
* 版本		:	1.0 (2011/05/04)
*
* 作者		：	more
*
*/

#ifndef PX2EDITEVENTTYPE_HPP
#define PX2EDITEVENTTYPE_HPP

#include "PX2EditorLibPrerequisites.hpp"

namespace PX2
{

	/// 编辑器事件空间
	PX2_DECLARE_EVENT_BEGIN(EditorEventSpace)
	PX2_EVENT(NewScene)
	PX2_EVENT(LoadedScene)
	PX2_EVENT(SavedScene)
	PX2_EVENT(CreateTerrainAndAddToScene)
	PX2_EVENT(CreateModelActorAndAddToScene)
	PX2_EVENT(CreateLightActor)
	PX2_EVENT(CreateSoundActor)
	PX2_EVENT(CreateEditEffectNode)
	PX2_EVENT(UpdateEffectNode)
	PX2_EVENT(SelectEffect)
	PX2_EVENT(UpdateEffect)
	PX2_EVENT(AddEffectEvent)
	PX2_EVENT(SelectEffectEvent)
	PX2_EVENT(AddActor)
	PX2_EVENT(RemoveActor)
	PX2_EVENT(SetEditMode)
	PX2_EVENT(AddSelectActor)
	PX2_EVENT(RemoveSelectActor)
	PX2_EVENT(ClearSelectActor)
	PX2_EVENT(ActorTransformChanged)
	PX2_EVENT(PushUnDo)
	PX2_EVENT(UnDo)
	PX2_EVENT(ReDo)
	PX2_EVENT(NoUnDo)
	PX2_EVENT(NoReDo)
	PX2_EVENT(ObjectNamePropertyChanged)
	PX2_EVENT(TextureConvert)
	PX2_EVENT(SetPreViewObject)
	PX2_EVENT(SelectTerrainPage)
	PX2_EVENT(SetTerrainTexturePreView)
	PX2_DECLARE_EVENT_END(EditorEventSpace)

}

#endif