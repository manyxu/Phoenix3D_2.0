/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ResTreePanel.hpp
*
*/

#ifndef PX2RESTREEPANEL_HPP
#define PX2RESTREEPANEL_HPP

#include "PX2EditorPre.hpp"
#include "PX2ResTree.hpp"

namespace PX2Editor
{

	class ResTreePanel : public wxPanel
	{
	public:
		ResTreePanel (wxWindow *parent);
		~ResTreePanel ();

		ResTree *GetResTree ();

		void OnUpdate (wxCommandEvent &e);

	protected:
		DECLARE_EVENT_TABLE()
		
		ResTree *mResTree;
		wxToolBar *mResTreeBar;
	};

}

#endif