/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectNodePane.hpp
*
*/

#ifndef PX2EFFECTNODEPANE_HPP
#define PX2EFFECTNODEPANE_HPP

#include "PX2EditorPre.hpp"
#include "PX2EffectModule.hpp"
#include "PX2EffectActor.hpp"

namespace PX2Editor
{

	class EffectNodePanel : public wxPanel
	{
	public:
		EffectNodePanel (wxWindow *parent);

		void SetActor (PX2::EffectActor *actor);

public_internal:
		void SetParent1 (wxWindow *par);

	protected:
		DECLARE_EVENT_TABLE();

		EffectNodePanel ();
		void RefreshActor (PX2::EffectActor *actor);
		void OnSelectEffect (PX2::Movable *mov);
		void OnSelectModule (PX2::EffectModule *module);
		void OnButton (wxCommandEvent& event);
		void OnListbox (wxCommandEvent& event);
		void OnNewParticles (wxCommandEvent& event);
		void OnNewEffectModule (wxCommandEvent& event);

		PX2::EffectActorPtr mEffectActor;

		wxButton *mNEffect;
		wxButton *mDEffect;
		wxButton *mPlayEffect;
		wxButton *mNModule;
		wxButton *mDModule;
		wxButton *mMoudleCurve;
		wxListBox *mEffectList;
		wxListBox *mModuleList;

		wxMenu mEffectMenu;
		wxMenu mModuleMenu;

		PX2::MovablePtr mSelectedEffect;
		PX2::EffectModulePtr mSelectedEffectModule;

		wxWindow *mParent1;
	};

}

#endif