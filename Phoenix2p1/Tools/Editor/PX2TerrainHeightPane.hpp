/*
*
* �ļ�����	��	PX2TerrainBrushPane.hpp
*
*/

#ifndef PX2TERRAINHEIGHTPANE_HPP
#define PX2TERRAINHEIGHTPANE_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class TerrainHeightPanel : public wxPanel
	{
	public:
		TerrainHeightPanel (wxWindow *parent);

		void OnRadio (wxCommandEvent &event);
		void RefleshCtrls ();

	protected:
		DECLARE_EVENT_TABLE();

		TerrainHeightPanel ();

		wxRadioBox *mHeightModeRadio;
	};

}

#endif