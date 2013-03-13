/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ObjectTreeItem.cpp
*
*/

#include "PX2ObjectTreeItem.hpp"
#include "PX2ObjectTree.hpp"
#include "PX2UIFrame.hpp"
using namespace PX2Editor;
using namespace PX2;

ObjectTreeItem::ObjectTreeItem (ObjectTree *tree,  wxTreeItemId parentId,
	ObjectTreeItem *parent,	PX2::Object *obj, int iconId)
	:
mTreeCtrl(tree),
mParent(parent),
mObject(obj),
mIconId(iconId)
{
	if (mParent)
	{
		mItemID = mTreeCtrl->AppendItem(parent->GetItemId(),
			obj->GetName(), mIconId);
	}
	else
	{
		mItemID = mTreeCtrl->AppendItem(parentId, obj->GetName(), mIconId);
	}

	UIFrame *frame = DynamicCast<UIFrame>(mObject);
	if (frame)
	{
		for (int i=0; i<(int)frame->GetNumChildren(); i++)
		{
			Movable *mov = frame->GetChild(i);
			if (mov)
			{
				AddChild(mov);
			}
		}
	}
}
//-----------------------------------------------------------------------------
ObjectTreeItem::~ObjectTreeItem ()
{
	for (int i=0; i<(int)mItems.size(); i++)
	{
		delete mItems[i];
	}
	mItems.clear();

	mTreeCtrl->Delete(mItemID);
}
//-----------------------------------------------------------------------------
void ObjectTreeItem::SetName (std::string name)
{
	mTreeCtrl->SetItemText(mItemID, name);

	if (mObject)
		mObject->SetName(name);
}
//-----------------------------------------------------------------------------
std::string ObjectTreeItem::GetName ()
{
	return std::string(mTreeCtrl->GetItemText(mItemID).ToAscii());
}
//-----------------------------------------------------------------------------
void ObjectTreeItem::AddChild (PX2::Object *obj)
{
	ObjectTreeItem *item = new ObjectTreeItem(mTreeCtrl, mItemID, this, obj, 
		mIconId);
	mItems.push_back(item);
}
//-----------------------------------------------------------------------------
void ObjectTreeItem::RemoveChild (PX2::Object *obj)
{
	std::vector<ObjectTreeItem*>::iterator it = mItems.begin(); 
	for (; it!=mItems.end(); it++)
	{
		if ((*it)->GetObject() == obj)
		{
			delete0(*it);
			mItems.erase(it);
			return;
		}
	}
}
//-----------------------------------------------------------------------------
ObjectTreeItem *ObjectTreeItem::GetItem (PX2::Object *obj)
{
	if (mObject == obj)
		return this;

	for (int i=0; i<(int)mItems.size(); i++)
	{
		ObjectTreeItem *item = mItems[i]->GetItem(obj);

		if (item)
		{
			return item;
		}
	}

	return 0;
}
//-----------------------------------------------------------------------------
ObjectTreeItem *ObjectTreeItem::GetItem (wxTreeItemId id)
{
	if (mItemID == id)
		return this;

	for (int i=0; i<(int)mItems.size(); i++)
	{
		if (mItems[i])
		{
			ObjectTreeItem *item = mItems[i]->GetItem(id);

			if (item)
			{
				return item;
			}
		}
	}

	return 0;
}
//-----------------------------------------------------------------------------