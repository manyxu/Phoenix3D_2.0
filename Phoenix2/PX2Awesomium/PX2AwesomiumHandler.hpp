/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Awesomium.hpp
*
* 版本		:	1.0 (2011/01/30)
*
* 作者		：	more
*
*/

#ifndef PX2AWESOMIUMHANDLER_HPP
#define PX2AWESOMIUMHANDLER_HPP

#include "PX2AwesomiumPrerequisites.hpp"
#include "PX2EventHandler.hpp"

namespace PX2
{

	class AwesomiumHandler : public Singleton<AwesomiumHandler>, public EventHandler
	{
	public:
		AwesomiumHandler ();
		~AwesomiumHandler ();

		/// 初始化
		/**
		* 内部会创建默认的缺省贴图
		*/
		bool Initlize (float width, float height);

		Awesomium::WebCore *GetWebCore ();
		Awesomium::WebView* GetDefaultView ();

		void SetTexture (Texture2D *texture);
		Texture2D *GetTexture ();

		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

	protected:
		bool mInitlized;
		Awesomium::WebCore* mCore;
		Awesomium::WebView* mDefaultView;
		float mWebViewWidth;
		float mWebViewHeight;
		const Awesomium::RenderBuffer *mDefaultRenderBuffer;
		Texture2DPtr mTexture;
	};

	typedef Pointer0<AwesomiumHandler> AwesomiumHandlerPtr;
#include "PX2AwesomiumHandler.inl"

}

#endif