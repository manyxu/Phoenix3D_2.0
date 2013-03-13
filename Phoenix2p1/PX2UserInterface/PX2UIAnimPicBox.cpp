/*
*
* 文件名称	：	PX2UIAnimPicBox.cpp
*
*/

#include "PX2UIAnimPicBox.hpp"
#include "PX2ResourceManager.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
// UIAnimPicBoxEle
//----------------------------------------------------------------------------
UIAnimPicBoxEle::UIAnimPicBoxEle ()
{
	Index = 0;
	UV0 = Float2::ZERO;
	UV1 = Float2::ZERO;
	UV2 = Float2::ZERO;
	UV3 = Float2::ZERO;
}
//----------------------------------------------------------------------------
UIAnimPicBoxEle::~UIAnimPicBoxEle ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// UIAnimPicBox
//----------------------------------------------------------------------------

PX2_IMPLEMENT_RTTI(PX2, UIPicBox, UIAnimPicBox);
PX2_IMPLEMENT_STREAM(UIAnimPicBox);
PX2_IMPLEMENT_FACTORY(UIAnimPicBox);
PX2_IMPLEMENT_DEFAULT_NAMES(UIPicBox, UIAnimPicBox);

//----------------------------------------------------------------------------
UIAnimPicBox::UIAnimPicBox ()
	:
mActiveIndex(0),
mIntervalTime(0.03f)
{
	SetName("UIAnimPicBox");

	mAPBCtrl = new0 UIAnimPicBoxControl();
	AttachController(mAPBCtrl);

	SetFrameTexPack("Data/engine/numAnim.xml");
}
//----------------------------------------------------------------------------
UIAnimPicBox::~UIAnimPicBox ()
{
}
//----------------------------------------------------------------------------
void UIAnimPicBox::Play ()
{
	mAPBCtrl->Reset();
}
//----------------------------------------------------------------------------
bool UIAnimPicBox::SetFrameTexPack (const std::string &filename)
{
	mFrameTexPack = filename;

	ResourceManager::GetSingleton().AddTexPack(mFrameTexPack);

	const TexPack &texPack = ResourceManager::GetSingleton().GetTexPack(
		mFrameTexPack);

	if (!texPack.IsValid())
		return false;

	mActiveIndex = 0;
	mElements.clear();

	for (int i=0; i<(int)texPack.Elements.size(); i++)
	{
		const TexPackElement &ele = texPack.Elements[i];

		float u0 = (float)ele.X/(float)ele.TexWidth;
		float u1 = (float)(ele.X+ele.W)/(float)ele.TexWidth;
		float v0 = (float)(ele.TexHeight-ele.Y-ele.H)/(float)ele.TexHeight;
		float v1 = (float)(ele.TexHeight-ele.Y)/(float)ele.TexHeight;

		UIAnimPicBoxEle animEle;
		animEle.Index = i;
		animEle.Tex = DynamicCast<Texture2D>(
			ResourceManager::GetSingleton().BlockLoad(ele.ImagePathFull));

		if (!ele.Rolated)
		{
			animEle.UV0 = Float2(u0, v0);
			animEle.UV1 = Float2(u1, v0);
			animEle.UV2 = Float2(u0, v1);
			animEle.UV3 = Float2(u1, v1);
		}
		else
		{
			animEle.UV0 = Float2(u0, v1);
			animEle.UV1 = Float2(u0, v0);
			animEle.UV2 = Float2(u1, v1);
			animEle.UV3 = Float2(u1, v0);
		}

		mElements.push_back(animEle);
	}

	SetIntervalTime(mIntervalTime);
	SetActiveIndex(0);

	return true;
}
//----------------------------------------------------------------------------
bool UIAnimPicBox::AddFrameTex (const std::string &filename)
{
	Texture2DPtr tex = DynamicCast<Texture2D>(ResourceManager::GetSingleton()
		.BlockLoad(filename));
	if (!tex)
	{
		assertion(false, "UIAnimPicBox::AddFrameTe failed.\n");
		return false;
	}

	UIAnimPicBoxEle ele;
	ele.Index = (int)mElements.size();
	ele.UV0 = Float2(0.0f, 0.0f);
	ele.UV1 = Float2(1.0f, 0.0f);
	ele.UV2 = Float2(0.0f, 1.0f);
	ele.UV3 = Float2(1.0f, 1.0f);
	ele.Tex = tex;
	mElements.push_back(ele);

	SetIntervalTime(mIntervalTime);
	SetActiveIndex(0);

	return true;
}
//----------------------------------------------------------------------------
void UIAnimPicBox::ClearFrames()
{
	mActiveIndex = 0;
	mElements.clear();
}
//----------------------------------------------------------------------------
void UIAnimPicBox::SetIntervalTime (float seconds)
{
	if (0.0f == seconds)
		seconds = 0.03f;

	mIntervalTime = seconds;

	mAPBCtrl->MinTime = 0.0f;
	mAPBCtrl->MaxTime = GetNumFrames() * mIntervalTime;
}
//----------------------------------------------------------------------------
void UIAnimPicBox::SetActiveIndex (int index)
{
	int numAnim = GetNumFrames();
	if (0 == numAnim)
		return;

	if (index < 0)
		index = 0;

	if (index >= numAnim)
		index = numAnim-1;

	mActiveIndex = index;

	mUV0 = mElements[mActiveIndex].UV0;
	mUV1 = mElements[mActiveIndex].UV1;
	mUV2 = mElements[mActiveIndex].UV2;
	mUV3 = mElements[mActiveIndex].UV3;

	UpdateVertexBuffer();

	SetTexture(mElements[mActiveIndex].Tex);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
UIAnimPicBox::UIAnimPicBox (LoadConstructor value)
	:
UIPicBox(value),
mActiveIndex(0),
mIntervalTime(0.03f)
{
}
//----------------------------------------------------------------------------
void UIAnimPicBox::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIPicBox::Load(source);

	source.ReadPointer(mAPBCtrl);
	source.ReadString(mFrameTexPack);
	source.Read(mIntervalTime);

	int numAnim = 0;
	source.Read(numAnim);
	mElements.resize(numAnim);
	for (int i=0; i<numAnim; i++)
	{
		source.Read(mElements[i].Index);
		source.ReadAggregate(mElements[i].UV0);
		source.ReadAggregate(mElements[i].UV1);
		source.ReadAggregate(mElements[i].UV2);
		source.ReadAggregate(mElements[i].UV3);
		source.ReadPointer(mElements[i].Tex);
	}

	PX2_END_DEBUG_STREAM_LOAD(UIAnimPicBox, source);
}
//----------------------------------------------------------------------------
void UIAnimPicBox::Link (InStream& source)
{
	UIPicBox::Link(source);

	source.ResolveLink(mAPBCtrl);

	int numAnim = (int)mElements.size();
	for (int i=0; i<numAnim; i++)
	{
		source.ResolveLink(mElements[i].Tex);
	}

}
//----------------------------------------------------------------------------
void UIAnimPicBox::PostLink ()
{
	UIPicBox::PostLink();
}
//----------------------------------------------------------------------------
bool UIAnimPicBox::Register (OutStream& target) const
{
	if (UIPicBox::Register(target))
	{
		target.Register(mAPBCtrl);

		int numAnim = (int)mElements.size();
		for (int i=0; i<numAnim; i++)
		{
			target.Register(mElements[i].Tex);
		}

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void UIAnimPicBox::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIPicBox::Save(target);

	target.WritePointer(mAPBCtrl);
	target.WriteString(mFrameTexPack);
	target.Write(mIntervalTime);
	int numAnim = (int)mElements.size();
	target.Write(numAnim);
	for (int i=0; i<numAnim; i++)
	{
		target.Write(mElements[i].Index);
		target.WriteAggregate(mElements[i].UV0);
		target.WriteAggregate(mElements[i].UV1);
		target.WriteAggregate(mElements[i].UV2);
		target.WriteAggregate(mElements[i].UV3);
		target.WritePointer(mElements[i].Tex);
	}

	PX2_END_DEBUG_STREAM_SAVE(UIAnimPicBox, target);
}
//----------------------------------------------------------------------------
int UIAnimPicBox::GetStreamingSize () const
{
	int size = UIPicBox::GetStreamingSize();
	size += PX2_POINTERSIZE(mAPBCtrl);
	size += PX2_STRINGSIZE(mFrameTexPack);
	size += sizeof(mIntervalTime);
	int numAnim = (int)mElements.size();
	size += sizeof(numAnim);
	for (int i=0; i<numAnim; i++)
	{
		size += sizeof(mElements[i].Index);
		size += sizeof(mElements[i].UV0)*4;
		size += PX2_POINTERSIZE(mElements[i].Tex);
	}
	return size;
}
//----------------------------------------------------------------------------
