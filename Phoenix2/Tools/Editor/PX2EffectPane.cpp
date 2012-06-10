/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectPane.cpp
*
*/

#include "PX2EffectPane.hpp"
#include "PX2EffectPropertyGrid.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(PX2Editor::EffectPanel, wxPanel)
BEGIN_EVENT_TABLE(EffectPanel, wxPanel)
	EVT_SIZE(EffectPanel::OnSize)
END_EVENT_TABLE()

EffectPanel::EffectPanel (wxWindow *parent)
:
wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize( 243,300 ))
{
	wxBoxSizer* sizer;
	sizer = new wxBoxSizer( wxVERTICAL );
	sizer->SetMinSize( wxSize( -1,200 ) ); 

	// propertygrid
	mPropGrid = new EffectPropertyGrid(this);
	PX2::EventWorld::GetSingleton().ComeIn(mPropGrid);
	sizer->Add( mPropGrid, 1, wxALL|wxEXPAND, 5 );

	this->SetSizer(sizer);

	this->Layout();
}
//-----------------------------------------------------------------------------
EffectPanel::~EffectPanel ()
{

}
//-----------------------------------------------------------------------------
void EffectPanel::OnSize (wxSizeEvent &e)
{
	wxPanel::OnSize(e);
}
//-----------------------------------------------------------------------------
EffectPanel::EffectPanel ()
{

}
//-----------------------------------------------------------------------------