/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ActorTreeItem.cpp
*
*/

#include "PX2ActorTreeItem.hpp"
using namespace PX2Editor;
using namespace PX2;

ActorTreeItem::ActorTreeItem (wxTreeCtrl *treeCtrl, wxTreeItemId parentId, 
							  Actor *actor)
{
	mActor = actor;
	mTreeCtrl = treeCtrl;
	mParentItemID = parentId;
	mItemID = mTreeCtrl->AppendItem(parentId, actor->GetName(), 0);
}
//-----------------------------------------------------------------------------
ActorTreeItem::~ActorTreeItem ()
{
	mActor = 0;
	mTreeCtrl->Delete(mItemID);
}
//-----------------------------------------------------------------------------
void ActorTreeItem::SetName (std::string name)
{
	mTreeCtrl->SetItemText(mItemID, name);
	if (mActor)
		mActor->SetName(name);
}
//-----------------------------------------------------------------------------