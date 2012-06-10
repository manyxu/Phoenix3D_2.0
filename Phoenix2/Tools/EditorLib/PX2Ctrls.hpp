/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2CtrlsFactory.hpp
*
* 版本		:	1.0 (2011/06/06)
*
* 作者		：	more
*
*/

#ifndef PX2CTRLS_HPP
#define PX2CTRLS_HPP

#include "PX2EditorLibPrerequisites.hpp"

namespace PX2Editor
{

	class CtrlsFactory
	{
	public:
		CtrlsFactory ();
		~CtrlsFactory ();

		PX2::Node *CreateTranslateCtrl_P ();
		PX2::Node *CreateRolateCtrl_P ();
		PX2::Node *CreateScaleCtrl_P ();

		PX2::Node *CreateTranslateCtrl_O ();
		PX2::Node *CreateRolateCtrl_O ();
		PX2::Node *CreateScaleCtrl_O ();

	private:
		PX2::VertexFormatPtr mVertexFormat;
	};

	class SceneNodeCtrl : public PX2::EventHandler
	{
	public:
		SceneNodeCtrl ();
		~SceneNodeCtrl ();

		enum AxisMode
		{
			AM_WORLD,
			AM_LOCAL
		};

		void SetAxisMode (AxisMode mode);
		AxisMode GetAxisMode () { return mAxisMode; }

		enum LookType
		{
			LT_TOP,
			LT_FRONT,
			LT_LEFT,
			LT_PERSPECTIVE
		};

		void SetLookType (LookType type);
		LookType GetLookType () { return mLookType; }

		enum CtrlType
		{
			CT_SELECT,
			CT_TRANSLATE,
			CT_ROLATE,
			CT_SCALE
		};

		void SetCtrlType (CtrlType type);
		CtrlType GetCtrlType () { return mCtrlType; }

		enum DragType
		{
			DT_NONE,
			DT_X,
			DT_Y,
			DT_Z,
			DT_XY,
			DT_XZ,
			DT_YZ,
			DT_XYZ
		};

		void SetDragType (DragType type);
		DragType GetDragType () { return mDragType; }

		void OnLeftMouseDown (PX2::Renderer *renderer,
			const PX2::Vector2f &point);
		void OnLeftMouseUp (PX2::Renderer *renderer,
			const PX2::Vector2f &point);
		void OnMouseWheel (PX2::Renderer *renderer, float wheelDelta);
		void OnMouseMove (PX2::Renderer *renderer, float x, float y);

		PX2::Node *GetCtrlsGroup () { return mCtrlsGroup; }
		PX2::Movable *GetCurrentCtrlX ();
		PX2::Movable *GetCurrentCtrlY ();
		PX2::Movable *GetCurrentCtrlZ ();
		PX2::Movable *GetCurrentCtrlXYZ ();

		PX2::APoint GetPosition();
		PX2::AVector GetXDir ();
		PX2::AVector GetYDir ();
		PX2::AVector GetZDir ();

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	private:
		void UpdateCtrl ();
		void UpdateCtrlTrans ();

		AxisMode mAxisMode;
		LookType mLookType;
		CtrlType mCtrlType;
		PX2::NodePtr mCtrl_P_Translate;
		PX2::NodePtr mCtrl_P_Rolate;
		PX2::NodePtr mCtrl_P_Scale;
		PX2::NodePtr mCtrl_O_Translate;
		PX2::NodePtr mCtrl_O_Rolate;
		PX2::NodePtr mCtrl_O_Scale;
		PX2::SwitchNodePtr mCtrlsGroup;
		float mOriginScale;
		DragType mDragType;
	};

}

#endif