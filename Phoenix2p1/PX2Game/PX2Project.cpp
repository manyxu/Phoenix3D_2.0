/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Project.cpp
*
*/

#include "PX2Project.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2XMLData.hpp"
#include "PX2UIManager.hpp"
#include "PX2StringHelp.hpp"
#include "PX2OutStream.hpp"
#include "PX2InStream.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Project::Project ()
	:
mIsInGamePlay(false),
mWidth(960),
mHeight(640),
mIsShowProjectInfo(true),
mIsShowSceneBound(true),
mIsSceneWired(false),
mIsUIWired(false),
mUICameraPercent(1.0f),
mIsShowUI(true),
mIsShowUIRange(true),
mIsShowGrid(true)
{
	mColor = Float4::BLACK;
	SetUI(new0 UIFrame());
}
//----------------------------------------------------------------------------
Project::~Project ()
{
}
//----------------------------------------------------------------------------
bool Project::Save (const std::string &filename)
{
	XMLNode projNode("Project");
	projNode.Create();
	projNode.SetAttributeString("Name", mName.c_str());
	projNode.SetAttributeInt("Width", mWidth);
	projNode.SetAttributeInt("Height", mHeight);
	projNode.SetAttributeFloat("Color0", mColor[0]);
	projNode.SetAttributeFloat("Color1", mColor[1]);
	projNode.SetAttributeFloat("Color2", mColor[2]);
	projNode.SetAttributeFloat("Color3", mColor[3]);
	projNode.SetAttributeBool("IsShowProjectInfo", mIsShowProjectInfo);
	projNode.SetAttributeBool("IsShowSceneBound", mIsShowSceneBound);
	projNode.SetAttributeBool("IsSceneWired", mIsSceneWired);
	projNode.SetAttributeBool("IsUIWired", mIsUIWired);
	projNode.SetAttributeFloat("UICameraPercent", mUICameraPercent);
	projNode.SetAttributeBool("IsShowUI", mIsShowUI);
	projNode.SetAttributeBool("IsShowUIRange", mIsShowUIRange);
	projNode.SetAttributeBool("IsShowGrid", mIsShowGrid);

	XMLNode sceneNode("Scene");
	sceneNode.Create();
	sceneNode.SetAttributeString("Filename", mSceneFilename.c_str());
	projNode.LinkEndChild(sceneNode);

	std::string outPath;
	std::string outBaseName;
	std::string outExt;
	StringHelp::SplitFullFilename(filename, outPath, outBaseName, outExt);
	std::string outName = outPath + outBaseName + ".px2ui";

	if (mUI)
	{
		Transform beforeLocalTrans = mUI->LocalTransform;
		Transform beforeWorldTrans = mUI->WorldTransform;
		OutStream output;
		mUI->LocalTransform.MakeIdentity();
		mUI->WorldTransform.MakeIdentity();
		output.Insert(mUI);
		output.Save(outName);
		mUI->LocalTransform = beforeLocalTrans;
		mUI->WorldTransform = beforeWorldTrans;
	}

	// xml
	XMLData data;
	data.Create();
	data.LinkEndChild(projNode);

	if (data.SaveFile(filename))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
bool Project::Load (const std::string &filename)
{
	std::string name;
	int width = 0;
	int height = 0;
	std::string sceneFilename;
	std::string uiFilename;
	
	char *buffer = 0;
	int bufferSize = 0;
	if (ResourceManager::GetSingleton().GetBuffer(filename, bufferSize,
		buffer))
	{
		XMLData data;
		if (data.LoadBuffer(buffer, bufferSize))
		{
			XMLNode rootNode = data.GetRootNode();
			name = rootNode.AttributeToString("Name");
			width = rootNode.AttributeToInt("Width");
			height = rootNode.AttributeToInt("Height");
			Float4 color = Float4::WHITE;
			color[0] = rootNode.AttributeToFloat("Color0");
			color[1] = rootNode.AttributeToFloat("Color1");
			color[2] = rootNode.AttributeToFloat("Color2");
			color[3] = rootNode.AttributeToFloat("Color3");
			bool isShowProjInfo = rootNode.AttributeToBool("IsShowProjectInfo");
			bool isShowSceneBound = rootNode.AttributeToBool("IsShowSceneBound");
			bool isSceneWired = rootNode.AttributeToBool("IsSceneWired");
			bool isUIWired = rootNode.AttributeToBool("IsUIWired");
			float uiCameraPercent = rootNode.AttributeToFloat("UICameraPercent");
			bool isShowUI = rootNode.AttributeToBool("IsShowUI");
			bool isShowUIRange = rootNode.AttributeToBool("IsShowUIRange");
			bool isShowGrid = rootNode.AttributeToBool("IsShowGrid");

			mName = name;
			mWidth = width;
			mHeight = height;
			SetColor(color);
			SetShowProjectInfo(isShowProjInfo);
			SetShowSceneBound(isShowSceneBound);
			SetSceneWired(isSceneWired);
			SetUIWired(isUIWired);
			SetUICameraPercent(uiCameraPercent);
			SetShowUI(isShowUI);
			SetShowUIRange(isShowUIRange);
			SetShowGrid(isShowGrid);

			XMLNode sceneNode = rootNode.GetChild("Scene");
			if (!sceneNode.IsNull())
			{
				sceneFilename = sceneNode.AttributeToString("Filename");
				SetSceneFilename(sceneFilename);
			}

			std::string outPath;
			std::string outBaseName;
			std::string outExt;
			StringHelp::SplitFullFilename(filename, outPath, outBaseName, outExt);
			std::string inName = outPath + outBaseName + ".px2ui";
			SetUIFilename(inName);
		}

		delete1(buffer);
	}
	else
	{
		if (buffer)
			delete1(buffer);
		return false;
	}

	return true;
}
//----------------------------------------------------------------------------
void Project::SetSceneFilename (std::string filename)
{
	mSceneFilename = filename;
}
//----------------------------------------------------------------------------
void Project::SetUIFilename (std::string filename)
{
	mUIFilename = filename;
}
//----------------------------------------------------------------------------
void Project::SetScene (Scene *scene)
{
	mScene = scene;
}
//----------------------------------------------------------------------------
void Project::SetUI (UIFrame *frame)
{
	mUI = frame;
	UIManager::GetSingleton().GetDefaultView()->SetMainFrame(frame);
}
//----------------------------------------------------------------------------
void Project::SetShowProjectInfo (bool show)
{
	mIsShowProjectInfo = show;
}
//----------------------------------------------------------------------------
void Project::SetSceneWired (bool wire)
{
	mIsSceneWired = wire;
}
//----------------------------------------------------------------------------
void Project::SetShowSceneBound (bool show)
{
	mIsShowSceneBound = show;
}
//----------------------------------------------------------------------------
void Project::SetUIWired (bool wire)
{
	mIsUIWired = wire;
}
//----------------------------------------------------------------------------
void Project::SetUICameraPercent (float percent)
{
	mUICameraPercent = percent;
}
//----------------------------------------------------------------------------
void Project::SetShowUI (bool show)
{
	mIsShowUI = show;
}
//----------------------------------------------------------------------------
void Project::SetShowUIRange (bool show)
{
	mIsShowUIRange = show;
}
//----------------------------------------------------------------------------
void Project::SetShowGrid(bool show)
{
	mIsShowGrid = show;
}
//----------------------------------------------------------------------------