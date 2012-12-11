/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainMaterialPane.cpp
*
*/

#include "PX2TerrainMaterialPane.hpp"
using namespace PX2Editor;
using namespace PX2;

#define SIZE_ADJUST 10.0f
#define STENGTH_ADJUST 0.1f

BEGIN_EVENT_TABLE(TerrainMaterialPanel, wxPanel)
EVT_SLIDER(wxID_ANY, TerrainMaterialPanel::OnSliderUpdate)
EVT_RADIOBOX(wxID_ANY, TerrainMaterialPanel::OnRadio)
EVT_LISTBOX(wxID_ANY, TerrainMaterialPanel::OnListbox)
EVT_TEXT_ENTER(wxID_ANY, TerrainMaterialPanel::OnTextEnter)
EVT_BUTTON(wxID_ANY, TerrainMaterialPanel::OnButton)
EVT_COLOURPICKER_CHANGED(wxID_ANY, TerrainMaterialPanel::OnColourChange)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
TerrainMaterialPanel::TerrainMaterialPanel (wxWindow *parent)
{
	const bool bSuccess = wxXmlResource::Get()->LoadPanel(this, parent,
		TEXT("TerrainMaterial") );

	assertion(bSuccess, "Load TerrainBrush failed!");
	PX2_UNUSED(bSuccess);

	mMtlEmissive = (wxColourPickerCtrl*)FindWindow(XRCID("mMtlEmissive"));
	assertion(mMtlEmissive!=0, "Window must be find!");
	mMtlAmbient = (wxColourPickerCtrl*)FindWindow(XRCID("mMtlAmbient"));
	assertion(mMtlAmbient!=0, "Window must be find!");
	mMtlDiffuse = (wxColourPickerCtrl*)FindWindow(XRCID("mMtlDiffuse"));
	assertion(mMtlDiffuse!=0, "Window must be find!");

	mTexToUse = (wxTextCtrl*)FindWindow(XRCID("mTexToUse"));
	assertion(mTexToUse!=0, "Window must be find!");

	mTexToUseButton = (wxButton*)FindWindow(XRCID("mTexToUseButton"));
	assertion(mTexToUseButton!=0, "Window must be find!");

	mTextPath = (wxTextCtrl*)FindWindow(XRCID("mTexPath"));
	assertion(mTextPath!=0, "Window must be find!");

	mXIndex = (wxTextCtrl*)FindWindow(XRCID("mXIndex"));
	assertion(mXIndex!=0, "Window must be find!");
	mYIndex = (wxTextCtrl*)FindWindow(XRCID("mYIndex"));
	assertion(mYIndex!=0, "Window must be find!");

	mLayerList = (wxListBox*)FindWindow(XRCID("LayerList"));
	assertion(mLayerList!=0, "Window must be find!");

	mURepeatText = (wxTextCtrl*)FindWindow(XRCID("mURepeatText"));
	assertion(mURepeatText!=0, "Window must be find!");

	mURepeatSlider = (wxSlider*)FindWindow(XRCID("mURepeatSlider"));
	assertion(mURepeatSlider!=0, "Window must be find!");

	mVRepeatText = (wxTextCtrl*)FindWindow(XRCID("mVRepeatText"));
	assertion(mVRepeatText!=0, "Window must be find!");

	mVRepeatSlider = (wxSlider*)FindWindow(XRCID("mVRepeatSlider"));
	assertion(mVRepeatSlider!=0, "Window must be find!");

	mLayerTexBitMap = (wxStaticBitmap*)FindWindow(XRCID("mLayerTex"));
	assertion(mLayerTexBitMap!=0, "Window must be find!");
}
//-----------------------------------------------------------------------------
void TerrainMaterialPanel::OnSliderUpdate (wxCommandEvent &event)
{
	PX2::RawTerrainPage *page = EditSystem::GetSingleton().GetTerrainEdit()
		->GetBrush()->GetSelectedPage();

	if (event.GetEventObject() == mURepeatSlider)
	{
		int value = mURepeatSlider->GetValue();

		int selectIndex = EditSystem::GetSingleton().GetTerrainEdit()
			->GetTextureProcess()->GetSelectedLayer();

		if (page)
		{
			PX2::Float2 uv = page->GetUV(selectIndex);
			uv[0] = (float)value;
			page->SetUV(selectIndex, uv);

			wxString strU = wxString::Format("%.2f", uv[0]);
			mURepeatText->Clear();
			mURepeatText->SetValue(strU);
		}
	}
	else if (event.GetEventObject() == mVRepeatSlider)
	{
		int value = mVRepeatSlider->GetValue();

		int selectIndex = EditSystem::GetSingleton().GetTerrainEdit()
			->GetTextureProcess()->GetSelectedLayer();
		PX2::RawTerrainPage *page = EditSystem::GetSingleton().GetTerrainEdit()
			->GetBrush()->GetSelectedPage();

		if (page)
		{
			PX2::Float2 uv = page->GetUV(selectIndex);
			uv[1] = (float)value;
			page->SetUV(selectIndex, uv);

			wxString strV = wxString::Format("%.2f", uv[1]);
			mVRepeatText->Clear();
			mVRepeatText->SetValue(strV);
		}
	}

	if (!page)
	{
		mURepeatText->Clear();
		mVRepeatText->Clear();
	}
}
//-----------------------------------------------------------------------------
void TerrainMaterialPanel::OnRadio( wxCommandEvent &event )
{
	//wxString str = event.GetString();

	//if ("Add" == str)
	//{
	//	EditSystem::GetSingleton().GetTerrainEdit()->GetTextureProcess()
	//		->SetTextureMode(TerrainTextureProcess::TM_INCREASE);
	//}
	//else if ("Reduce" == str)
	//{
	//	EditSystem::GetSingleton().GetTerrainEdit()->GetTextureProcess()
	//		->SetTextureMode(TerrainTextureProcess::TM_DECREASE);
	//}
}
//-----------------------------------------------------------------------------
void TerrainMaterialPanel::OnListbox (wxCommandEvent& event)
{
	if (event.GetEventObject() == mLayerList)
	{
		int selectIndex = event.GetSelection();

		EditSystem::GetSingleton().GetTerrainEdit()
			->GetTextureProcess()->SetSelectedLayer(selectIndex);

		RefleshCtrls();
	}
}
//-----------------------------------------------------------------------------
void TerrainMaterialPanel::OnTextEnter (wxCommandEvent& event)
{
	int selectIndex = EditSystem::GetSingleton().GetTerrainEdit()
		->GetTextureProcess()->GetSelectedLayer();
	PX2::RawTerrainPage *page = EditSystem::GetSingleton().GetTerrainEdit()
		->GetBrush()->GetSelectedPage();

	PX2::Float2 uv = page->GetUV(selectIndex);

	if (event.GetEventObject() == mURepeatText)
	{
		int value = wxAtoi(event.GetString().GetData());
		uv[0] = (float)value;
		page->SetUV(selectIndex, uv);

		mURepeatSlider->SetValue(value);
	}
	else if (event.GetEventObject() == mVRepeatText)
	{
		int value = wxAtoi(event.GetString().GetData());
		uv[1] = (float)value;

		page->SetUV(selectIndex, uv);
		mVRepeatSlider->SetValue(value);
	}
}
//-----------------------------------------------------------------------------
void TerrainMaterialPanel::OnButton (wxCommandEvent& event)
{
	if (event.GetEventObject() == mTexToUseButton)
	{
		PX2::Object *obj = EditSystem::GetSingleton().GetSelectedResource();
		PX2::Texture2D *tex = PX2::DynamicCast<PX2::Texture2D>(obj);

		if (tex)
		{
			EditSystem::GetSingleton().GetTerrainEdit()->GetTextureProcess()
				->SetSelectedLayerUsingTexture(tex);

			RefleshCtrls();
		}
	}
}
//-----------------------------------------------------------------------------
void TerrainMaterialPanel::RefleshCtrls ()
{
	int selectIndex = 0;
	selectIndex = EditSystem::GetSingleton().GetTerrainEdit()
		->GetTextureProcess()->GetSelectedLayer();

	TerrainActor *actor = EditSystem::GetSingleton().GetEditMap()
		->GetScene()->GetTerrainActor();
	Terrain *ter = 0;
	if (actor)
		ter = actor->GetTerrain();

	if (!ter)
		return;

	RawTerrain *terrain = DynamicCast<RawTerrain>(ter);
	if (!terrain)
		return;

	Shine *shine = terrain->GetShine();
	mShineEmissive = Float3(shine->Emissive[0],
		shine->Emissive[1], shine->Emissive[2]);
	mShineAmbient = Float3(shine->Ambient[0],
		shine->Ambient[1], shine->Ambient[2]);
	mShineDiffuse = Float3(shine->Diffuse[0],
		shine->Diffuse[1], shine->Diffuse[2]);

	wxColour emissiveColour = wxColour(
		(unsigned char)(mShineEmissive[0]*255),
		(unsigned char)(mShineEmissive[1]*255),
		(unsigned char)(mShineEmissive[2]*255));
	mMtlEmissive->SetColour(emissiveColour);

	wxColour ambientColour = wxColour(
		(unsigned char)(mShineAmbient[0]*255),
		(unsigned char)(mShineAmbient[1]*255),
		(unsigned char)(mShineAmbient[2]*255));
	mMtlAmbient->SetColour(ambientColour);

	wxColour diffuseColour = wxColour(
		(unsigned char)(mShineDiffuse[0]*255),
		(unsigned char)(mShineDiffuse[1]*255),
		(unsigned char)(mShineDiffuse[2]*255));
	mMtlDiffuse->SetColour(diffuseColour);

	// texToUse
	PX2::Texture2D *tex = EditSystem::GetSingleton().GetTerrainEdit()
		->GetTextureProcess()->GetLayerUsingTexture(selectIndex);
	if (tex)
	{
		std::string strText = tex->GetResourcePath();
		mTexToUse->Clear();
		mTexToUse->WriteText(strText.c_str());
	}
	else
	{
		mTexToUse->Clear();
	}

	// selectedPage
	PX2::RawTerrainPage *selectedPage = EditSystem::GetSingleton().GetTerrainEdit()
		->GetBrush()->GetSelectedPage();

	if (selectedPage && terrain)
	{
		int xIndex = 0;
		int yIndex = 0;
		terrain->GetPageIndex(xIndex, yIndex, selectedPage);
		wxString strXIndex = wxString::Format("%d", xIndex);
		wxString strYIndex = wxString::Format("%d", yIndex);
		mXIndex->Clear();
		mXIndex->WriteText(strXIndex);
		mYIndex->Clear();
		mYIndex->WriteText(strYIndex);	

		Float2 uv = selectedPage->GetUV(selectIndex);

		PX2::Texture2D *tex2d = 0;
		tex2d = selectedPage->GetTexture(selectIndex);
		if (tex2d)
		{
			std::string texPath = tex2d->GetResourcePath();
			mTextPath->Clear();
			mTextPath->WriteText(texPath);

			wxString strU = wxString::Format("%.2f", uv[0]);
			wxString strV = wxString::Format("%.2f", uv[1]);
			mURepeatText->Clear();
			mURepeatText->WriteText(strU);
			mURepeatSlider->SetValue(int(uv[0]));

			mVRepeatText->Clear();
			mVRepeatText->WriteText(strV);
			mVRepeatSlider->SetValue(int(uv[1]));

			wxImage im(texPath);
			wxBitmap bitMap(im);
			bitMap.SetWidth(mLayerTexBitMap->GetSize().GetWidth());
			bitMap.SetHeight(mLayerTexBitMap->GetSize().GetHeight());
			mLayerTexBitMap->SetBitmap(bitMap);
		}
		else
		{
			mTextPath->Clear();
			mURepeatText->Clear();
			mVRepeatText->Clear();
			mURepeatSlider->SetValue(0);
			mVRepeatSlider->SetValue(0);
		}
	}
	else
	{
		mXIndex->Clear();
		mYIndex->Clear();

		mURepeatText->Clear();
		mURepeatSlider->SetValue(0);

		mVRepeatText->Clear();
		mVRepeatSlider->SetValue(0);
	}
}
//-----------------------------------------------------------------------------
void TerrainMaterialPanel::OnColourChange(wxColourPickerEvent &e)
{
	PX2::RawTerrain *terrain = EditSystem::GetSingleton().GetTerrainEdit()
		->GetBrush()->GetTerrain();
	if (!terrain)
		return;

	Shine *shine = terrain->GetShine();

	if (mMtlEmissive == e.GetEventObject())
	{
		wxColour colour = mMtlEmissive->GetColour();
		shine->Emissive = Float4(colour.Red()/255.0f,
			colour.Green()/255.0f, 
			colour.Blue()/255.0f, 1.0f);
	}
	else if (mMtlAmbient == e.GetEventObject())
	{
		wxColour colour = mMtlAmbient->GetColour();
		shine->Ambient = Float4(colour.Red()/255.0f,
			colour.Green()/255.0f, 
			colour.Blue()/255.0f, 1.0f);
	}
	else if (mMtlDiffuse == e.GetEventObject())
	{
		wxColour colour = mMtlDiffuse->GetColour();
		shine->Diffuse = Float4(colour.Red()/255.0f,
			colour.Green()/255.0f, 
			colour.Blue()/255.0f, 1.0f);
	}
}
//-----------------------------------------------------------------------------