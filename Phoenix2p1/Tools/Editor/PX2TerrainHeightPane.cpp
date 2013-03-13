/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainHeightPane.cpp
*
*/

#include "PX2TerrainHeightPane.hpp"
#include "PX2EditSystem.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(TerrainHeightPanel, wxPanel)
EVT_RADIOBOX(wxID_ANY, TerrainHeightPanel::OnRadio)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
TerrainHeightPanel::TerrainHeightPanel (wxWindow *parent)
{
	const bool bSuccess = wxXmlResource::Get()->LoadPanel(this, parent,
		TEXT("TerrainHeight") );

	assertion(bSuccess, "Load TerrainBrush failed!");
	PX2_UNUSED(bSuccess);

	mHeightModeRadio = (wxRadioBox*)FindWindow(XRCID("mHeightModeRadio"));
	assertion(mHeightModeRadio!=0, "Window must be find!");
}
//-----------------------------------------------------------------------------
void TerrainHeightPanel::OnRadio( wxCommandEvent &event )
{
	wxString str = event.GetString();

	if ( "Raise" == str)
	{
		EditSystem::GetSingleton().GetTerrainEdit()->GetHeightProcess()
			->SetHeightMode(TerrainHeightProcess::HM_RAISE);
	}
	else if ("Lower" == str)
	{
		EditSystem::GetSingleton().GetTerrainEdit()->GetHeightProcess()
			->SetHeightMode(TerrainHeightProcess::HM_LOWER);
	}
	else if ("Fatten" == str)
	{
		EditSystem::GetSingleton().GetTerrainEdit()->GetHeightProcess()
			->SetHeightMode(TerrainHeightProcess::HM_FLATTEN);
	}
	else if ("Smooth" == str)
	{
		EditSystem::GetSingleton().GetTerrainEdit()->GetHeightProcess()
			->SetHeightMode(TerrainHeightProcess::HM_SMOOTH);
	}
	else if ("Zero" == str)
	{
		EditSystem::GetSingleton().GetTerrainEdit()->GetHeightProcess()
			->SetHeightMode(TerrainHeightProcess::HM_ZERO);
	}
}
//-----------------------------------------------------------------------------
void TerrainHeightPanel::RefleshCtrls ()
{
	TerrainHeightProcess::HeightMode mode = 
		EditSystem::GetSingleton().GetTerrainEdit()->GetHeightProcess()
		->GetHeightMode();

	if (mode == TerrainHeightProcess::HM_RAISE)
	{
		mHeightModeRadio->SetSelection(0);
	}
	else if (mode == TerrainHeightProcess::HM_LOWER)
	{
		mHeightModeRadio->SetSelection(1);
	}
	else if (mode == TerrainHeightProcess::HM_FLATTEN)
	{
		mHeightModeRadio->SetSelection(2);
	}
	else if (mode == TerrainHeightProcess::HM_SMOOTH)
	{
		mHeightModeRadio->SetSelection(3);
	}
}
//-----------------------------------------------------------------------------