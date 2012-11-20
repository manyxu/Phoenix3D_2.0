/*
*
* ÎÄ¼þÃû³Æ	£º	PX2DefCtrlInst.hpp
*
*/

#ifndef PX2DEFVIEWCTRLINST_HPP
#define PX2DEFVIEWCTRLINST_HPP

#include "PX2EditorPre.hpp"
#include "PX2ViewCtrlInst.hpp"

namespace PX2Editor
{

	class DefViewCtrlInst : public ViewCtrlInst
	{
	public:
		DefViewCtrlInst ();
		virtual ~DefViewCtrlInst ();

		virtual void Activate();
		virtual void DeActivate();
	};

}

#endif