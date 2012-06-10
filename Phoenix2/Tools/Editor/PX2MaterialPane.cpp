/*
*
* ÎÄ¼þÃû³Æ	£º	PX2MaterialPane.cpp
*
*/

#include "PX2MaterialPane.hpp"
#include "PX2MaterialPropertyGrid.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(MaterialPanel, wxPanel)
	EVT_BUTTON(wxID_ANY, MaterialPanel::OnButton)
	EVT_CHOICE(wxID_ANY, MaterialPanel::OnMaterialChoose)
END_EVENT_TABLE()

MaterialPanel::MaterialPanel (wxWindow *parent)
:
wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize( 243,300 )),
mMaterialGrid(0)
{
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText *staticText12 = new wxStaticText( this, wxID_ANY, wxT("Material"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText12->Wrap( -1 );
	bSizer31->Add( staticText12, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxString m_choice2Choices[] = { wxT("VertexColor4"), wxT("Texture2D") };
	int m_choice2NChoices = sizeof( m_choice2Choices ) / sizeof( wxString );
	mMaterialChoose = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice2NChoices, m_choice2Choices, 0 );
	mMaterialChoose->SetSelection( 0 );
	bSizer31->Add( mMaterialChoose, 1, wxALL|wxEXPAND, 5 );

	bSizer28->Add( bSizer31, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxVERTICAL );

	mMaterialGrid = new MaterialPropertyGrid(this);
	bSizer32->Add(mMaterialGrid, 1, wxEXPAND, 5 );

	bSizer28->Add( bSizer32, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer311;
	bSizer311 = new wxBoxSizer( wxVERTICAL );

	mApply = new wxButton( this, wxID_ANY, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer311->Add( mApply, 0, wxALL|wxALIGN_RIGHT, 5 );

	bSizer28->Add( bSizer311, 0, wxEXPAND, 5 );

	this->SetSizer( bSizer28 );
	this->Layout();
}
//-----------------------------------------------------------------------------
MaterialPanel::~MaterialPanel ()
{

}
//-----------------------------------------------------------------------------
MaterialPanel::MaterialPanel ()
{

}
//-----------------------------------------------------------------------------
void MaterialPanel::OnMaterialChoose (wxCommandEvent &event)
{
	if (event.GetEventObject() == mMaterialChoose)
	{
		int selectIndex = mMaterialChoose->GetCurrentSelection();
		wxString selectString = mMaterialChoose->GetString(selectIndex);

		if (selectString == "VertexColor4")
		{
			mNewMaterial = new0 VertexColor4Material;
		}
		else if (selectString == "Texture2D")
		{
			mNewMaterial = new0 Texture2DMaterial;
		}

		mMaterialGrid->SetObject(mNewMaterial);
	}
}
//-----------------------------------------------------------------------------
void MaterialPanel::OnButton (wxCommandEvent& event)
{
	if (event.GetEventObject() == mApply)
	{
		VertexColor4Material *vcm = DynamicCast<VertexColor4Material>(
			mNewMaterial);
		Texture2DMaterial *t2m = DynamicCast<Texture2DMaterial>(mNewMaterial);

		if (vcm)
		{
			mRenderable->SetMaterialInstance(vcm->CreateInstance());
		}
		else if (t2m)
		{
			PX2::Texture2D *tex2d = mMaterialGrid->mTexture2D_Tex;

			if (tex2d)
			{
				mRenderable->SetMaterialInstance(t2m->CreateInstance(tex2d));
			}
		}
	}
}
//-----------------------------------------------------------------------------
void MaterialPanel::SetRenderable (PX2::Renderable *ren)
{
	mRenderable = ren;

	PX2::Material *mtl = DynamicCast<PX2::Material>(ren
		->GetMaterialInstance()->GetMaterial()->Copy(""));
	mNewMaterial = mtl;

	mMaterialGrid->SetRenderable(ren);
	mMaterialGrid->SetObject(mNewMaterial);
}
//-----------------------------------------------------------------------------