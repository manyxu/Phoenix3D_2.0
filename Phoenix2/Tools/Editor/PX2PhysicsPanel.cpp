/*
*
* ÎÄ¼þÃû³Æ	£º	PX2MaterialPane.cpp
*
*/

#include "PX2PhysicsPanel.hpp"
#include "PX2ModelPhysicsPropertyGrid.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(PhysicsPanel, wxPanel)
	EVT_BUTTON(wxID_ANY, PhysicsPanel::OnButton)
END_EVENT_TABLE()

PhysicsPanel::PhysicsPanel (wxWindow *parent)
:
wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize( 243,200 ))
{
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxVERTICAL );

	mApply = new wxButton( this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer33->Add( mApply, 0, wxALL, 5 );

	bSizer32->Add( bSizer33, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxVERTICAL );

	mPropertyGrid = new ModelPhysicsPropertyGrid(this);
	bSizer34->Add( mPropertyGrid, 1, wxEXPAND, 5 );

	bSizer32->Add( bSizer34, 1, wxEXPAND, 5 );

	this->SetSizer( bSizer32 );
	this->Layout();
}
//-----------------------------------------------------------------------------
PhysicsPanel::~PhysicsPanel ()
{

}
//-----------------------------------------------------------------------------
void PhysicsPanel::OnButton (wxCommandEvent& event)
{

}
//-----------------------------------------------------------------------------
void PhysicsPanel::SetActor (PX2::Actor *actor)
{
	mActor = actor;

	mPropertyGrid->SetObject(mActor);
}
//-----------------------------------------------------------------------------
PhysicsPanel::PhysicsPanel ()
{

}
//-----------------------------------------------------------------------------