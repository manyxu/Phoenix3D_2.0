/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ObjectNameProperty.hpp
*
*/

#ifndef PX2OBJECTNAMEPROPERTY_HPP
#define PX2OBJECTNAMEPROPERTY_HPP

#include "PX2EditorPre.hpp"
#include "PX2Property.hpp"

namespace PX2Editor
{

	class ObjectNameProperty : public Property
	{
	public:
		ObjectNameProperty (PropertyPage *parent, std::string name,
			PX2::Object *object);
		virtual ~ObjectNameProperty ();

		virtual void OnChange (wxPropertyGridEvent &event);

		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		PX2::ObjectPtr mObject;
	};

}

#endif