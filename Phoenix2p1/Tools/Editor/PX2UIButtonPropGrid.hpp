/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIButtonPropGrid.hpp
*
*/

#ifndef PX2UIBUTTONPROPGRID_HPP
#define PX2UIBUTTONPROPGRID_HPP

#include "PX2UIFramePropGrid.hpp"
#include "PX2UIButton.hpp"

namespace PX2Editor
{

	class UIButtonPropGrid : public UIFramePropGrid
	{
	public:
		UIButtonPropGrid (wxWindow *parent);
		~UIButtonPropGrid ();

		virtual void OnSetObject(PX2::Object *object);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		PX2::UIButtonPtr mButton;
		float mWidth;
		float mHeight;
	};

}

#endif