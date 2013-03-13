/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIView.hpp
*
*/

#ifndef PX2UIVIEW_HPP
#define PX2UIVIEW_HPP

#include "PX2UIPre.hpp"
#include "PX2Size.hpp"
#include "PX2Camera.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIPicBox.hpp"
#include "PX2Culler.hpp"
#include "PX2Renderer.hpp"

namespace PX2
{

	// Help to set camera
	class UIView
	{
	public:
		UIView (int id);
		~UIView ();

		int GetID ();

		void SetSize (float width, float height);
		void SetSize (const Sizef &size);
		const Sizef &GetSize () const;
		void SetWidth (float width);
		float GetWidth ();
		void SetHeight (float height);
		float GetHeight ();

		void SetRenderer(Renderer *renderer);
		Renderer *GetRenderer ();
		void SetMainFrame (UIFrame *frame);
		UIFrame *GetMainFrame ();
		Camera *GetCamera ();
		Culler &GetCuller ();
		std::vector<UIPicBoxPtr> &GetPickedPicBoxs ();

		void Update (double appSeconds, double elapsedSeconds);
		void ComputeVisibleSet ();

		void DoExecute (Event *event);

	protected:
		void OnSizeChange ();
		void DoPick (std::vector<UIPicBoxPtr> &vec, float x, float y,
			int pickInfo);

		int mID;
		Sizef mSize;
		CameraPtr mCamera;
		Renderer *mRenderer;
		UIFramePtr mUIMainFrame;
		Culler mCuller;
		std::vector<UIPicBoxPtr> mPickedPicBoxes;
	};

#include "PX2UIView.inl"
	typedef Pointer0<UIView> UIViewPtr;

}

#endif