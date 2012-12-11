/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainMaterialPane.hpp
*
*/

#ifndef PX2TERRAINMATERIALPANE_HPP
#define PX2TERRAINMATERIALPANE_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class TerrainMaterialPanel : public wxPanel
	{
	public:
		TerrainMaterialPanel (wxWindow *parent);

		void OnSliderUpdate (wxCommandEvent &event);
		void OnRadio (wxCommandEvent &event);
		void OnListbox (wxCommandEvent& event);
		void OnTextEnter (wxCommandEvent& event);
		void OnButton (wxCommandEvent& event);

		void RefleshCtrls ();

	protected:
		TerrainMaterialPanel ();
		void OnColourChange (wxColourPickerEvent &e);

		PX2::Float3 mShineEmissive;
		PX2::Float3 mShineAmbient;
		PX2::Float3 mShineDiffuse;
		wxColourPickerCtrl *mMtlEmissive;
		wxColourPickerCtrl *mMtlAmbient;
		wxColourPickerCtrl *mMtlDiffuse;

		wxTextCtrl *mTexToUse;
		wxButton *mTexToUseButton;

		wxTextCtrl *mXIndex;
		wxTextCtrl *mYIndex;
		wxTextCtrl *mTextPath;
		wxTextCtrl *mURepeatText;
		wxSlider *mURepeatSlider;
		wxTextCtrl *mVRepeatText;
		wxSlider *mVRepeatSlider;
		wxStaticBitmap *mLayerTexBitMap;

		wxListBox *mLayerList;

		DECLARE_EVENT_TABLE();
	};

}

#endif