/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EffectEditTimeLineWindow.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2EFFECTEDITTIMELINEWINDOW_HPP
#define PX2EFFECTEDITTIMELINEWINDOW_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class EffectEditTimeLineWindow : public wxScrolledWindow
	{
	public:
		EffectEditTimeLineWindow ();
		EffectEditTimeLineWindow (wxWindow* parent);
		virtual ~EffectEditTimeLineWindow ();

		DECLARE_DYNAMIC_CLASS(EffectEditTimeLineWindow);

		void OnPaint(wxPaintEvent &event);
		void OnLeftDown(wxMouseEvent& e);
		void OnLeftUp(wxMouseEvent& e);
		void OnLeftDoubleClick(wxMouseEvent& e);
		void OnMotion (wxMouseEvent &e);

		void ResetSelectIndex ();
		void SelectEffectNode (PX2::EffectNode *node);
		void AddEffectObject (PX2::Movable *obj);
		void RemoveEffectObject (PX2::Movable *obj);
		PX2::Movable *GetSelectEffectObject ();
		void ClearEffectObjects ();

	protected:
		DECLARE_EVENT_TABLE()
		
		void DoPaint (wxDC &dc);
		void DrawTimeLine (wxDC &dc);
		void DrawOneTimeGrid (int index, std::string name, wxDC &dc);
		void DrawOneTimeGridKeys (int index, PX2::Movable *obj, wxDC &dc);
		int GetSelectIndex (int y);
		int GetSelectTimeKeyIndex (int x);
		void CalculateDragingEvents (int selectIndexX, PX2::Movable *obj);

		void OnSelectEffect (PX2::Movable *obj);
		void OnSelectEffectEvent (PX2::EffectEvent *event);

		wxBrush mWhiteBrush;
		wxBrush mBlackBrush;
		wxBrush mGrayBrush;
		static int sTimeLineHeight;
		static int sTimeGridHeadWidth;
		static int sTimeGridWidth;
		static int sTimeGridHeight;
		static int sTimeKeyWidth;
		bool mLeftDown;
		std::vector<PX2::MovablePtr> mEffectObjects;
		int mSelectIndex;
		int mSelectTimeKeyIndexX;
		int mSelectTimeKeyIndexY;
		bool mIsDragingEvents;
		std::vector<PX2::EffectEventPtr> mDragingEvents;
	};

}

#endif