/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ObjectTreeItem.hpp
*
*/

#ifndef PX2OBJECTTREEITEM_HPP
#define PX2OBJECTTREEITEM_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class ObjectTree;

	class ObjectTreeItem 
	{
	public:
		ObjectTreeItem (ObjectTree *tree, wxTreeItemId parentId,
			ObjectTreeItem *parent, PX2::Object *obj, int iconId);
		virtual ~ObjectTreeItem ();

		void SetName (std::string name);
		std::string GetName ();
		void AddChild (PX2::Object *obj);
		void RemoveChild (PX2::Object *obj);

		ObjectTreeItem *GetParent () { return mParent; }
		PX2::Object *GetObject () { return mObject; }
		wxTreeItemId GetItemId () { return mItemID; }
		ObjectTreeItem *GetItem (PX2::Object *obj);
		ObjectTreeItem *GetItem (wxTreeItemId id);

	protected:
		ObjectTree *mTreeCtrl;
		ObjectTreeItem *mParent;
		PX2::ObjectPtr mObject;
		wxTreeItemId mItemID;
		int mIconId;
		std::vector<ObjectTreeItem*> mItems;
	};

}

#endif