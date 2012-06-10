/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ActorTransProperty.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2ACTORTRANSPROPERTY_HPP
#define PX2ACTORTRANSPROPERTY_HPP

#include "PX2EditorPrerequisites.hpp"
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

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
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