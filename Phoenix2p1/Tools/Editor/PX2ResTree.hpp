/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ResTree.hpp
*
*/

#ifndef PX2RESTREE_HPP
#define PX2RESTREE_HPP

#include "PX2EditorPre.hpp"
#include "PX2ResTreeItem.hpp"

namespace PX2Editor
{

	class ResTree : public wxTreeCtrl, public PX2::EventHandler, public PX2::Singleton<ResTree>
	{
	public:
		ResTree (wxWindow *parent);
		~ResTree ();

		void OnItemActivated(wxTreeEvent& event);
		void OnSelChanged(wxTreeEvent& event);
		void OnSelChanging(wxTreeEvent& event);

		void UpdateOnPath (std::string pathName);
		ResTreeItem *GetItem (wxTreeItemId id);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		ResTreeItemPtr mRootItem;

		DECLARE_EVENT_TABLE()
	};

}

#endif