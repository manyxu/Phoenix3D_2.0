/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2WglRendererData.hpp
*
* 版本		:	1.0 (2011/05/17)
*
* 作者		：	TimeX
*
*/

#ifndef PX2WGLRENDERERDATA_HPP
#define PX2WGLRENDERERDATA_HPP

#include "PX2OpenGLPrerequisites.hpp"
#include "PX2OpenGLRendererData.hpp"
#include "PX2WGLExtensions.hpp"

namespace PX2
{

	class WglRendererData : public RendererData
	{
	public:
		HWND mWindowHandle;
		HDC mWindowDC;
		HGLRC mWindowRC;
	};

}

#endif
