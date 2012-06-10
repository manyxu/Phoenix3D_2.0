/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2TextureConvertPanel.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2TEXTURECONVERTPANEL_HPP
#define PX2TEXTURECONVERTPANEL_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class TextureConvertPane : public wxPanel
	{
	public:
		TextureConvertPane (wxWindow *parent);

		void OnButton (wxCommandEvent& event);
		void OnSize(wxSizeEvent& e);

	protected:
		TextureConvertPane ();

		wxButton* mAdd;
		wxButton* mRemove;
		wxButton* mClear;
		wxListBox* mTextureList;
		wxCheckBox* mDDSKC;
		wxButton* mConvert;

		DECLARE_EVENT_TABLE();
	};

}

#endif