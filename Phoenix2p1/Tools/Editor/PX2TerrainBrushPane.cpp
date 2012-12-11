/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainEditPane.cpp
*
*/

#include "PX2TerrainBrushPane.hpp"
using namespace PX2Editor;
using namespace PX2;

#define SIZE_ADJUST 10
#define STENGTH_ADJUST 0.1f

BEGIN_EVENT_TABLE(TerrainBrushPanel, wxPanel)
EVT_CHOICE(wxID_ANY, TerrainBrushPanel::OnChoice)
EVT_SLIDER(wxID_ANY, TerrainBrushPanel::OnSliderUpdate)
EVT_CHECKBOX(wxID_ANY, TerrainBrushPanel::OnCheckbox)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
TerrainBrushPanel::TerrainBrushPanel (wxWindow *parent)
{
	const bool bSuccess = wxXmlResource::Get()->LoadPanel(this, parent,
		TEXT("TerrainBrush") );

	assertion(bSuccess, "Load TerrainBrush failed!");
	PX2_UNUSED(bSuccess);

	mInterplate = (wxChoice*)FindWindow(XRCID("InterplateMode"));
	assertion(mInterplate!=0, "Window must be find!");

	mSize = (wxSlider*)FindWindow(XRCID("Size"));
	assertion(mSize!=0, "Window must be find!");

	mStrength = (wxSlider*)FindWindow(XRCID("Strength"));
	assertion(mStrength!=0, "Window must be find!");

	TerrainBrush::InterplateMode mode = 
		EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()
		->GetInterplateMode();
	float size = EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()
		->GetSize();
	float strength = EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()
		->GetStrength();

	if (mode == TerrainBrush::IM_NONE)
		mInterplate->SetSelection(3);
	else if (mode == TerrainBrush::IM_LINER)
		mInterplate->SetSelection(2);
	else if (mode == TerrainBrush::IM_SQUARE)
		mInterplate->SetSelection(1);
	else if (mode == TerrainBrush::IM_COS)
		mInterplate->SetSelection(0);

	mSize->SetValue((int)((size/SIZE_ADJUST)*10));
	mStrength->SetValue((int)((strength/STENGTH_ADJUST)*100));
}
//-----------------------------------------------------------------------------
void TerrainBrushPanel::OnSliderUpdate (wxCommandEvent &event)
{
	if (event.GetEventObject() == mSize)
	{
		int value = mSize->GetValue();
		if (value > 0)
		{
			float size = ((float)value/10.0f) * SIZE_ADJUST;
			EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()->SetSize(
				size);
		}
	}
	else if (event.GetEventObject() == mStrength)
	{
		int value = mStrength->GetValue();
		if (value > 0)
		{
			float strength = ((float)value/100.0f) * STENGTH_ADJUST;
			EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()
				->SetStrength(strength);
		}
	}
}
//-----------------------------------------------------------------------------
void TerrainBrushPanel::OnChoice( wxCommandEvent &event )
{
	if (event.GetEventObject() == mInterplate)
	{
		int selectIndex = mInterplate->GetCurrentSelection();
		wxString selectString = mInterplate->GetString(selectIndex);

		if (selectString == "Cos")
		{
			EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()
				->SetInterplateMode(TerrainBrush::IM_COS);
		}
		else if (selectString == "Square")
		{
			EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()
				->SetInterplateMode(TerrainBrush::IM_SQUARE);
		}
		else if (selectString == "Linear")
		{
			EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()
				->SetInterplateMode(TerrainBrush::IM_LINER);
		}
		else if (selectString == "None")
		{
			EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()
				->SetInterplateMode(TerrainBrush::IM_NONE);
		}
	}
}
//-----------------------------------------------------------------------------
void TerrainBrushPanel::OnCheckbox (wxCommandEvent& event)
{
}
//-----------------------------------------------------------------------------
void TerrainBrushPanel::RefleshCtrls ()
{
	float sz = EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()
		->GetSize();
	float szValue = 10.0f * sz/SIZE_ADJUST;
	mSize->SetValue((int)szValue);

	float strength = EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()
		->GetStrength();
	float strengthValue = 100.0f * strength/STENGTH_ADJUST;
	mStrength->SetValue((int)strengthValue);
}
//-----------------------------------------------------------------------------