/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EffectPane.hpp
*
* 版本		:	1.0 (2012/01/19)
*
* 作者		：	more
*
*/

#ifndef PX2EFFECTPANE_HPP
#define PX2EFFECTPANE_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2PropertyGrid.hpp"

namespace PX2Editor
{

	class EffectPanel : public wxPanel
	{
	public:
		EffectPanel (wxWindow *parent);
		~EffectPanel ();

		DECLARE_DYNAMIC_CLASS(EffectPanel);

		void OnSize (wxSizeEvent &e);

	protected:
		EffectPanel ();

		DECLARE_EVENT_TABLE();

		PropertyGrid *mPropGrid;
	};

}

#endif