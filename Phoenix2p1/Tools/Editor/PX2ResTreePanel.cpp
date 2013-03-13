/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ResTreeWindow.cpp
*
*/

#include "PX2ResTreePanel.hpp"
#include "PX2LanguageManager.hpp"
using namespace PX2Editor;
using namespace PX2;

#define ID_RESTREE_UPDATE wxID_HIGHEST + 4002

BEGIN_EVENT_TABLE(ResTreePanel, wxPanel)
	EVT_MENU(ID_RESTREE_UPDATE, ResTreePanel::OnUpdate)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
ResTreePanel::ResTreePanel (wxWindow *parent)
:
wxPanel(parent, wxID_ANY),
mResTreeBar(0),
mResTree(0)
{
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	mResTreeBar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxTB_FLAT); 
	mResTreeBar->AddTool(ID_RESTREE_UPDATE,
		wxBitmap(wxT("ToolRes/icons/resTreeUpdate.png"), wxBITMAP_TYPE_PNG),
		PX2_LM.GetValue("ResTreeUpdate"));
	mResTreeBar->Realize(); 

	bSizer10->Add( mResTreeBar, 1, wxEXPAND, 0);

	bSizer9->Add( bSizer10, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 0);

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	mResTree = new ResTree( this);
	bSizer11->Add( mResTree, 1, wxALL|wxEXPAND, 2);

	bSizer9->Add( bSizer11, 1, wxEXPAND, 0);

	this->SetSizer( bSizer9 );
	this->Layout();
}
//-----------------------------------------------------------------------------
ResTreePanel::~ResTreePanel ()
{
}
//-----------------------------------------------------------------------------
ResTree *ResTreePanel::GetResTree ()
{
	return mResTree;
}
//-----------------------------------------------------------------------------
void ResTreePanel::OnUpdate (wxCommandEvent &e)
{
	if (mResTree)
		mResTree->UpdateOnPath("Data/");
}
//-----------------------------------------------------------------------------