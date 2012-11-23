/*
*
* ÎÄ¼þÃû³Æ	£º	PX2PreViewWindow.hpp
*
*/

#ifndef PX2PREVIEWWINDOW_HPP
#define PX2PREVIEWWINDOW_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class PreViewWindow : public wxWindow, public PX2::EventHandler
	{
	public:
		PreViewWindow ();
		PreViewWindow (wxWindow *parent);
		virtual ~PreViewWindow ();

		DECLARE_DYNAMIC_CLASS(PreViewWindow)
	
		void SetObject (PX2::Object *obj);

		void OnTimer (wxTimerEvent& event);
		void OnPaint(wxPaintEvent& e);

public_internal:
		void Initialize ();

	protected:
		DECLARE_EVENT_TABLE()

		void SetTexture (PX2::Texture2D *texture);
		void SetModel (PX2::Movable *object);
		void Update ();
		void DrawScene ();

		bool mInited;

		PX2::RendererInput mInput;
		PX2::Texture::Format mColorFormat;
		PX2::Texture::Format mDepthStencilFormat;
		int mNumMultisamples;
		PX2::Renderer* mRenderer;
		PX2::Float4 mBackGroundColor;
		
		int mWidth, mHeight;
		PX2::CameraPtr mCamera;
		PX2::VertexFormatPtr mVFormat;
		PX2::TriMeshPtr mScreenMesh;
		PX2::Texture2DMaterialPtr mPreViewMaterial;
		PX2::TexturePtr mPreViewTexture;
		PX2::CameraPtr mPreViewTextureCamera;

		PX2::MovablePtr mPreViewObject;

		// Scene
		PX2::Culler mCuller;
		PX2::MovablePtr mScene;
		PX2::Culler mCuller1;
		PX2::MovablePtr mScene1;

		wxTimer mPreViewTimer;
	};

}

#endif