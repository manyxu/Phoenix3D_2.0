/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ResTreeItem.cpp
*
*/

#include "PX2ResTreeItem.hpp"
#include "PX2ResTree.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
ResTreeItem::ResTreeItem (std::string name, std::string pathName)
	:
mResName(name),
	mResPathName(pathName),
	mItemID(0),
	mParent(0)
{
}
//-----------------------------------------------------------------------------
ResTreeItem::~ResTreeItem ()
{
}
//-----------------------------------------------------------------------------
void ResTreeItem::SetRoot ()
{
	 ResTree::GetSingleton().DeleteAllItems();

	mParent = 0;
	mItemID = ResTree::GetSingleton().AddRoot("Data", 1);

	BuildChild();

	ResTree::GetSingleton().Expand(mItemID);
}
//-----------------------------------------------------------------------------
void ResTreeItem::AddChild (ResTreeItem *item)
{
	mChildItems.push_back(item);

	item->SetParent(this);

	item->BuildChild();
}
//-----------------------------------------------------------------------------
int ResTreeItem::GetChildNum ()
{
	return (int)mChildItems.size();
}
//-----------------------------------------------------------------------------
ResTreeItem *ResTreeItem::GetChildItem (wxTreeItemId id)
{
	ResTreeItemPtr item;

	for (int i=0; i<(int)mChildItems.size(); i++)
	{
		if (id == mChildItems[i]->GetItemID())
		{
			item = mChildItems[i];

			return item;
		}
		else
		{
			item = mChildItems[i]->GetChildItem(id);

			if (item)
				return item;
		}
	}

	return item;
}
//-----------------------------------------------------------------------------
void ResTreeItem::SetParent (ResTreeItem *parent)
{
	mParent = parent;
	mItemID = ResTree::GetSingleton().AppendItem(parent->GetItemID(), mResName, 0);
}
//-----------------------------------------------------------------------------
void ResTreeItem::BuildChild ()
{
	if (mResPathName.find(".") != std::string::npos)
	{
		mResPathName = mResPathName.substr(0, mResPathName.size()-1);
		return;
	}

	wxDir d;

	d.Open(mResPathName);
	wxString eachFilename;

	if (d.IsOpened())
	{
		if (!d.HasFiles() && !d.HasSubDirs())
			return;

		if (d.GetFirst(&eachFilename))
		{
			do 
			{
				if ((eachFilename != wxT(".")) && (eachFilename != wxT("..")))
				{
					std::string fileName = eachFilename.ToAscii();
					ResTreeItem *item = new0 ResTreeItem(fileName,
						mResPathName+fileName+"/");

					AddChild(item);
				}
			}
			while (d.GetNext(&eachFilename));
		}
	}
}
//-----------------------------------------------------------------------------