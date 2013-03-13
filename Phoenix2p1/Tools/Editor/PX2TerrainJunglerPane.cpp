/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainJunglerPane.cpp
*
*/

#include "PX2TerrainJunglerPane.hpp"
#include "PX2EditSystem.hpp"
#include "PX2Project.hpp"
using namespace PX2Editor;
using namespace PX2;

#define SIZE_ADJUST 10.0f
#define STENGTH_ADJUST 0.1f

BEGIN_EVENT_TABLE(TerrainJunglerPanel, wxPanel)
EVT_RADIOBOX(wxID_ANY, TerrainJunglerPanel::OnRadio)
EVT_LISTBOX(wxID_ANY, TerrainJunglerPanel::OnListbox)
EVT_LISTBOX_DCLICK(wxID_ANY, TerrainJunglerPanel::OnListboxD)
EVT_BUTTON(wxID_ANY, TerrainJunglerPanel::OnButton)
EVT_TEXT_ENTER(wxID_ANY, TerrainJunglerPanel::OnTextEnter)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
TerrainJunglerPanel::TerrainJunglerPanel (wxWindow *parent)
{
	const bool bSuccess = wxXmlResource::Get()->LoadPanel(this, parent,
		TEXT("TerrainJungler") );

	assertion(bSuccess, "Load TerrainJungler failed!");
	PX2_UNUSED(bSuccess);

	mTexToUse = (wxTextCtrl*)FindWindow(XRCID("mTexToUse"));
	assertion(mTexToUse!=0, "Window must be find!");

	mTexToUseButton = (wxButton*)FindWindow(XRCID("mTexToUseButton"));
	assertion(mTexToUseButton!=0, "Window must be find!");

	mXIndex = (wxTextCtrl*)FindWindow(XRCID("mXIndex"));
	assertion(mXIndex!=0, "Window must be find!");
	mYIndex = (wxTextCtrl*)FindWindow(XRCID("mYIndex"));
	assertion(mYIndex!=0, "Window must be find!");
	mWidthText = (wxTextCtrl*)FindWindow(XRCID("mWidth"));
	assertion(mWidthText!=0, "Window must be find!");
	mHeightText = (wxTextCtrl*)FindWindow(XRCID("mHeight"));
	assertion(mHeightText!=0, "Window must be find!");

	mJungleTexBitmap = (wxStaticBitmap*)FindWindow(XRCID("mJungleTexBitmap"));
	assertion(mJungleTexBitmap!=0, "Window must be find!");

	mJungleList = (wxListBox*)FindWindow(XRCID("mJungleList"));
	assertion(mJungleList!=0, "Window must be find!");
}
//-----------------------------------------------------------------------------
void TerrainJunglerPanel::OnRadio( wxCommandEvent &event )
{
	wxString str = event.GetString();

	if ("Add" == str)
	{
		EditSystem::GetSingleton().GetTerrainEdit()->GetJunglerProcess()
			->SetJunglerMode(TerrainJunglerProcess::JM_ADD);
	}
	else if ("Reduce" == str)
	{
		EditSystem::GetSingleton().GetTerrainEdit()->GetJunglerProcess()
			->SetJunglerMode(TerrainJunglerProcess::JM_REDUCE);
	}
}
//-----------------------------------------------------------------------------
void TerrainJunglerPanel::OnListbox (wxCommandEvent& event)
{
	if (event.GetEventObject() == mJungleList)
	{
		int sel = event.GetSelection();
		int selectIndex = mJungleList->GetCount()- (sel+1);

		TerrainActor *actor = 0;
		
		if (Project::GetSingletonPtr())
			actor = Project::GetSingleton().GetScene()->GetTerrainActor();

		if (!actor)
			return;
		RawTerrain *terrain = actor->GetRawTerrain();
		PX2::TerrainPage *page = 
			EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()->GetSelectedPage();

		if (!page || !terrain)
			return;

		PX2::Jungler *jungler = page->GetJungler(selectIndex); 
		if (jungler)
		{
			Texture2D *tex = jungler->GetTexture();
			std::string texPath = tex->GetResourcePath();

			wxImage im(texPath);
			wxBitmap bitMap(im);
			bitMap.SetWidth(mJungleTexBitmap->GetSize().GetWidth());
			bitMap.SetHeight(mJungleTexBitmap->GetSize().GetHeight());
			mJungleTexBitmap->SetBitmap(bitMap);
		}
	}
}
//-----------------------------------------------------------------------------
void TerrainJunglerPanel::OnListboxD (wxCommandEvent& event)
{
	if (event.GetEventObject() == mJungleList)
	{
		int sel = event.GetSelection();
		int selectIndex = mJungleList->GetCount()- (sel+1);

		TerrainActor *actor = 0;

		if (Project::GetSingletonPtr())
			actor = Project::GetSingleton().GetScene()->GetTerrainActor();

		if (!actor)
			return;
		RawTerrain *terrain = actor->GetRawTerrain();
		PX2::TerrainPage *page = 
			EditSystem::GetSingleton().GetTerrainEdit()->GetBrush()->GetSelectedPage();

		if (!page || !terrain)
			return;

		PX2::Jungler *jungler = page->GetJungler(selectIndex); 
		if (jungler)
		{
			Texture2D *tex = jungler->GetTexture();
			std::string texPath = tex->GetResourcePath();

			wxImage im(texPath);
			wxBitmap bitMap(im);
			bitMap.SetWidth(mJungleTexBitmap->GetSize().GetWidth());
			bitMap.SetHeight(mJungleTexBitmap->GetSize().GetHeight());
			mJungleTexBitmap->SetBitmap(bitMap);

			mTexToUse->Clear();
			mTexToUse->WriteText(texPath.c_str());
			EditSystem::GetSingleton().GetTerrainEdit()->GetJunglerProcess()
				->SetUsingTexture(tex);
		}
	}
}
//-----------------------------------------------------------------------------
void TerrainJunglerPanel::OnButton (wxCommandEvent& event)
{
	if (event.GetEventObject() == mTexToUseButton)
	{
		PX2::Object *obj = EditSystem::GetSingleton().GetSelectedResource();
		PX2::Texture2D *tex = PX2::DynamicCast<PX2::Texture2D>(obj);

		if (tex)
		{
			EditSystem::GetSingleton().GetTerrainEdit()->GetJunglerProcess()
				->SetUsingTexture(tex);

			RefleshCtrls();
		}
	}
}
//-----------------------------------------------------------------------------
void TerrainJunglerPanel::OnTextEnter (wxCommandEvent& event)
{
	if (event.GetEventObject() == mWidthText)
	{
		float val = (float)wxAtof(event.GetString().GetData());

		EditSystem::GetSingleton().GetTerrainEdit()->GetJunglerProcess()
			->SetWidth(val);
	}
	else if (event.GetEventObject() == mHeightText)
	{
		float val = (float)wxAtof(event.GetString().GetData());

		EditSystem::GetSingleton().GetTerrainEdit()->GetJunglerProcess()
			->SetHeight(val);
	}
}
//-----------------------------------------------------------------------------
void TerrainJunglerPanel::RefleshCtrls ()
{
	int selectIndex = 0;
	selectIndex = EditSystem::GetSingleton().GetTerrainEdit()
		->GetTextureProcess()->GetSelectedLayer();

	TerrainActor *actor = 0;

	if (Project::GetSingletonPtr())
		actor = Project::GetSingleton().GetScene()->GetTerrainActor();

	if (!actor)
		return;

	RawTerrain *terrain = actor->GetRawTerrain();
	if (!terrain)
		return;

	PX2::Texture2D *tex = EditSystem::GetSingleton().GetTerrainEdit()
		->GetJunglerProcess()->GetUsingTexture();
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

	float width = EditSystem::GetSingleton().GetTerrainEdit()
		->GetJunglerProcess()->GetWidth();
	float height = EditSystem::GetSingleton().GetTerrainEdit()
		->GetJunglerProcess()->GetHeight();
	wxString strWidth =  wxString::Format("%.2f", width);
	wxString strHeight =  wxString::Format("%.2f", height);
	mWidthText->Clear();
	mWidthText->WriteText(strWidth);
	mHeightText->Clear();
	mHeightText->WriteText(strHeight);	

	// rawPage
	PX2::TerrainPage *page = EditSystem::GetSingleton().GetTerrainEdit()
		->GetBrush()->GetSelectedPage();

	if (page && terrain)
	{
		int xIndex = 0;
		int yIndex = 0;
		terrain->GetPageIndex(xIndex, yIndex, page);
		wxString strXIndex = wxString::Format("%d", xIndex);
		wxString strYIndex = wxString::Format("%d", yIndex);
		mXIndex->Clear();
		mXIndex->WriteText(strXIndex);
		mYIndex->Clear();
		mYIndex->WriteText(strYIndex);	

		mJungleList->Clear();
		int junglerNum = page->GetJunglerNum();
		for (int i=0; i<junglerNum; i++)
		{
			Jungler *jungler = page->GetJungler(i);
			if (jungler)
			{
				PX2::Texture2D *texture = jungler->GetTexture();
				std::string resPath = texture->GetResourcePath();
				mJungleList->Insert(resPath, 0, (void*)texture);
			}
		}	
	}
	else
	{
		mXIndex->Clear();
		mYIndex->Clear();
	}
}
//-----------------------------------------------------------------------------