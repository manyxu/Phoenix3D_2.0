/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ActorTree.hpp
*
* 版本		:	1.0 (2011/05/04)
*
* 作者		：	more
*
*/

#ifndef PX2ACTORTREE_HPP
#define PX2ACTORTREE_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class ActorTreeItem;

	class ActorTree : public wxTreeCtrl, public PX2::EventHandler
	{
	public:
		ActorTree (wxWindow *parent);
		~ActorTree ();

		// 当场景改变后刷新
		void RefleshScene (); 

		ActorTreeItem *AddActor (wxTreeItemId parentID, PX2::Actor *actor);
		void RemoveActor (PX2::Actor *actor);
		void RemoveAllActors ();
		ActorTreeItem *GetItem (wxTreeItemId id);
		ActorTreeItem *GetItem (PX2::Actor *actor);

		void OnItemActivated (wxTreeEvent& event);
		void OnSelChanged (wxTreeEvent& event);
		void OnSelChanging (wxTreeEvent& event);

		// 事件
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()
		
		wxTreeItemId mRootItemId;
		wxTreeItemId mSkyItemId; // 天空
		wxTreeItemId mTerrainItemId; // 地形
		wxTreeItemId mWaterItemId; // 水面
		wxTreeItemId mObjectsItemId; // 物件
		wxTreeItemId mLightsItemId; // 灯光
		std::vector<ActorTreeItem*> mItems;

		wxTreeItemId mEnvItemId;
	};
}

#endif