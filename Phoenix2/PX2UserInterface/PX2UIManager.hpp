/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2UIManager.hpp
*
* 版本		:	1.0 (2011/02/23)
*
* 作者		：	more
*
*/

#ifndef PX2UIMANAGER_HPP
#define PX2UIMANATER_HPP

#include "PX2UIPrerequisites.hpp"
#include "PX2Singleton.hpp"
#include "PX2VertexFormat.hpp"
#include "PX2Camera.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIMaterial.hpp"
#include "PX2EventHandler.hpp"
#include "PX2Help.hpp"

namespace PX2
{

	class UIManager : public Singleton<UIManager>, public EventHandler
	{
	public:
		UIManager (EventWorld *eventWorld);
		UIManager (EventWorld *eventWorld, float width, float height);
		~UIManager ();

		// 消息世界
		EventWorld *GetEventWorld ();

		// ID
		int GetNextID ();

		// 顶点格式
		VertexFormat *GetUIVertexFromat ();

		// 相机
		Camera *GetUICamera ();

		// UI材质
		UIMaterial *GetUIMaterial ();

		// App 参数
		float GetWndWidth ();
		float GetWndHeight ();

		UIFrame *CreateAddAddUIFrame (const std::string &name, bool isForwardUI=true);
		void AddUIFrame (UIFrame *group, bool isForwardUI=true);
		bool RemoveUIFrame (const int ID);
		bool RemoveUIFrame (const std::string &name);
		void RemoveAllGroups ();

		UIFrame *GetUIFrame (const int ID);
		UIFrame *GetUIFrame (const std::string &name);

		// 事件
		virtual void DoExecute (Event *event);

		/// 获得可见集
		/**
		* 简单的将所有元素的几何图形加到可见集中。
		*/
		VisibleSet &GetVisibleSet();

		/// 绘制排完序的可见几何图形
		void DrawSorted (Renderer *renderer);

		// 绘制
		/**
		* 简单地遍历所有元素进行绘制。
		*/
		void Draw (Renderer *renderer);

	private:
		UIManager ();

		EventWorldPtr mEventWorld;
		int mNextID;
		float mWndWidth;
		float mWndHeight;
		VertexFormatPtr mVFormat;
		CameraPtr mCamera;
		UIMaterialPtr mUIMaterial;

		VisibleSet mSet;

		std::vector<UIFramePtr> mForwardUIFrames;
		std::vector<UIFramePtr> mBackgroundUIFrames;
	};

	typedef Pointer0<UIManager> UIManagerPtr;

}

#endif