/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	RenderViewWindow.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2RENDERVIEWWINDOW_HPP
#define PX2RENDERVIEWWINDOW_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2EditorGeneral.hpp"
#include "PX2Ctrls.hpp"

namespace PX2Editor
{

	class RenderViewWindow : public wxWindow, public PX2::EventHandler
	{
	public:
		RenderViewWindow ();
		RenderViewWindow (wxWindow *parent);
		virtual ~RenderViewWindow ();

		DECLARE_DYNAMIC_CLASS(RenderViewWindow)
		
		void Initialize ();
		void InitExpand ();

		// Event hooks
		void OnSize(wxSizeEvent& e);
		void OnMove(wxMoveEvent& e);
		void OnPaint(wxPaintEvent& e);
		void OnLeftDown(wxMouseEvent& e);
		void OnLeftUp(wxMouseEvent& e);
		void OnMiddleDown(wxMouseEvent& e);
		void OnMiddleUp(wxMouseEvent& e);
		void OnMouseWheel(wxMouseEvent& e);
		void OnRightDown(wxMouseEvent& e);
		void OnRightUp(wxMouseEvent& e);
		void OnMotion(wxMouseEvent& e);
		void OnKeyDown(wxKeyEvent& e);
		void OnKeyUp(wxKeyEvent& e);
		void OnChar(wxKeyEvent& e);
		void OnEnterWindow(wxMouseEvent& e);
		void OnLeaveWindow(wxMouseEvent& e);

		void OnViewOptionsClicked(wxCommandEvent& e);
		void OnMouseCaptureLost(wxMouseCaptureLostEvent& e);
		void OnViewTypeCommand (wxCommandEvent& e);
		void OnWireFrame (wxCommandEvent& e);
		void OnTextured (wxCommandEvent& e);
		void OnFullFour (wxCommandEvent& e);
		void OnStageGrid (wxCommandEvent& e);
		void OnActorModel (wxCommandEvent& e);
		void OnActorLight_Ambient (wxCommandEvent& e);
		void OnActorLight_Direction (wxCommandEvent& e);
		void OnActorLight_Point (wxCommandEvent& e);
		void OnActorLight_Spot (wxCommandEvent& e);
		void OnActorSound (wxCommandEvent& e);
		void OnCloneInstance (wxCommandEvent& e);
		void OnCloneData (wxCommandEvent& e);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

		void SetWindowIndex (int index);
		int GetWindowIndex ();

		// 视角类型
		enum ViewType
		{
			VT_TOP = 0,
			VT_FRONT = 1,
			VT_LEFT = 2,			
			VT_PERSPECTIVE = 3,
			VT_MAX_TYPE
		};
		
		void SetViewType (ViewType viewType);
		ViewType GetViewType ();

		enum ViewDetail
		{
			VD_WIREFRAME = 0,
			VD_SOLID = 1,
			VD_TEXTURED = 2
		};

		void SetViewDetail (ViewDetail viewDetail);
		ViewDetail GetViewDetail () const;

		void OnTimer (wxTimerEvent& event);
		void TargetCamera (const PX2::Vector3f &pos);
		void SetCameraOrientation (const PX2::HQuaternion &orientation);
		void DollyCamera (const PX2::Vector3f &trans);
		void PanCamera (const float &horz, const float &vert); //< 透视角度，上下左右移动，其他视角和MoveCamera一样
		void RollCamera (const float &roll);
		void OrbitCamera (const float &horz, const float &vert);
		void RolateCamera (const float &horz, const float &vert);
		void MoveCamera (const float &horz, const float vert); //< 透视角度，沿着视线方向移动
		void ZoomCamera (float zoom);

		// option
		void FocusCursourOnCenter ();

		PixelToWorld StartMouseDrag(wxMouseEvent& e);
		void EndMouseDrag(wxMouseEvent& e);

		void SetScene (PX2::Movable *scene);
		PX2::Movable *GetScene ();

		void SetHelpScene (PX2::Movable *scene);
		PX2::Movable *GetHelpScene ();

		PX2::Renderer *GetRenderer ();
		PX2::Camera *GetCamera ();

		PX2Editor::SceneNodeCtrl *GetSceneNodeCtrl () { return mSceneNodeCtrl; }

		static std::string ViewTypeString[RenderViewWindow::VT_MAX_TYPE];

	protected:
		DECLARE_EVENT_TABLE()

		void CreateToolbar ();
		void CreatePopupMenu ();
		void SetCameraFrameAxis (); //< 切换相机透视模式时调用
		void SetAxisTop ();
		void SetAxisFront ();
		void SetAxisLeft ();
		void SetAxisPerspective ();
		void UpdateCameraOrthorFrame (); // 当size改变时，frame需要调整
		void RegenGridGeometry ();
		void Update ();
		void Draw ();

		wxTimer mTimer;
		bool mInited;
		int mWindowIndex;
		POINT mMouseDragBefore;
		bool mActive;
		bool mLeftDown;
		bool mMiddleDown;
		bool mRightDown;
		bool mRightDownOnMotion;
		std::string mWindowTitle;
		int mXPosition, mYPosition, mWidth, mHeight;
		wxPoint mLastMousePoint;

//#ifdef PX2_USE_DX9
		PX2::RendererInput mInput;
//#endif
		PX2::Texture::Format mColorFormat;
		PX2::Texture::Format mDepthStencilFormat;
		int mNumMultisamples;
		PX2::Renderer* mRenderer;
		PX2::CameraPtr mCamera;
		bool mCameraNodesTargetted;

		ViewType mViewType;
		ViewDetail mViewDetail;
		wxToolBar *mToolbar;
		wxMenu *mViewOptionsPopupMenu;
		wxChoice *mViewChoice;
		PX2::Float4 mBackGroundColor;
		bool mExpanded;
		PX2::WirePropertyPtr mOverrideWireProperty;

		wxMenu *mEditMenu;

		// Grid Scene
		PX2::Culler mGridCuller;
		PX2::NodePtr mGridScene;
		PX2::VertexFormatPtr mGridVFormat;
		PX2::MaterialPtr mGridMaterial;
		PX2::RenderablePtr mGrid;
		PX2::VertexBufferPtr mVBGridAxis;
		PX2::VertexBufferAccessor mGridAxisAssessor;
		PX2::RenderablePtr mGridAxis;
		PX2::Float4 mBlack;
		PX2::Float4 mRed;
		PX2::Float4 mGreen;
		PX2::Float4 mBlue;
		PX2::Float4 mGray;
		bool mShowGrid;

		// Ctrl Scene;
		PX2::Culler mCtrlCuller;
		PX2::NodePtr mCtrlScene;
		PX2::DepthPropertyPtr mOverWriteDepth;

		// Ctrls
		PX2Editor::SceneNodeCtrl *mSceneNodeCtrl;

		// Scene
		PX2::Culler mCuller;
		PX2::MovablePtr mGraphicsScene;

		// HelpScene
		PX2::Culler mHelpSceneCuller;
		PX2::MovablePtr mHelpScene;
	};

#include "PX2RenderViewWindow.inl"

}

#endif