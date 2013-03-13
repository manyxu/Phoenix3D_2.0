/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectActorInspector.hpp
*
*/

#ifndef PX2EFFECTACTORINSPECTOR_HPP
#define PX2EFFECTACTORINSPECTOR_HPP

#include "PX2EditorPre.hpp"
#include "PX2EffectNodePanel.hpp"
#include "PX2EffectPropertyGrid.hpp"
#include "PX2EffectActor.hpp"
#include "foldpanelbar.h"

namespace PX2Editor
{

	class EffectInspector : public wxScrolledWindow
	{
	public:
		EffectInspector (wxWindow *parent);
		~EffectInspector ();

		void OnSize(wxSizeEvent& e);
		void SetActor (PX2::EffectActor *actor);
		void TryRefreshModule (void *pointer);
		void TryRefreshModulePoints (void *pointer);

	protected:
		EffectInspector ();

		DECLARE_EVENT_TABLE()

		bool mInitSized;
		PX2::EffectActorPtr mEffectActor;
		wxFoldPanelBar *mFoldPaneBar;

	public_internal:
		EffectPropertyGrid *mEffectPropGrid;
		EffectNodePanel *mEffectNodePanel;
	};

}

#endif