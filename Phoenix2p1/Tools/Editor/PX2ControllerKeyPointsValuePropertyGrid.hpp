/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ControllerKeyPointsValuePropertyGrid.hpp
*
*/

#ifndef PX2CONTROLLERKEYPOINTSVALUEPROPERTYGRID_HPP
#define PX2CONTROLLERKEYPOINTSVALUEPROPERTYGRID_HPP

#include "PX2EditorPre.hpp"
#include "PX2ObjectPropertyGrid.hpp"

namespace PX2Editor
{

	class ControllerKeyPointsValuePropertyGrid : public ObjectPropertyGrid
	{
	public:
		ControllerKeyPointsValuePropertyGrid (wxWindow *parent);
		~ControllerKeyPointsValuePropertyGrid ();

		DECLARE_DYNAMIC_CLASS(ControllerKeyPointsValuePropertyGrid)

		void SetIndex (int index);
		virtual void OnSetObject(PX2::Object *object);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()

		ControllerKeyPointsValuePropertyGrid ();
		std::string mType;
		int mIndex;
		float mTime;
		PX2::Float3 mValue;
	};

}

#endif