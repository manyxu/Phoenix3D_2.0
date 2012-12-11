/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainBrushPane.hpp
*
*/

#ifndef PX2TERRAINBRUSHPANE_HPP
#define PX2TERRAINBRUSHPANE_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class TerrainBrushPanel : public wxPanel
	{
	public:
		TerrainBrushPanel (wxWindow *parent);

		void OnChoice (wxCommandEvent &event);
		void OnSliderUpdate (wxCommandEvent &event);
		void OnCheckbox (wxCommandEvent& event);

		void RefleshCtrls ();

	protected:
		TerrainBrushPanel ();

		// Brush
		wxChoice *mInterplate;
		wxSlider *mSize;
		wxSlider *mStrength;

		DECLARE_EVENT_TABLE();
	};

}

#endif