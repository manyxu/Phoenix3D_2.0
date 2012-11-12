/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2WindowApplication.hpp
*
* 版本		:	1.0 (2011/02/02)
*
* 作者		：	more
*
*/

#ifndef PX2WINDOWAPPLICATION_HPP
#define PX2WINDOWAPPLICATION_HPP

#include "PX2Application.hpp"
#include <windows.h>

#ifdef PX2_USE_DX9
#include "PX2Dx9RendererInput.hpp"
#include "PX2Dx9RendererData.hpp"
#endif

#ifdef PX2_USE_OPENGLES2
#include "PX2OpenGLES2RendererInput.hpp"
#include "PX2OpenGLES2RendererData.hpp"
#endif

namespace PX2
{

#define PX2_DECLARE_WINDOW_APPLICATION(classname) \
	\
	static bool AppInitialize (); \
	static bool AppTerminate ();

#define PX2_REGISTER_WINDOW_APPLICATION(classname) \
	static bool gsAppInitializeRegistered_##classname = \
	classname::AppInitialize (); \
	static bool gsAppTerminnateRegistered_##classname = \
	classname::AppTerminate ();

#define PX2_IMPLEMENT_WINDOW_APPLICATION(classname) \
	\
	bool classname::AppInitialize () \
	{ \
		Application::msAppInitlizeFun = &classname::AppInitialize; \
		Application::msAppTernamateFun = &classname::AppTerminate; \
		Application::msEntry = &WindowApplication::Entry; \
		msApplication = new classname(); \
		return true; \
	} \
	\
	bool classname::AppTerminate () \
	{ \
		delete (msApplication); \
		return true; \
	}
	//----------------------------------------------------------------------------

	class WindowApplication : public Application
	{
	public:
		WindowApplication ();
		virtual ~WindowApplication ();

		static int Entry (int numArguments, char** arguments);

		virtual int Main (int numArguments, char** arguments);

		virtual bool OnInitlize ();
		virtual bool OnTernamate ();

	protected:
		// 窗口参数
		std::string mWindowTitle;
		int mXPosition, mYPosition, mWidth, mHeight;
		bool mAllowResize;

		// 窗口
		HWND mhWnd;

		RendererInput mInput;
	};

}

#endif