/*
*
* 文件名称	：	PX2RenderViewWindow.hpp
*
*/

#ifndef PX2RENDERVIEWWINDOW_HPP
#define PX2RENDERVIEWWINDOW_HPP

#include "PX2EditorPre.hpp"
#include "PX2SceneNodeCtrl.hpp"
#include "PX2UIPicBox.hpp"

namespace PX2Editor
{

	class RenderViewWindow : public wxWindow, public PX2::EventHandler
	{
	public:
		RenderViewWindow ();
		RenderViewWindow (wxWindow *parent);
		virtual ~RenderViewWindow ();

		DECLARE_DYNAMIC_CLASS(RenderViewWindow)	

		void SetScene (PX2::Movable *scene);
		PX2::Movable *GetScene ();
		void SetHelpScene (PX2::Movable *scene);
		PX2::Movable *GetHelpScene ();
		PX2::Renderer *GetRenderer ();
		PX2::Camera *GetCamera ();
		SceneNodeCtrl *GetSceneNodeCtrl ();
		BoundCtrl *GetBoundCtrl ();

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
			VD_WIREFRAME,
			VD_SOLID,
			VD_TEXTURED
		};
		void SetViewDetail (ViewDetail viewDetail);
		ViewDetail GetViewDetail () const;

		void SetRenderMilliseconds (int ms);
		int GetRenderMilliseconds ();
		void SetCtrlMilliseconds (int ms);
		int GetCtrlMilliseconds ();
		void SetCameraSpeed (float moveSpeed);
		void GetCameraSpeed (float &moveSpeed);

		void OnTimer (wxTimerEvent& event);
		void OnSize (wxSizeEvent& e);
		void OnPaint(wxPaintEvent& e);
		void OnEnterWindow(wxMouseEvent& e);
		void OnLeaveWindow(wxMouseEvent& e);
		void OnLeftDown (wxMouseEvent& e);
		void OnLeftUp (wxMouseEvent& e);
		void OnMiddleDown (wxMouseEvent& e);
		void OnMiddleUp (wxMouseEvent& e);
		void OnMouseWheel (wxMouseEvent& e);
		void OnRightDown (wxMouseEvent& e);
		void OnRightUp (wxMouseEvent& e);
		void OnMotion (wxMouseEvent& e);

		void OnActorModel (wxCommandEvent& e);
		void OnActorLight_Direction (wxCommandEvent& e);
		void OnActorLight_Point (wxCommandEvent& e);
		void OnActorLight_Spot (wxCommandEvent& e);
		void OnActorSky (wxCommandEvent& e);
		void OnCreateBox (wxCommandEvent& e);
		void OnCreateSphere (wxCommandEvent& e);
		void OnCreateEffect (wxCommandEvent& e);
		void OnCreateUIFrame (wxCommandEvent& e);
		void OnCreateUIPicBox (wxCommandEvent& e);
		void OnCreateUIAnimPixBox (wxCommandEvent& e);
		void OnCreateUIStaticText (wxCommandEvent& e);
		void OnCreateUIButton (wxCommandEvent& e);
		void OnCloneShare (wxCommandEvent& e);
		void OnCloneData (wxCommandEvent& e);

		void ZoomCamera (float zoom);
		void PanCamera (const float &horz, const float &vert); //< 透视角度，上下左右移动，其他视角和MoveCamera一样
		void MoveCamera (const float &horz, const float &vert); //< 透视角度，沿着视线方向移动
		void RolateCamera (const float &horz, const float &vert);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

public_internal:
		std::pair<float, float> StartMouseDrag(wxMouseEvent& e);
		void EndMouseDrag(wxMouseEvent& e);

public_internal:
		bool Initlize ();

	protected:
		DECLARE_EVENT_TABLE()
		void UpdateProjectTrans ();
		void UpdateProjectRange ();
		void AdjustUICameraPercent ();
		void CreateEditMenu ();
		void CreateGridGeometry ();
		void SetAxisPerspective ();
		void Update (double detalSeconds);
		void CamMoveUpdate (double detalSeconds);
		void DrawScene ();
		void CameraChangedSimplyTerrain ();

		bool mInited;

		PX2::Float4 mBlack, mRed, mGreen, mBlue, mGray;
		int mWidth, mHeight;
		PX2::Culler mCuller;
		PX2::MovablePtr mScene;
		PX2::CameraPtr mCamera;
		PX2::Texture::Format mColorFormat;
		PX2::Texture::Format mDepthStencilFormat;
		PX2::Float4 mBackGroundColor;
		int mNumMultisamples;
		PX2::RendererInput mRendererInput;
		PX2::Renderer *mRenderer;
		ViewType mViewType;
		ViewDetail mViewDetail;

		PX2::WirePropertyPtr mSceneWireOverride;
		PX2::WirePropertyPtr mUIWireOverride;

		wxTimer mRenderTimer;
		int mRenderMilliseconds;
		wxTimer mCtrlTimer;
		int mCtrlMilliseconds;
		float mCameraMoveSpeed;
		float mCurCameraMoveSpeed_W;
		float mCurCameraMoveSpeed_S;
		float mCurCameraMoveSpeed_A;
		float mCurCameraMoveSpeed_D;

		PX2::DepthPropertyPtr mOverWriteDepth;

		// Grid
		PX2::Culler mGridCuller;
		PX2::NodePtr mGridScene;
		PX2::VertexFormatPtr mGridVFormat;
		PX2::MaterialPtr mGridMaterial;
		PX2::RenderablePtr mGrid;
		PX2::RenderablePtr mGridAxis;
		PX2::VertexBufferPtr mVBGridAxis;
		PX2::VertexBufferAccessor mGridAxisAssessor;
		bool mShowGrid;

		// HelpScene
		PX2::Culler mHelpCuller;
		PX2::MovablePtr mHelpScene;

		// Ctrl
		PX2::Culler mCtrlCuller;
		PX2::NodePtr mCtrlScene;
		SceneNodeCtrl *mSceneNodeCtrl;
		BoundCtrl *mBoundCtrl;

		bool mActive;
		bool mLeftDown;
		bool mMiddleDown;
		bool mRightDown;
		bool mRightDownOnMotion;
		wxPoint mLastMousePoint;

		// View
		wxMenu *mEditMenu;
		PX2::Float2 mRightDownScreenPos;

		// splash
		PX2::UIPicBoxPtr mPicBox;

		// Project Range
		PX2::VertexFormatPtr mProjRangeVFormat;
		PX2::VertexBufferPtr mProjRangeVBuffer;
		PX2::PolysegmentPtr mProjRangeSegment;
	};

#include "PX2RenderViewWindow.inl"

}

#endif