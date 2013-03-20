/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ControllerPropertyGrid.hpp
*
*/

#ifndef PX2CONTROLLERPROPERTYGRID_HPP
#define PX2CONTROLLERPROPERTYGRID_HPP

#include "PX2EditorPre.hpp"
#include "PX2ObjectPropertyGrid.hpp"

namespace PX2Editor
{

	class ControllerPropertyGrid : public ObjectPropertyGrid
	{
	public:
		ControllerPropertyGrid (wxWindow *parent);
		~ControllerPropertyGrid ();

		DECLARE_DYNAMIC_CLASS(EffectPropertyGrid)

		virtual void OnSetObject(PX2::Object *object);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

	protected:
		DECLARE_EVENT_TABLE()

		ControllerPropertyGrid ();

		std::string mObjectType;
	};

}

#endif