/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Application.hpp
*
* 版本		:	1.0 (2012/04/15)
*
* 作者		：	more
*
*/

#ifndef PX2APPLICATIONBASE_HPP
#define PX2APPLICATIONBASE_HPP

#include "PX2Core.hpp"
#include "PX2Mathematics.hpp"
#include "PX2Graphics.hpp"
#include "PX2Renderers.hpp"
#include "PX2Unity.hpp"

namespace PX2
{

	class ApplicationBase
	{
	protected:
		ApplicationBase ();
	public:
		virtual ~ApplicationBase ();

		// App
		static ApplicationBase* msApplication;

		// system use
		bool Initlize ();
		bool Ternamate ();

		// you overwrite these
		virtual bool OnInitlize ();
		virtual bool OnTernamate ();

		virtual void OnIdle ();
		virtual bool OnResume();
		virtual bool OnPause();

		// Enteries
		typedef bool (*AppInitlizeFun)();
		static AppInitlizeFun msAppInitlizeFun;
		typedef bool (*AppTernamateFun)();
		static AppTernamateFun msAppTernamateFun;
		typedef int (*EntryPoint)(int numArguments, char** arguments);
		static EntryPoint msEntry;

		virtual int Main (int numArguments, char** arguments);

	protected:
		// 渲染性能衡量
		void ResetTime ();
		void MeasureTime ();
		void UpdateFrameCount ();
		void DrawFrameRate (int x, int y, const Float4& color);
		
		// 渲染相关
		Texture::Format mColorFormat;
		Texture::Format mDepthStencilFormat;
		int mNumMultisamples;
		Float4 mClearColor;
		Renderer* mRenderer;
		CameraPtr mCamera;

		GraphicsRoot *mRoot;

		double mLastTime, mAccumulatedTime, mFrameRate;
		int mFrameCount, mAccumulatedFrameCount, mTimer, mMaxTimer;
	};

}

#endif