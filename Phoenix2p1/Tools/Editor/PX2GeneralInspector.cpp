/*
*
* ÎÄ¼þÃû³Æ	£º	PX2GeneralInspector.cpp
*
*/

#include "PX2GeneralInspector.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(GeneralInspector, wxScrolledWindow)
	EVT_SIZE(GeneralInspector::OnSize)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
GeneralInspector::GeneralInspector (wxWindow *parent)
:
wxScrolledWindow(parent),
mGeneralPropertyGrid(0),
mType(0),
mInitSized(false)
{
	mGeneralPropertyGrid = new GeneralPropertyGrid(this);
}
//-----------------------------------------------------------------------------
GeneralInspector::~GeneralInspector ()
{
}
//-----------------------------------------------------------------------------
void GeneralInspector::OnSize(wxSizeEvent& e)
{
	if (mGeneralPropertyGrid)
	{
		mGeneralPropertyGrid->SetSize(e.GetSize());
	}
}
//-----------------------------------------------------------------------------
void GeneralInspector::SetType (int type)
{
	mType = type;

	mGeneralPropertyGrid->SetType(type);
}
//-----------------------------------------------------------------------------
GeneralInspector::GeneralInspector ()
{
}
//-----------------------------------------------------------------------------