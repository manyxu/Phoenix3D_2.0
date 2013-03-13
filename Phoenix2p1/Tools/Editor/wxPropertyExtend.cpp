/*
*
* ÎÄ¼þÃû³Æ	£º	SystemManager.cpp
*
*/

#include "wxPropertyExtend.hpp"

//-----------------------------------------------------------------------------
WX_PG_IMPLEMENT_VARIANT_DATA_DUMMY_EQ(APoint)
//-----------------------------------------------------------------------------
// wxAPoint3VariantData
//-----------------------------------------------------------------------------
WX_PG_IMPLEMENT_PROPERTY_CLASS(wxAPoint3Property, wxPGProperty, APoint,
	const APoint&, TextCtrl);
//-----------------------------------------------------------------------------
wxAPoint3Property::wxAPoint3Property (const wxString &label, const wxString &name,
	const APoint &value)
	:
wxPGProperty(label, name)
{
	SetValue(WXVARIANT(value));
	AddPrivateChild(new wxFloatProperty(wxT("X"),wxPG_LABEL,value.X()));
	AddPrivateChild(new wxFloatProperty(wxT("Y"),wxPG_LABEL,value.Y()));
	AddPrivateChild(new wxFloatProperty(wxT("Z"),wxPG_LABEL,value.Z()));
}
//-----------------------------------------------------------------------------
wxAPoint3Property::~wxAPoint3Property() 
{
}
//-----------------------------------------------------------------------------
void wxAPoint3Property::RefreshChildren()
{
	if (!GetChildCount())
		return;

	APoint &point = APointRefFromVariant(m_value);
	Item(0)->SetValue(point.X());
	Item(1)->SetValue(point.Y());
	Item(2)->SetValue(point.Z());
}
//-----------------------------------------------------------------------------
wxVariant wxAPoint3Property::ChildChanged(wxVariant &thisValue, int childIndex, 
	wxVariant &childValue ) const
{
	APoint &point = APointRefFromVariant(thisValue);
	switch (childIndex)
	{
	case 0:
		point.X() = (float)childValue.GetDouble();
		break;
	case 1: 
		point.Y() = (float)childValue.GetDouble();
		break;
	case 2: 
		point.Z() = (float)childValue.GetDouble();
		break;
	}

	wxVariant newVariant;
	newVariant << point;
	return newVariant;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
WX_PG_IMPLEMENT_VARIANT_DATA_DUMMY_EQ(Float3)
	//-----------------------------------------------------------------------------
	// wxFloat3Property
	//-----------------------------------------------------------------------------
	WX_PG_IMPLEMENT_PROPERTY_CLASS(wxFloat3Property, wxPGProperty, Float3,
	const Float3&, TextCtrl);
//-----------------------------------------------------------------------------
wxFloat3Property::wxFloat3Property (const wxString &label, const wxString &name,
	const Float3 &value)
	:
wxPGProperty(label, name)
{
	SetValue(WXVARIANT(value));
	AddPrivateChild(new wxFloatProperty(wxT("X"),wxPG_LABEL,value[0]));
	AddPrivateChild(new wxFloatProperty(wxT("Y"),wxPG_LABEL,value[1]));
	AddPrivateChild(new wxFloatProperty(wxT("Z"),wxPG_LABEL,value[2]));
}
//-----------------------------------------------------------------------------
wxFloat3Property::~wxFloat3Property() 
{
}
//-----------------------------------------------------------------------------
void wxFloat3Property::RefreshChildren()
{
	if (!GetChildCount())
		return;

	Float3 &value = Float3RefFromVariant(m_value);
	Item(0)->SetValue(value[0]);
	Item(1)->SetValue(value[1]);
	Item(2)->SetValue(value[2]);
}
//-----------------------------------------------------------------------------
wxVariant wxFloat3Property::ChildChanged(wxVariant &thisValue, int childIndex, 
	wxVariant &childValue ) const
{
	Float3 &value = Float3RefFromVariant(thisValue);
	switch (childIndex)
	{
	case 0:
		value[0] = (float)childValue.GetDouble();
		break;
	case 1: 
		value[1] = (float)childValue.GetDouble();
		break;
	case 2: 
		value[2] = (float)childValue.GetDouble();
		break;
	}

	wxVariant newVariant;
	newVariant << value;
	return newVariant;
}
//-----------------------------------------------------------------------------