/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIAnimPicBox.hpp
*
*/

#ifndef PX2UIANIMPICBOX_HPP
#define PX2UIANIMPICBOX_HPP

#include "PX2UIPicBox.hpp"
#include "PX2UIAnimPicBoxControl.hpp"

namespace PX2
{

	class UIAnimPicBoxEle
	{
	public:
		UIAnimPicBoxEle ();
		~UIAnimPicBoxEle ();

		int Index;
		Float2 UV0;
		Float2 UV1;
		Float2 UV2;
		Float2 UV3;
		Texture2DPtr Tex;
	};

	class UIAnimPicBox : public UIPicBox
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(UIAnimPicBox);

	public:
		UIAnimPicBox ();
		virtual ~UIAnimPicBox ();

		UIAnimPicBoxControl *GetAPBCtrl ();

		void Play ();

		bool SetFrameTexPack (const std::string &filename);
		const std::string &GetFrameTexPack () const;
		bool AddFrameTex (const std::string &filename);

		void ClearFrames();
		int GetNumFrames ();

		void SetIntervalTime (float seconds);
		float GetIntervalTime ();

		Movable *GetAsMovable ();

public_internal:
		void SetActiveIndex (int index);
		int GetActiveIndex ();

	protected:
		UIAnimPicBoxControlPtr mAPBCtrl;

		std::string mFrameTexPack;		
		float mIntervalTime;
		int mActiveIndex;
		std::vector<UIAnimPicBoxEle> mElements;
	};

	PX2_REGISTER_STREAM(UIAnimPicBox);
	typedef Pointer0<UIAnimPicBox> UIAnimPicBoxPtr;
#include "PX2UIAnimPicBox.inl"

}

#endif