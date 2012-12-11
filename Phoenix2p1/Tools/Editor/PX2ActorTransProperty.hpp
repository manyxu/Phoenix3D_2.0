/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ActorTransProperty.hpp
*
*/

#ifndef PX2ACTORTRANSPROPERTY_HPP
#define PX2ACTORTRANSPROPERTY_HPP

#include "PX2EditorPre.hpp"
#include "PX2Property.hpp"

namespace PX2Editor
{

	class ActorTransProperty : public Property
	{
	public:
		ActorTransProperty (PropertyPage *parent, std::string name,
			PX2::Actor *actor);
		virtual ~ActorTransProperty ();

		virtual void OnChange (wxPropertyGridEvent &event);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		PX2::ActorPtr mActor;

		wxPGProperty *mPropertyTranslate;
		wxPGProperty *mPropertyRotation;
		wxPGProperty *mPropertyScale;
	};

}

#endif