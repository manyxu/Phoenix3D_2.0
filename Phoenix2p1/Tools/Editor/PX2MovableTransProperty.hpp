/*
*
* ÎÄ¼þÃû³Æ	£º	PX2MovableTransProperty.hpp
*
*/

#ifndef PX2MOVABLEPROPERTY_HPP
#define PX2MOVABLEPROPERTY_HPP

#include "PX2EditorPre.hpp"
#include "PX2Property.hpp"

namespace PX2Editor
{

	class MovableTransProperty : public Property
	{
	public:
		MovableTransProperty (PropertyPage *parent, std::string name,
			PX2::Movable *mov);
		virtual ~MovableTransProperty ();

		virtual void OnChange (wxPropertyGridEvent &event);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		PX2::MovablePtr mMovable;

		wxPGProperty *mPropertyTranslate;
		wxPGProperty *mPropertyRotation;
		wxPGProperty *mPropertyScale;
	};

}

#endif