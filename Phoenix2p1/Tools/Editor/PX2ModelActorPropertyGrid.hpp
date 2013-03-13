/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ModelActorPropertyGrid.hpp
*
*/

#ifndef PX2MODELACTORPROPERTYGRID_HPP
#define PX2MODELACTORPROPERTYGRID_HPP

#include "PX2ObjectPropertyGrid.hpp"

namespace PX2Editor
{

	class ModelActorPropertyGrid : public ObjectPropertyGrid
	{
	public:
		ModelActorPropertyGrid (wxWindow *parent);
		virtual ~ModelActorPropertyGrid ();

		DECLARE_DYNAMIC_CLASS(ModelActorPropertyGrid)

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

		ModelActorPropertyGrid ();
		void RefreshOnModelActor ();

		std::string mActorName;
		std::string mActorType;
	};

}

#endif