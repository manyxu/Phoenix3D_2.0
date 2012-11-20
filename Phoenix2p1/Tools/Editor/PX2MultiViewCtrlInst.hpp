/*
*
* ÎÄ¼þÃû³Æ	£º	PX2MultiViewCtrlInst.hpp
*
*/

#ifndef PX2MULTIVIEWCTRLINST_HPP
#define PX2MULTIVIEWCTRLINST_HPP

#include "PX2EditorPre.hpp"
#include "PX2ViewCtrlInst.hpp"

namespace PX2Editor
{

	class MultiViewCtrlInst : public ViewCtrlInst
	{
	public:
		MultiViewCtrlInst ();
		~MultiViewCtrlInst ();

		virtual void Activate();
		virtual void DeActivate();
	};


}

#endif