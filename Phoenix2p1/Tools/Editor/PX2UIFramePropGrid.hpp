/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIFramePropGrid.hpp
*
*/

#ifndef PX2UIFRAMEPROPGRID_HPP
#define PX2UIFRAMEPROPGRID_HPP

#include "PX2UIFrame.hpp"
#include "PX2ObjectPropertyGrid.hpp"

namespace PX2Editor
{

	class UIFramePropGrid : public ObjectPropertyGrid
	{
	public:
		UIFramePropGrid (wxWindow *parent);
		virtual ~UIFramePropGrid ();

		virtual void OnSetObject(PX2::Object *object);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		PX2::UIFramePtr mUIFrame;
		std::string mObjectType;
	};

}

#endif