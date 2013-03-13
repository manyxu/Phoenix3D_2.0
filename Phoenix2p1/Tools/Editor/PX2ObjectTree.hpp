/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ObjectTree.hpp
*
*/

#ifndef PX2OBJECTTREE_HPP
#define PX2OBJECTTREE_HPP

#include "PX2EditorPre.hpp"
#include "PX2Actor.hpp"

namespace PX2Editor
{

	class ObjectTreeItem;

	class ObjectTree : public wxTreeCtrl, public PX2::EventHandler
	{
	public:
		ObjectTree (wxWindow *parent);
		virtual ~ObjectTree ();

		ObjectTreeItem *GetItem (wxTreeItemId id);
		ObjectTreeItem *GetItem (PX2::Object *obj);

		void OnItemActivated (wxTreeEvent& event);
		void OnSelChanged (wxTreeEvent& event);
		void OnSelChanging (wxTreeEvent& event);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()
		void RefreshProject ();
		void RefreshScene ();
		void RefreshUI ();
		void ClearProject ();
		void ClearScene();
		void ClearUI ();
		void AddActor (PX2::Actor *actor);
		void RemoveActor (PX2::Actor *actor);

		wxImageList *mImageList;

		wxTreeItemId mRootItemId;

		wxTreeItemId mSceneItemId;
		wxTreeItemId mSkyItemId;
		wxTreeItemId mTerrainItemId;
		wxTreeItemId mRoadItemId;
		wxTreeItemId mWaterItemId;
		wxTreeItemId mObjectsItemId;
		wxTreeItemId mEffectsItemId;
		wxTreeItemId mLightsItemId;
		wxTreeItemId mSoundsItemId;
		wxTreeItemId mEnvItemId;
		std::vector<ObjectTreeItem*> mSceneItems;

		wxTreeItemId mUIId;
		ObjectTreeItem *mMainFrameItem;
	};

}

#endif