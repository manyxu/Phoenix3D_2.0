/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2GraphicsPrerequisites.hpp
*
* 版本		:	1.0 (2011/01/31)
*
* 作者		：	more
*
*/

#ifndef PX2GRAPHICSPREREQUISITES_HPP
#define PX2GRAPHICSPREREQUISITES_HPP

#include "PX2MathematicsPrerequisites.hpp"

// Begin Microsoft Windows DLL
#if defined(PX2_GRAPHICS_DLL_EXPORT)
    #define PX2_GRAPHICS_ENTRY __declspec(dllexport)
#elif defined(PX2_GRAPHICS_DLL_IMPORT)
    #define PX2_GRAPHICS_ENTRY __declspec(dllimport)
#else
    #define PX2_GRAPHICS_ENTRY
#endif
// End Microsoft Windows DLL

// 加上此宏会对输入的相机是否正交化进行检查，只进行一次正交化检查，只
// 需要进行一次正交化。
#ifdef _DEBUG
    #define PX2_VALIDATE_CAMERA_FRAME_ONCE
#endif

// 当改变了Shader::MAX_PROFILES，在shader持久化读取时使用此宏产生断言。
#ifdef _DEBUG
    #define PX2_ASSERT_ON_CHANGED_MAX_PROFILES
#endif

// 设置这个宏，Renderer::Draw (const Renderable*, const MaterialInstance*)渲染
// 完毕，内部会置回到缺省渲染状态。
#ifdef _DEBUG
	//#define PX2_RESET_STATE_AFTER_DRAW
#endif

// 加上此宏进行渲染像素量的计算
// Renderer::DrawPrimitive.
//#define PX2_QUERY_PIXEL_COUNT

#ifdef PX2_USE_OPENGL
    #ifndef __LINUX__
        #define PX2_USE_TEXT_DISPLAY_LIST
    #endif

    // Some OpenGL 2.x drivers are not handling normal attributes correctly.
    // This is a problem should you want to use the normal vector to pass a
    // 4-tuple of information to the shader.  The OpenGL 1.x glNormalPointer
    // assumes the normals are 3-tuples.  If you know that your target
    // machines correctly support OpenGL 2.x normal attributes, expose the
    // following #define.  Otherwise, the renderer will use the OpenGL 1.x
    // glNormalPointer.
    //
    // TODO.  I must be misunderstanding how generic attributes work.  On the
    // Macintosh, whether PowerPC or Intel, with NVIDIA graphics cards, the
    // generic attributes for normals does not work.
    #ifndef __APPLE__
        #define PX2_USE_OPENGL2_NORMAL_ATTRIBUTES
    #endif
#endif

// Dx9渲染器中的一些检测
#ifdef PX2_USE_DX9
    #ifdef _DEBUG
        #define PX2_PDR_DEBUG
    #endif
#endif

#endif