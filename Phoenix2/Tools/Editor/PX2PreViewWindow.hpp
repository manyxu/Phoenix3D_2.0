/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2PreViewWindow.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2PREPREVIEWWINDOW_HPP
#define PX2PREPREVIEWWINDOW_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class PreViewWindow : public wxWindow, public PX2::EventHandler
	{
	public:
		PreViewWindow ();
		PreViewWindow (wxWindow *parent);
		virtual ~PreViewWindow ();

		DECLARE_DYNAMIC_CLASS(PreViewWindow)

		void Initialize ();

		enum PreViewType
		{
			PVT_NONE,
			PVT_TEXTURE,
			PVT_MODEL,
			PVT_MAX_TYPE
		};
		
		// Set
		void SetObject (PX2::Object *obj);

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
		void OnWireframeClicked(wxCommandEvent& e);
		void OnHiddenLineClicked(wxCommandEvent& e);
		void OnShadedClicked(wxCommandEvent& e);
		void OnTexturedClicked(wxCommandEvent& e);
		void OnMouseCaptureLost(wxMouseCaptureLostEvent& e);
		void OnViewTypeCommand (wxCommandEvent& e);
		void OnFullFour (wxCommandEvent& e);
		void OnStageGrid (wxCommandEvent& e);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

		void OnTimer (wxTimerEvent& event);

		PX2::Renderer *GetRenderer ();
		PX2::Camera *GetCamera ();

	protected:
		DECLARE_EVENT_TABLE()

		void SetTexture (PX2::Texture2D *texture);
		void SetModel (PX2::Movable *object);
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
		PX2::Float4 mBackGroundColor;
		bool mCameraNodesTargetted;

		PX2::CameraPtr mCamera;
		PX2::CameraPtr mPreViewTextureCamera;
		PX2::VertexFormatPtr mVFormat;
		PX2::TriMeshPtr mScreenMesh;
		PX2::Texture2DMaterialPtr mPreViewMaterial;
		PX2::TexturePtr mPreViewTexture;

		PX2::MovablePtr mPreViewObject;
		PreViewType mPreViewType;

		// Scene
		PX2::Culler mCuller;
		PX2::MovablePtr mGraphicsScene;
		PX2::Culler mCuller1;
		PX2::MovablePtr mScene1;
	};

#include "PX2PreViewWindow.inl"

}

#endif