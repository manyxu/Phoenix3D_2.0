/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIManager.cpp
*
*/

#include "PX2UIManager.hpp"
#include "PX2Camera.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2InputEvent.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
UIManager::UIManager ()
	:
mFontManager(0)
{
	mFontManager = new0 FontManager();

	mDefaultView = new0 UIView(0);
	mUiViews["DefaultUIView"] = mDefaultView;

	mVertexFormat = VertexFormat::Create(3,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT4, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);	

	mUIMaterial = new0 UIMaterial();
	mUIMaterialDoubleSide = new0 UIMaterial();
	mUIMaterialDoubleSide->GetCullProperty(0, 0)->Enabled = false;
}
//----------------------------------------------------------------------------
UIManager::~UIManager ()
{
	if (mFontManager)
	{
		delete0(mFontManager);
		mFontManager = 0;
	}
}
//----------------------------------------------------------------------------
void UIManager::AddUIView (std::string name, UIView *view)
{
	mUiViews[name] = view;
}
//----------------------------------------------------------------------------
UIPicBox *UIManager::CreateUIPicBox (const APoint &localPos,
	const std::string &filename)
{
	UIPicBox *picBox = new0 UIPicBox(filename);
	picBox->LocalTransform.SetTranslate(localPos);

	return picBox;
}
//----------------------------------------------------------------------------
UIAnimPicBox *UIManager::CreateUIAnimPicBox (const APoint &localPos,
	const std::string &texPack)
{
	UIAnimPicBox *animPixBox = new0 UIAnimPicBox();
	animPixBox->LocalTransform.SetTranslate(localPos);

	if ("" != texPack)
	{
		animPixBox->SetFrameTexPack(texPack);
	}

	return animPixBox;
}
//----------------------------------------------------------------------------
UIStaticText *UIManager::CreateUIStaticText (const APoint &localPos)
{
	UIStaticText *text = new0 UIStaticText();
	text->LocalTransform.SetTranslate(localPos);
	return text;
}
//----------------------------------------------------------------------------
UIFrame *UIManager::CreateUIFrame (const APoint &localPos)
{
	UIFrame *frame = new0 UIFrame();
	frame->LocalTransform.SetTranslate(localPos);

	return frame;
}
//----------------------------------------------------------------------------
UIButton *UIManager::CreateUIButton (const APoint &localPos)
{
	UIButton *bnt = new0 UIButton();
	bnt->LocalTransform.SetTranslate(localPos);

	return bnt;
}
//----------------------------------------------------------------------------
void UIManager::DoExecute (Event *event)
{
	std::map<std::string, UIViewPtr>::iterator it = mUiViews.begin();
	for (; it!=mUiViews.end(); it++)
	{
		it->second->DoExecute(event);
	}
}
//----------------------------------------------------------------------------