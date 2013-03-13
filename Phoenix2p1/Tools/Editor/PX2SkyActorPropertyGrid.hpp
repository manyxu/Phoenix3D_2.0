/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SkyActorPropertyGrid.hpp
*
*/

#ifndef PX2SKYACTORPROPERTYGRID_HPP
#define PX2SKYACTORPROPERTYGRID_HPP

#include "PX2EditorPre.hpp"
#include "PX2ObjectPropertyGrid.hpp"
#include "PX2SkyActor.hpp"

namespace PX2Editor
{

	class SkyActorPropertyGrid : public ObjectPropertyGrid
	{
	public:
		SkyActorPropertyGrid (wxWindow *parent);
		virtual ~SkyActorPropertyGrid ();

		DECLARE_DYNAMIC_CLASS(SkyActorPropertyGrid)

		virtual void OnSetObject(PX2::Object *object);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()

		SkyActorPropertyGrid ();
		void RefreshOnSkyActor ();

		PX2::SkyActorPtr mSkyActor;

		std::string mActorName;
		std::string mActorType;

		PX2::Float4 mSunParams;
		PX2::Float4 mSkyParams;
	};

}

#endif