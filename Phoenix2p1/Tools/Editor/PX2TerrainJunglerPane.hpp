/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainJunglerPane.hpp
*
*/

#ifndef PX2TERRAINJUNGLERPANE_HPP
#define PX2TERRAINJUNGLERPANE_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class TerrainJunglerPanel : public wxPanel
	{
	public:
		TerrainJunglerPanel (wxWindow *parent);

		void OnRadio (wxCommandEvent &event);
		void OnListbox (wxCommandEvent& event);
		void OnListboxD (wxCommandEvent& event);
		void OnButton (wxCommandEvent& event);
		void OnTextEnter (wxCommandEvent& event);

		void RefleshCtrls ();

	protected:
		DECLARE_EVENT_TABLE();

		TerrainJunglerPanel ();

		wxTextCtrl *mTexToUse;
		wxButton *mTexToUseButton;
		wxTextCtrl *mXIndex;
		wxTextCtrl *mYIndex;
		wxTextCtrl *mWidthText;
		wxTextCtrl *mHeightText;
		wxStaticBitmap *mJungleTexBitmap;
		wxListBox *mJungleList;
	};

}

#endif