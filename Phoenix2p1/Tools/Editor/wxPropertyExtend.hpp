/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	wxPropertyExtend.hpp
*
* 版本		:	1.0 (2011/07/01)
*
* 作者		：	more
*
*/

#ifndef WXPROPERTYEXTEND_HPP
#define WXPROPERTYEXTEND_HPP

#include "PX2EditorPre.hpp"
using namespace PX2;

WX_PG_DECLARE_VARIANT_DATA(APoint)
class wxAPoint3Property : public wxPGProperty
{
	WX_PG_DECLARE_PROPERTY_CLASS(wxAPoint3Property)
public:

	wxAPoint3Property (const wxString& label = wxPG_LABEL,
		const wxString& name = wxPG_LABEL,
		const PX2::APoint &value = PX2::APoint());
	virtual ~wxAPoint3Property();

	virtual wxVariant ChildChanged( wxVariant& thisValue,
		int childIndex, wxVariant& childValue ) const;
	virtual void RefreshChildren();
};

WX_PG_DECLARE_VARIANT_DATA(Float3)
class wxFloat3Property : public wxPGProperty
{
	WX_PG_DECLARE_PROPERTY_CLASS(wxFloat3Property)
public:

	wxFloat3Property (const wxString& label = wxPG_LABEL,
		const wxString& name = wxPG_LABEL,
		const PX2::Float3 &value = PX2::Float3(0.0f, 0.0f, 0.0f));
	virtual ~wxFloat3Property();

	virtual wxVariant ChildChanged( wxVariant& thisValue,
		int childIndex, wxVariant& childValue ) const;
	virtual void RefreshChildren();
};

#endif