/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EMFloat3Property.cpp
*
*/

#include "PX2EMFloat3Property.hpp"
#include "PX2PropertyPage.hpp"
#include "wxPropertyExtend.hpp"
using namespace PX2Editor;
using namespace PX2;

EMFloat3Property::EMFloat3Property (PropertyPage *parent,
	std::string name, InterpCurvePointFloat3 *point,
	bool isForInit)
	:
Property(parent, name, Property::PT_EMFLOAT3, 0),
	mPropertyInVal(0),
	mPropertyOutVal(0),
	mPropertyArriveTangent(0),
	mPropertyLeaveTangent(0),
	mInterpMode(0),
	mPoint(point),
	mIsForInit(isForInit)
{
	mProperty = parent->mPage->Append(new wxStringProperty(
		name, name, wxT("<composed>")) );

	if (!mIsForInit)
	{
		mPropertyInVal = parent->mPage->AppendIn(mProperty,
			new wxFloatProperty(wxT("InVal"), wxT("InVal"),
			double(mPoint->InVal)) );

		mPropertyOutVal = parent->mPage->AppendIn(mProperty,
			new wxFloat3Property(wxT("OutVal"), wxT("OutVal"), 
			mPoint->OutVal) );

		mPropertyArriveTangent = parent->mPage->AppendIn(mProperty,
			new wxFloat3Property(wxT("ArriveTangent"), wxT("ArriveTangent"),
			mPoint->ArriveTangent) );

		mPropertyLeaveTangent = parent->mPage->AppendIn(mProperty,
			new wxFloat3Property(wxT("OutTangent"), wxT("OutTangent"), 
			mPoint->LeaveTangent) );

		wxArrayString labels;
		labels.push_back(ICMToString(ICM_LINEAR));
		labels.push_back(ICMToString(ICM_CONSTANT));
		labels.push_back(ICMToString(ICM_CURVE_AUTO));
		labels.push_back(ICMToString(ICM_CURVE_AUTOCLAMPED));
		labels.push_back(ICMToString(ICM_CURVE_USER));
		labels.push_back(ICMToString(ICM_CURVE_BREAK));
		wxArrayInt arrayInt;
		arrayInt.push_back(ICM_LINEAR);
		arrayInt.push_back(ICM_CONSTANT);
		arrayInt.push_back(ICM_CURVE_AUTO);
		arrayInt.push_back(ICM_CURVE_AUTOCLAMPED);
		arrayInt.push_back(ICM_CURVE_USER);
		arrayInt.push_back(ICM_CURVE_BREAK);
		mInterpMode = parent->mPage->AppendIn(mProperty, 
			new wxEnumProperty(wxT("InterpMode"), wxT("InterpMode"), labels, 
			arrayInt, (int)(mPoint->InterpMode)));
	}
	else
	{
		mPropertyOutVal = parent->mPage->AppendIn(mProperty,
			new wxFloat3Property(wxT("OutVal"), wxT("OutVal"), 
			mPoint->OutVal) );
	}
}
//-----------------------------------------------------------------------------
EMFloat3Property::~EMFloat3Property ()
{
}
//-----------------------------------------------------------------------------
void EMFloat3Property::OnChange (wxPropertyGridEvent &event)
{
	wxPGProperty *prop = event.GetProperty();
	const wxString &wxName = event.GetPropertyName();
	wxVariant var = prop->GetValue();

	if (var.IsNull())
		return;

	if (mPropertyInVal == prop)
	{
		float fValue = (float)(var.GetDouble());

		mPoint->InVal = fValue;

		if (mPropertyInVal)
			mPropertyInVal->SetValue(fValue);
	}
	else if (mPropertyOutVal == prop)
	{
		mPoint->OutVal = Float3RefFromVariant(var);
	}
	else if (mPropertyArriveTangent == prop)
	{
		mPoint->ArriveTangent = Float3RefFromVariant(var);
	}
	else if (mPropertyLeaveTangent == prop)
	{
		mPoint->LeaveTangent = Float3RefFromVariant(var);
	}
	else if (mInterpMode == prop)
	{
		int val = var.GetInteger();
		mPoint->InterpMode = (InterpCurveMode)val;
	}
}
//-----------------------------------------------------------------------------
void EMFloat3Property::DoEnter ()
{
}
//-----------------------------------------------------------------------------
void EMFloat3Property::DoExecute (PX2::Event *event)
{
}
//-----------------------------------------------------------------------------
void EMFloat3Property::DoLeave ()
{
}
//-----------------------------------------------------------------------------