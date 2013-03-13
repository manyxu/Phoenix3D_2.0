/*
* Turandot 3D 游戏引擎 Version 1.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	TdOpenGLES2RendererPre.hpp
*
* 版本		:	1.0 (2011/07/12)
*
* 作者		：	许多
*
*/

#ifndef PX2OPENGLES2RENDERERPRE_HPP
#define PX2OPENGLES2RENDERERPRE_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Assert.hpp"

#include <GLES2/gl2.h>
#include <EGL/egl.h>

enum AttribLocationPos
{
	ALP_POSITION = 0,
	ALP_NORMAL,
	ALP_COLOR0,
	ALP_TEXCOORD0,
};

#define PX2_GL_CHECK(x) \
	x; \
		{ \
		GLenum glError = glGetError(); \
		if(glError != GL_NO_ERROR) { \
		assertion(false, "glGetError() = %i (0x%.8x) at line %i\n", glError, glError, __LINE__); \
		} \
		}

#define PX2_EGL_CHECK(x) \
	x; \
	{ \
	EGLint eglError = eglGetError(); \
	if(eglError != EGL_SUCCESS) { \
	assertion(false, "eglGetError() = %i (0x%.8x) at line %i\n", eglError, eglError, __LINE__); \
	} \
	}

#endif