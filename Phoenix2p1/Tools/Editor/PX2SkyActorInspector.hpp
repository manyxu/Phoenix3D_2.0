/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SkyInspector.hpp
*
*/

#ifndef PX2SKYACTORINSPECTOR_HPP
#define PX2SKYACTORINSPECTOR_HPP

#include "PX2EditorPre.hpp"
#include "PX2SkyActor.hpp"
#include "PX2SkyActorPropertyGrid.hpp"

namespace PX2Editor
{

	class SkyActorInspector : public wxScrolledWindow
	{
	public:
		SkyActorInspector (wxWindow *parent);
		~SkyActorInspector ();

		void OnSize(wxSizeEvent& e);
		void SetActor (PX2::SkyActor *actor);

	protected:
		DECLARE_EVENT_TABLE()

		SkyActorInspector ();

		bool mInited;
		PX2::SkyActorPtr mSkyActor;
		SkyActorPropertyGrid *mSkyActorPropertyGrid;
	};

}

#endif