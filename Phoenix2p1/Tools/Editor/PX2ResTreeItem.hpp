/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ResTreeItem.hpp
*
*/

#ifndef PX2RESTREEITEM_HPP
#define PX2RESTREEITEM_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class ResTreeItem
	{
	public:
		ResTreeItem (std::string name, std::string pathName);
		~ResTreeItem ();

		wxTreeItemId GetItemID () { return mItemID; }
		std::string GetName () { return mResName; }
		std::string GetPathName () { return mResPathName; }

		void SetRoot ();
		void AddChild (ResTreeItem *item);
		int GetChildNum ();
		ResTreeItem *GetParent () { return mParent; }

		ResTreeItem *GetChildItem (wxTreeItemId id);

public_internal:
		void SetParent (ResTreeItem *parent);
		void BuildChild ();

	protected:
		ResTreeItem ();

		wxTreeItemId mItemID;
		std::string mResName;
		std::string mResPathName;

		ResTreeItem *mParent;
		std::vector<PX2::Pointer0<ResTreeItem>> mChildItems;
	};

	typedef PX2::Pointer0<ResTreeItem> ResTreeItemPtr;

}

#endif