/*
*
* ÎÄ¼þÃû³Æ	£º	PX2MVCViewLogWindow.cpp
*
*/

#include "PX2ViewLogWindow.hpp"
using namespace PX2Editor;

IMPLEMENT_DYNAMIC_CLASS(PX2Editor::ViewLogWindow, wxPanel)
//----------------------------------------------------------------------------
ViewLogWindow::ViewLogWindow()
: 
wxPanel(NULL, -1), mTextCtrl(0)
{
}	
//----------------------------------------------------------------------------
ViewLogWindow::ViewLogWindow(wxWindow* parent)
: wxPanel(parent, -1), mTextCtrl(0)
{

	this->SetSizer(new wxBoxSizer(wxVERTICAL));

	mTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, 
		wxDefaultSize, wxTE_MULTILINE|wxVSCROLL|wxTE_READONLY);

	this->GetSizer()->Add(mTextCtrl, 1, wxEXPAND, 0);
	this->GetSizer()->Fit(this);
}
//----------------------------------------------------------------------------
ViewLogWindow::~ViewLogWindow()
{
}
//----------------------------------------------------------------------------
void ViewLogWindow::AddMessage (const wxString *msg)
{
	wxDateTime now = wxDateTime::Now();
	mTextCtrl->AppendText(now.FormatTime());
	mTextCtrl->AppendText(wxT(" "));
	mTextCtrl->AppendText(*msg);
	mTextCtrl->AppendText(wxT("\n"));
}
//----------------------------------------------------------------------------