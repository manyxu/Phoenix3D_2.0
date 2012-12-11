/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Property.cpp
*
*/

#include "PX2Property.hpp"
#include "PX2PropertyPage.hpp"
#include "wxPropertyExtend.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
// wxStringButtonEditor
//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC_CLASS(wxStringButtonEditor, wxPGTextCtrlEditor)
//-----------------------------------------------------------------------------
wxStringButtonEditor::wxStringButtonEditor()
:
mProperty(0),
mButtonDownCallback(0)
{
}
//-----------------------------------------------------------------------------
wxStringButtonEditor::wxStringButtonEditor(Property *prop)
:
mProperty(prop),
mButtonDownCallback(0)
{
}
//-----------------------------------------------------------------------------
wxStringButtonEditor::~wxStringButtonEditor() 
{
}
//-----------------------------------------------------------------------------
wxPGWindowList wxStringButtonEditor::CreateControls( wxPropertyGrid* propGrid,
							 wxPGProperty* property,
							 const wxPoint& pos,
							 const wxSize& sz ) const
{
	wxPGMultiButton* buttons = new wxPGMultiButton( propGrid, sz );

	buttons->Add( wxT("Use") );

	wxPGWindowList wndList = wxPGTextCtrlEditor::CreateControls
		( propGrid, property, pos, buttons->GetPrimarySize() );

	buttons->Finalize(propGrid, pos);

	wndList.SetSecondary( buttons );

	return wndList;
}
//-----------------------------------------------------------------------------
bool wxStringButtonEditor::OnEvent( wxPropertyGrid* propGrid,
										wxPGProperty* property,
										wxWindow* ctrl,
										wxEvent& event ) const
{
	if ( event.GetEventType() == wxEVT_COMMAND_BUTTON_CLICKED )
	{
		wxPGMultiButton* buttons = (wxPGMultiButton*) propGrid->GetEditorControlSecondary();

		if ( event.GetId() == buttons->GetButtonId(0) )
		{
			if (mButtonDownCallback)
				mButtonDownCallback (mProperty);

			return false;
		}
	}

	return wxPGTextCtrlEditor::OnEvent(propGrid, property, ctrl, event);
}
//-----------------------------------------------------------------------------
void wxStringButtonEditor::SetButtonDownCallback (ButtonDownCallback fun)
{
	mButtonDownCallback = fun;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Property
//-----------------------------------------------------------------------------
bool Property::msRegisteredStrongButton = false;
//-----------------------------------------------------------------------------
Property::Property (PropertyPage *parent, std::string name, PropertyType type, 
					void *data, bool enable)
:
mParent(parent),
mName(name),
mType(type),
mData(data),
mEnable(enable),
mProperty(0),
mStringButtonEditor(0),
mButtonDownCallback(0)
{
	if (PT_CATEGORY == type)
	{
		 mProperty = new wxPropertyCategory(name.c_str(), wxPG_LABEL);

		 mParent->mPage->Append(mProperty);
	}
	else if (PT_INT == type)
	{
		long value = 0;
		if (mData)
			value = *((long*)mData);
		mProperty = new wxIntProperty(name.c_str(), wxPG_LABEL, value);

		mParent->mPage->Append(mProperty);
	}
	else if (PT_FLOAT == type)
	{
		double value = 0.0;
		if (mData)
			value = (double)(*((float*)mData));
		mProperty = new wxFloatProperty(name.c_str(), wxPG_LABEL, value);

		mParent->mPage->Append(mProperty);
	}
	else if (PT_BOOL == type)
	{
		bool value = false;
		if (mData)
			value = *((bool*)mData);
		mProperty = new wxBoolProperty(name.c_str(), wxPG_LABEL, value);

		mParent->mPage->Append(mProperty);
	}
	else if (PT_BOOLCHECK == type)
	{
		bool value = false;
		if (mData)
			value = *((bool*)mData);
		mProperty = new wxBoolProperty(name.c_str(), wxPG_LABEL, value);

		mParent->mPage->Append(mProperty);

		mParent->mPage->SetPropertyAttribute(name.c_str(),
			wxPG_BOOL_USE_CHECKBOX, true );
	}
	else if (PT_COLOR3FLOAT3 == type)
	{
		wxColour color;
		if (mData)
		{
			Float3 value = *((Float3*)mData);
			color.Set((unsigned char)(255*value[0]), (unsigned char)(255*value[1]),
				(unsigned char)(255*value[2]));
		}
		else
			color.Set(255, 255, 255);

		mProperty = new wxColourProperty(name.c_str(), wxPG_LABEL, color);

		mParent->mPage->Append(mProperty);
	}
	else if (PT_FLOAT3 == type)
	{
		Float3 value;

		if (mData)
		{
			value = *((Float3*)mData);
		}

		mProperty = new wxFloat3Property(name.c_str(), wxPG_LABEL, value);

		mParent->mPage->Append(mProperty);
	}
	else if (PT_STRING == type)
	{
		wxString value;
		if (mData)
		{
			value = wxString( (*((std::string*)data)).c_str() );
		}

		mProperty = new wxStringProperty(name.c_str(), wxPG_LABEL, value);

		mParent->mPage->Append(mProperty);
	}
	else if (PT_STRINGBUTTON == type)
	{
		wxString value;
		if (mData)
		{
			value = wxString( (*((std::string*)data)).c_str() );
		}

		mProperty = new wxStringProperty(name.c_str(), wxPG_LABEL, value);

		mParent->mPage->Append(mProperty);

		if (!msRegisteredStrongButton)
		{
			wxPropertyGrid::RegisterEditorClass(new wxStringButtonEditor());
			msRegisteredStrongButton = true;
		}

		mStringButtonEditor = new wxStringButtonEditor(this);
		mParent->mPage->SetPropertyEditor(name.c_str(), mStringButtonEditor);
	}

	parent->mProperties.push_back(this);

	if (mProperty)
		mProperty->Enable(mEnable);
}
//-----------------------------------------------------------------------------
Property::~Property ()
{
}
//-----------------------------------------------------------------------------
void Property::Enable (bool editable)
{
	if (mProperty)
		mProperty->Enable(editable);
}
//-----------------------------------------------------------------------------
bool Property::IsEnabled()
{
	if (mProperty)
		return mProperty->IsEnabled();

	return false;
}
//-----------------------------------------------------------------------------
void Property::SetValue (std::string val)
{
	if (mProperty)
	{
		mProperty->SetValue(wxVariant(val));
	}
}
//-----------------------------------------------------------------------------
std::string Property::GetAsString ()
{
	if (mProperty)
	{
		return mProperty->GetValue();
	}

	return "";
}
//-----------------------------------------------------------------------------
void Property::SetValue (bool val)
{
	if (mProperty)
	{
		mProperty->SetValue(wxVariant(val));
	}
}
//-----------------------------------------------------------------------------
bool Property::GetAsBool ()
{
	if (mProperty)
	{
		return mProperty->GetValue();
	}

	return "";
}
//-----------------------------------------------------------------------------
void Property::SetButtonDownCallback (ButtonDownCallback fun)
{
	mButtonDownCallback = fun;

	if (mStringButtonEditor)
		mStringButtonEditor->SetButtonDownCallback(fun);
}
//-----------------------------------------------------------------------------
void Property::OnChange (wxPropertyGridEvent &event)
{
	wxPGProperty *property = event.GetProperty();
	const wxString &name = event.GetPropertyName();
	std::string stdName = std::string(name);
	wxAny anyValue = property->GetValue();

	if (name != wxString(mName.c_str()))
		return;

	if (!mData)
		return;

	if (mType == PT_INT)
	{
		*((int*)mData) = wxANY_AS(anyValue, int);
	}
	else if (mType == PT_FLOAT)
	{
		double value = 0;
		value = wxANY_AS(anyValue, double);
		*((float*)mData) = (float)value;
	}
	else if (mType == PT_BOOL)
	{
		bool value =  wxANY_AS(anyValue, bool);
		*((bool*)mData) = value;
	}
	else if (mType == PT_BOOLCHECK)
	{
		bool value =  wxANY_AS(anyValue, bool);
		*((bool*)mData) = value;
	}
	else if (PT_COLOR3FLOAT3 == mType)
	{
		wxColor color =  wxANY_AS(anyValue, wxColor);

		Float3 float3Color((float)color.Red()/255.0f, (float)color.Green()/255.0f,
			(float)color.Blue()/255.0f);

		*((Float3*)mData) = float3Color;
	}
	else if (PT_FLOAT3 == mType)
	{
		//*((Float3*)mData) = Float3FromVariant(variant);
	}
	else if (mType == PT_STRING)
	{
		std::string value;
		value = wxANY_AS(anyValue, std::string);
		*((std::string*)mData) = value;
	}
}
//-----------------------------------------------------------------------------
void Property::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void Property::DoExecute (PX2::Event *event)
{
	PX2_UNUSED(event);
}
//-----------------------------------------------------------------------------
void Property::DoLeave ()
{

}
//-----------------------------------------------------------------------------
wxPGProperty *Property::GetWxProperty ()
{
	return mProperty;
}
//-----------------------------------------------------------------------------
wxColor Property::StringToColor (wxString strColor)
{
	std::string stdStrColor(strColor.GetData());
	std::string::size_type posK0 = stdStrColor.find_first_of("(");
	std::string::size_type posD0 = stdStrColor.find_first_of(",");
	std::string strRed = stdStrColor.substr(posK0+1, posD0-posK0-1);
	std::string::size_type posD1 = stdStrColor.find_last_of(",");
	std::string::size_type posK1 = stdStrColor.find_first_of(")");
	std::string strGreen = stdStrColor.substr(posD0+1, posD1-posD0-1);
	std::string strBlue = stdStrColor.substr(posD1+1, posK1-posD1);
	int red = atoi(strRed.c_str());
	int green = atoi(strGreen.c_str());
	int blue = atoi(strBlue.c_str());

	return wxColor((unsigned char)red, (unsigned char)green,
		(unsigned char)blue);
}
//-----------------------------------------------------------------------------