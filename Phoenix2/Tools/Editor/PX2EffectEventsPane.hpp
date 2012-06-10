/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EffectEventsPane.hpp
*
* 版本		:	1.0 (2012/01/19)
*
* 作者		：	more
*
*/

#ifndef PX2EFFECTEVENTPANE_HPP
#define PX2EFFECTEVENTPANE_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2PropertyGrid.hpp"

namespace PX2Editor
{

	class EffectEventsPanel : public wxPanel
	{
	public:
		EffectEventsPanel (wxWindow *parent);
		~EffectEventsPanel ();

		DECLARE_DYNAMIC_CLASS(EffectEventsPanel);

		void OnSize (wxSizeEvent &e);
		void OnListCtrlItemSelected(wxListEvent& event);

public_internal:
		void UpdateEventsOnEffect (PX2::Movable *obj);

	protected:
		EffectEventsPanel ();

		DECLARE_EVENT_TABLE();

		void OnRightDown (wxMouseEvent& e);
		void OnButton (wxCommandEvent& event);
		void OnEE_EmitRate (wxCommandEvent &e);
		void OnEE_ParticleSize (wxCommandEvent &e);
		void OnEE_ParticleColor (wxCommandEvent &e);
		void OnEE_ParticleAlpha (wxCommandEvent &e);
		void OnEE_ParticleSpeed (wxCommandEvent &e);
		void OnEE_ParticleSpeedDir (wxCommandEvent &e);

		wxListCtrl *mListCtrl;
		wxButton *mNewButton;
		wxButton *mDeleteButton;
		PropertyGrid *mPropGrid;

		wxMenu mEventCreateMenu;
	};

}

#endif