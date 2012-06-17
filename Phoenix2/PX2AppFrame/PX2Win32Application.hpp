/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Win32Application.hpp
*
* 版本		:	1.0 (2011/02/02)
*
* 作者		：	more
*
*/

#ifndef PX2WIN32APPLICATION_HPP
#define PX2WIN32APPLICATION_HPP

#include "PX2Application.hpp"
#include <windows.h>

namespace PX2
{

	class Win32Application : public Application
	{
	public:
		Win32Application ();
		virtual ~Win32Application ();

		// 运行
		void Run ();

		// 初始/终结
		virtual bool Initlize ();
		virtual bool OnInitlize ();
		virtual bool OnTernamate ();
		virtual bool Ternamate ();

		// 逻辑，渲染
		virtual void OnIdle ();

	protected:
		// 窗口参数
		std::string mWindowTitle;
		int mXPosition, mYPosition, mWidth, mHeight;
		Float4 mClearColor;
		bool mAllowResize;

		// 窗口
		HWND mhWnd;

		// 渲染相关
		Texture::Format mColorFormat;
		Texture::Format mDepthStencilFormat;
		int mNumMultisamples;
		Renderer* mRenderer;
		CameraPtr mCamera;

#ifdef PX2_USE_DX9
		RendererInput mInput;
#endif

		// EventSystem
		EventWorldPtr mEventWorld;
		OISEventAdapterPtr mOISEventAdapter;

		// ResourceManager
		ResourceManager *mResManager;

		// UserInterface
		UIManagerPtr mUIManager;

		// 渲染性能衡量
		void ResetTime ();
		void MeasureTime ();
		void UpdateFrameCount ();
		void DrawFrameRate (int x, int y, const Float4& color);

		double mLastTime, mAccumulatedTime, mFrameRate;
		int mFrameCount, mAccumulatedFrameCount, mTimer, mMaxTimer;
	};

}

#endif