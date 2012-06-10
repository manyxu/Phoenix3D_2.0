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

#include "PX2EditorPrerequisites.hpp"
using namespace PX2;

WX_PG_DECLARE_VARIANT_DATA(wxAPoint3VariantData, APoint, wxPG_NO_DECL)

class wxAPoint3Property : public wxPGProperty
{
	WX_PG_DECLARE_PROPERTY_CLASS(wxAPoint3Property)
public:

	wxAPoint3Property (const wxString& label = wxPG_LABEL,
		const wxString& name = wxPG_LABEL,
		const PX2::APoint &value = PX2::APoint());
	virtual ~wxAPoint3Property();

	WX_PG_DECLARE_PARENTAL_METHODS()

protected:
};

WX_PG_DECLARE_VARIANT_DATA(wxFloat3VariantData, Float3, wxPG_NO_DECL)

class wxFloat3Property : public wxPGProperty
{
	WX_PG_DECLARE_PROPERTY_CLASS(wxFloat3Property)
public:

	wxFloat3Property (const wxString& label = wxPG_LABEL,
		const wxString& name = wxPG_LABEL,
		const PX2::Float3 &value = PX2::Float3(0.0f, 0.0f, 0.0f));
	virtual ~wxFloat3Property();

	WX_PG_DECLARE_PARENTAL_METHODS()

protected:
};

#endif