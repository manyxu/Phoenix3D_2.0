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
		void OnPaint (wxPaintEvent& e);
		void OnSize (wxSizeEvent& e);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

public_internal:
		void Initlize ();

		enum PreViewType
		{
			PVT_NONE,
			PVT_TEXTURE,
			PVT_MODEL,
			PVT_MAX_TYPE
		};

	protected:
		DECLARE_EVENT_TABLE()

		void SetTexture (PX2::Texture2D *texture);
		void SetModel (PX2::Movable *object);
		void Update ();
		void DrawScene ();

		bool mInited;

		int mWidth, mHeight;
		PX2::RendererInput mInput;
		PX2::Texture::Format mColorFormat;
		PX2::Texture::Format mDepthStencilFormat;
		int mNumMultisamples;
		PX2::Float4 mBackGroundColor;
		PX2::Renderer* mRenderer;
		
		PreViewType mPreViewType;
		PX2::VertexFormatPtr mVFormat;
		PX2::TriMeshPtr mScreenMesh;
		PX2::Texture2DMaterialPtr mPreViewMaterial;
		PX2::TexturePtr mPreViewTexture;
		PX2::CameraPtr mPreViewTextureCamera;
		PX2::MovablePtr mPreViewObject;
		PX2::CameraPtr mCamera;

		// Scene
		PX2::Culler mCuller;
		PX2::MovablePtr mScene;
		PX2::Culler mCuller1;
		PX2::MovablePtr mScene1;

		wxTimer mPreViewTimer;
	};

}

#endif