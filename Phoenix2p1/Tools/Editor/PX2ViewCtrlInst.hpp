/*
*
* 文件名称	：	PX2ViewCtrlInst.hpp
*
*/

#ifndef PX2VIEWCTRLINST_HPP
#define PX2VIEWCTRLINST_HPP

#include "PX2EditorPre.hpp"

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
	class ViewCtrl;
	class Selection;

	class ViewCtrlInst
	{
	public:
		ViewCtrlInst();
		virtual ~ViewCtrlInst();

		virtual void Activate() = 0;
		virtual void DeActivate() = 0;

		virtual void DoSelection (PX2::Renderer *renderer, const PX2::Vector2f &point,
			SelectionMode mode);
		virtual void DoSelection (PX2::Renderer *renderer, const PX2::Vector2f &topLeft, 
			const PX2::Vector2f &bottonRight, SelectionMode mode);

		PX2::APoint CalculateSelectPoint (PX2::Renderer *renderer, const PX2::Vector2f &point);
		PX2::APoint GetSelectPoint ();

		virtual void SetInteractionMode (InteractionMode im);
		virtual InteractionMode GetInteractionMode () const;

		virtual void HandleLeftDown (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleLeftUp (RenderViewWindow *win,	wxMouseEvent &e);
		virtual void HandleMiddleDown (RenderViewWindow *win,	wxMouseEvent &e);
		virtual void HandleMiddleUp (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMouseWheel (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleRightDown (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleRightUp (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMotion (RenderViewWindow *win, wxMouseEvent &e);

	protected:
		virtual void SwitchPaneController (ViewCtrl *ctrl);

		virtual void EnterSelectMode ();
		virtual void ExitSelectMode ();
		virtual void EnterTranslateMode ();
		virtual void ExitTranslateMode ();
		virtual void EnterRolateMode ();
		virtual void ExitRolateMode ();
		virtual void EnterScaleMode ();
		virtual void ExitScaleMode ();

		PX2::Ray3f mRay;
		InteractionMode mInteractionMode;
		ViewCtrl *mViewCtrl;
		PX2::APoint mSelectPoint;
	};

#include "PX2ViewCtrlInst.inl"

}

#endif