/*
*
* ÎÄ¼þÃû³Æ	£º	PX2CurveEditWindow.hpp
*
*/

#ifndef PX2CURVEEDITWINDOW_HPP
#define PX2CURVEEDITWINDOW_HPP

#include "PX2EditorPre.hpp"
#include "PX2UIFrame.hpp"

namespace PX2Editor
{

	class CurveEditWindow : public wxWindow, public PX2::EventHandler, public PX2::Singleton<CurveEditWindow>
	{
	public:
		CurveEditWindow (wxWindow *parent);
		~CurveEditWindow ();

		void OnSize(wxSizeEvent& e);
		void OnPaint(wxPaintEvent& e);
		void OnEnterWindow(wxMouseEvent& e);
		void OnLeaveWindow(wxMouseEvent& e);
		void OnTimer (wxTimerEvent& event);
		void OnLeftDown (wxMouseEvent& e);
		void OnLeftDoubleClick (wxMouseEvent& e);
		void OnLeftUp (wxMouseEvent& e);
		void OnMiddleDown (wxMouseEvent& e);
		void OnMiddleUp (wxMouseEvent& e);
		void OnMouseWheel (wxMouseEvent& e);
		void OnRightDown (wxMouseEvent& e);
		void OnRightUp (wxMouseEvent& e);
		void OnMotion (wxMouseEvent& e);

		void OnFitHor (wxCommandEvent &e);
		void OnFitVer (wxCommandEvent &e);
		void OnFitAll (wxCommandEvent &e);
		void OnFitSelect (wxCommandEvent &e);
		void OnPan (wxCommandEvent &e);
		void OnZoom (wxCommandEvent &e);
		void OnChangeInterpMode (wxCommandEvent &e);
		void OnFattenTangentsToAxis (wxCommandEvent &e);
		void OnStraightenTangents (wxCommandEvent &e);
		void OnSetInVal (wxCommandEvent &e);
		void OnSetOutVal (wxCommandEvent &e);
		void OnDelete (wxCommandEvent &e);
		void OnDeleteUICurveGroup (wxCommandEvent &e);
		void OnDeleteAllUICurveGroup (wxCommandEvent &e);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()
		void Initlize ();
		void DrawScene ();
		void ZoomCamera (float xDetal, float zDetal);
		void ZoomCameraTo (float xMax, float zMax);
		void RefreshGrid (PX2::Renderer *renderer, bool doScale);
		void FitViewHorizontally();
		void FitViewVertically();
		void FitViewToSelected();
		void FitViewToAll();
		void EnableInterps (bool enable);
		void UnToggleAllInterps ();
		void TrySelectCurveCtrlPoint (const wxPoint &pos);
		void ToggleInterp (PX2::InterpCurveMode mode);

		enum MoveMode
		{
			MM_PAN,
			MM_ZOOM,
			MM_MAX_MODE
		};
		MoveMode mMoveMode;

		bool mInited;

		wxToolBar *mToolBar;

		int mWidth, mHeight;
		int mLeftWidth;
		PX2::RendererInput mInput;
		PX2::Texture::Format mColorFormat;
		PX2::Texture::Format mDepthStencilFormat;
		int mNumMultisamples;
		PX2::Float4 mBackGroundColor;
		PX2::Renderer* mRenderer;

		PX2::VertexFormatPtr mVFormat;
		PX2::CameraPtr mCamera;
		PX2::NodePtr mScene;
		PX2::PolysegmentPtr mGridPoly;
		PX2::Culler mCuller;

		// ui
		PX2::UIFramePtr mEditorUI;

		wxTimer mTimer;

		// Grid
		float mUPerGrid;
		float mVPerGrid;

		bool mActive;
		bool mLeftDown;
		bool mLeftDownOnMotion;
		bool mMiddleDown;
		bool mRightDown;
		bool mRightDownOnMotion;
		wxPoint mRightDownMousePoint;
		float mRightDownRMax;
		float mRightDownUMax;
		wxPoint mLastMousePoint;
		float mPixelOverCamIn;
		float mPixelOverCamOut;
		float mXStart;
		float mXEnd;
		float mZStart;
		float mZEnd;

		struct FontStr
		{
			FontStr () 
			{
				x = 0;
				y = 0;
			}

			int x;
			int y;
			std::string str;
		};
		std::vector<FontStr> mFontStrs;

		wxMenu *mEditMenu;
		wxMenu *mEditCurveGroupMenu;
	};

}

#endif