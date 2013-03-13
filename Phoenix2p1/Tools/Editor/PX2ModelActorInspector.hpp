/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ModelInspector.hpp
*
*/

#ifndef PX2MODELACTORINSPECTOR_HPP
#define PX2MODELACTORINSPECTOR_HPP

#include "PX2EditorPre.hpp"
#include "PX2ModelActorPropertyGrid.hpp"
#include "PX2Actor.hpp"
#include "foldpanelbar.h"

namespace PX2Editor
{

	class ModelActorInspector : public wxScrolledWindow
	{
	public:
		ModelActorInspector (wxWindow *parent);
		~ModelActorInspector ();

		void OnSize(wxSizeEvent& e);
		void SetActor (PX2::Actor *actor);

	protected:
		DECLARE_EVENT_TABLE()

		ModelActorInspector ();

		bool mInitSized;
		PX2::ActorPtr mActor;
		wxFoldPanelBar *mFoldPaneBar;
		ModelActorPropertyGrid *mModelActorPropGrid;
	};

}

#endif