/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TextureConvertPanel.cpp
*
*/

#include "PX2TextureConvertPanel.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(TextureConvertPane, wxPanel)
	EVT_BUTTON(wxID_ANY, TextureConvertPane::OnButton)
	EVT_SIZE(TextureConvertPane::OnSize)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
TextureConvertPane::TextureConvertPane (wxWindow *parent)
:
mAdd(0),
mRemove(0),
mClear(0),
mTextureList(0),
mDDSKC(0),
mConvert(0)
{
	const bool bSuccess = wxXmlResource::Get()->LoadPanel(this, parent,
		TEXT("TextureConvert") );

	assertion(bSuccess, "Load TerrainBrush failed!");
	PX2_UNUSED(bSuccess);

	mAdd = (wxButton*)FindWindow(XRCID("Add"));
	assertion(mAdd!=0, "Window must be find!");
	
	mRemove = (wxButton*)FindWindow(XRCID("Remove"));
	assertion(mRemove!=0, "Window must be find!");

	mClear = (wxButton*)FindWindow(XRCID("Clear"));
	assertion(mClear!=0, "Window must be find!");

	mTextureList = (wxListBox*)FindWindow(XRCID("TextureList"));
	assertion(mTextureList!=0, "Window must be find!");

	mDDSKC = (wxCheckBox*)FindWindow(XRCID("DDSKC"));
	assertion(mDDSKC!=0, "Window must be find!");

	mConvert = (wxButton*)FindWindow(XRCID("Convert"));
	assertion(mConvert!=0, "Window must be find!");
}
//-----------------------------------------------------------------------------
TextureConvertPane::TextureConvertPane ()
{

}
//-----------------------------------------------------------------------------
void TextureConvertPane::OnButton (wxCommandEvent& event)
{
	if (event.GetEventObject() == mAdd)
	{
		wxFileDialog dialog(this, _T("Select textures"),
			wxEmptyString, wxEmptyString, 
			wxString::Format
			(
			_T("AllFiles(%s)|%s|BMP(*.bmp)|*.bmp|JPG(*.jpg)|*.jpg|PNG(*png)|*.png|D3D/DDS(*dds)|*.dds"),
			wxFileSelectorDefaultWildcardStr,
			wxFileSelectorDefaultWildcardStr
			),
			wxFD_OPEN|wxFD_MULTIPLE|wxFD_PREVIEW);

		dialog.CenterOnParent();

		if (dialog.ShowModal() == wxID_OK)
		{
			wxArrayString paths, filenames;

			dialog.GetPaths(paths);
			dialog.GetFilenames(filenames);

			wxString msg, s;
			size_t count = paths.GetCount();

			for ( size_t n = 0; n < count; n++ )
			{
				wxString wxPath = paths[n];

				std::string path = std::string(wxPath.ToAscii());
				std::string pathDirectory;
				std::string filename;
				std::string extname;
				StringHelp::SplitFullFilename(path, pathDirectory, filename,
					extname);

				if (extname != "tdtf")
					mTextureList->Append(path);
			}
		}
	}
	else if (event.GetEventObject() == mConvert)
	{
		bool check = mDDSKC->IsChecked();
		bool isKeep = ResourceManager::GetSingleton().IsDDSKeepCompressed();
		ResourceManager::GetSingleton().DDSKeepCompressed(check);

		unsigned int count = (int)mTextureList->GetCount();

		for (unsigned int i=0; i<count; i++)
		{
			wxString wxPath = mTextureList->GetString(i);
			std::string path = std::string(wxPath.ToAscii());
			PX2::TexturePtr tex = DynamicCast<PX2::Texture>(ResourceManager
				::GetSingleton().BlockLoad(path.c_str()));
			assertion(tex!=0, "tex load failed.");

			if (tex)
			{
				std::string pathDirectory;
				std::string filename;
				std::string extname;
				StringHelp::SplitFullFilename(path, pathDirectory, filename, 
					extname);
				std::string saveName = pathDirectory+ filename + ".pxtf";
				tex->SavePXtf(saveName);
			}
		}

		mTextureList->Clear();
		ResourceManager::GetSingleton().DDSKeepCompressed(isKeep);
	}
	else if (event.GetEventObject() == mClear)
	{
		mTextureList->Clear();
	}
	else if (event.GetEventObject() == mRemove)
	{
		wxArrayInt selections;
		mTextureList->GetSelections(selections);

		while ((int)selections.size() > 0)
		{
			mTextureList->Delete(selections[0]);
			mTextureList->GetSelections(selections);
		}
	}
}
//-----------------------------------------------------------------------------
void TextureConvertPane::OnSize (wxSizeEvent& e)
{
	wxPanel::OnSize(e);
}
//-----------------------------------------------------------------------------