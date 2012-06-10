/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ControllerInstance.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2CONTROLLERINSTANCE_HPP
#define PX2CONTROLLERINSTANCE_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	/// 交互模式
	enum InteractionMode
	{
		IM_NONE,
		IM_SELECT,
		IM_TRANSLATE,
		IM_ROLATE,
		IM_SCALE,
		IM_TERRAINHEIGHT,
		IM_TERRAINTEXTURE,
		IM_MAX_MODE
	};
	
	/// 选择模式
	enum SelectionMode
	{
		SM_REPLACE = 0,
		SM_ADD = 1,
		SM_SUBTRACT = 2
	};

	/// 角色操纵模式
	enum ActorControlMode
	{
		ACM_SELECT,
		ACM_TRANSLATE,
		ACM_ROLATE,
		ACM_SCALE
	};

	class RenderViewWindow;
	class PaneController;
	class Selection;

	class ControllerInstance
	{
	public:
		ControllerInstance();
		virtual ~ControllerInstance();

		virtual void Activate() = 0;
		virtual void DeActivate() = 0;

		virtual void NotifySelection (const Selection &selection) = 0;
		virtual void ResetSelection ();

		virtual void DoSelection (PX2::Renderer *renderer, const PX2::Vector2f &point,
			SelectionMode mode); // 点选
		virtual void DoSelection (PX2::Renderer *renderer, 
			const PX2::Vector2f &topLeft, const PX2::Vector2f &bottonRight, 
			SelectionMode mode); // 区域选择
		PX2::APoint CalculateSelectPoint (PX2::Renderer *renderer,
			const PX2::Vector2f &point);
		PX2::APoint GetSelectPoint ();

		virtual void SetInteractionMode (InteractionMode im);
		virtual InteractionMode GetInteractionMode () const;

		virtual void Handle3DPaneLeftDown (RenderViewWindow *win,
			wxMouseEvent &e);
		virtual void Handle3DPaneLeftUp (RenderViewWindow *win,
			wxMouseEvent &e);
		virtual void Handle3DPaneMiddleDown (RenderViewWindow *win,
			wxMouseEvent &e);
		virtual void Handle3DPaneMiddleUp (RenderViewWindow *win, 
			wxMouseEvent &e);
		virtual void Handler3DPaneMouseWheel (RenderViewWindow *win, 
			wxMouseEvent &e);
		virtual void Handle3DPaneRightDown (RenderViewWindow *win,
			wxMouseEvent &e);
		virtual void Handle3DPaneRightUp (RenderViewWindow *win, 
			wxMouseEvent &e);
		virtual void Handle3DPaneMotion (RenderViewWindow *win, 
			wxMouseEvent &e);
		virtual void Handle3DPaneKeyDown (RenderViewWindow *win, 
			wxKeyEvent &e);
		virtual void Handle3DPaneKeyUp (RenderViewWindow *win, 
			wxKeyEvent &e);
		virtual void Handle3DPaneChar (RenderViewWindow *win,
			wxKeyEvent &e);

	protected:
		PX2::Ray3f mRay;
		InteractionMode mInteractionMode;
		PaneController *mPaneController;
		PX2::APoint mSelectPoint;

		virtual void SwitchPaneController (PaneController *ctrl);

		virtual void EnterSelectMode ();
		virtual void ExitSelectMode ();

		virtual void EnterTranslateMode ();
		virtual void ExitTranslateMode ();

		virtual void EnterRolateMode ();
		virtual void ExitRolateMode ();

		virtual void EnterScaleMode ();
		virtual void ExitScaleMode ();

		virtual void EnterTerrainHeightEditMode ();
		virtual void ExitTerrainHeightEditMode ();

		virtual void EnterTerrainTextureEditMode ();
		virtual void ExitTerrainTextureEditMode ();
	};

#include "PX2ControllerInstance.inl"

}

#endif