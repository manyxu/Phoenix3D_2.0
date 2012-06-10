/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EditorOption.hpp
*
* 版本		:	1.0 (2011/04/18)
*
* 作者		：	more
*
*/

#ifndef PX2EDITOROPTIONS_HPP
#define PX2EDITOROPTIONS_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2Singleton.hpp"

namespace PX2Editor
{

	class EditorOptions : public PX2::Singleton<EditorOptions>
	{
	public:
		EditorOptions ();
		~EditorOptions ();

		bool Save (std::string filename);
		bool Load (std::string filename);

		float mGridSize; //< 场景网格大小
		float mOrthoAdjust; //< 正交相机调解率
		float mOrthoFrustumMin;
		bool mViewFull; //< 
		int mViewFullIndex; //<
		bool mShowEffectEditorBar;
	};

}

#endif