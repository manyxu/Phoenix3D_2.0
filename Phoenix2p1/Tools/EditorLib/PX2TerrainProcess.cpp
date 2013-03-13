/*
*
* 文件名称	：	PX2TerrainProcess.cpp
*
*/

#include "PX2TerrainProcess.hpp"
#include "PX2EditSystem.hpp"

#pragma warning(disable : 4310)

using namespace PX2Editor;
using namespace PX2;

TerrainProcess::TerrainProcess ()
{
	mTerProType = TPT_MAX_TYPE;
}
//----------------------------------------------------------------------------
TerrainProcess::TerrainProcess (TerProType type)
:
mTerProType(type)
{
}
//----------------------------------------------------------------------------
TerrainProcess::~TerrainProcess ()
{
}
//----------------------------------------------------------------------------
TerrainProcess::TerProType TerrainProcess::GetTerProType()
{
	return mTerProType;
}
//----------------------------------------------------------------------------
void TerrainProcess::Apply ()
{

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// TerrainHeightProcess
//----------------------------------------------------------------------------
TerrainHeightProcess::TerrainHeightProcess ()
:
TerrainProcess(TerrainProcess::TPT_HEIGHT),
mHeightMode(HM_RAISE)
{
}
//----------------------------------------------------------------------------
TerrainHeightProcess::~TerrainHeightProcess ()
{
}
//----------------------------------------------------------------------------
void TerrainHeightProcess::Apply ()
{
	if (!mTerrain)
		return;

	float strength = mBrush->GetStrength();
	mBrush->CalculateInfulencedInfo();
	std::vector<PageAffectInfo> &infos = mBrush->GetInfulencedInfo();
	
	std::vector<PageAffectInfo>::iterator it = infos.begin();
	for (; it!=infos.end(); it++)
	{
		PageAffectInfo &info = *it;
		TerrainPagePtr page = info.InfulencedPage;
		int size = page->GetSize();
		PX2_UNUSED(size);
		VertexBufferPtr vBuffer = page->GetVertexBuffer();
		VertexBufferAccessor vba;
		vba.ApplyTo(page);

		for (int j=0; j<(int)info.VertexInfoList.size(); j++)
		{
			int vertexIndex = info.VertexInfoList[j].Index;

			float weight = info.VertexInfoList[j].Weight;
			Float3 &pos = vba.Position<Float3>(vertexIndex);
			Float3 &normal = vba.Normal<Float3>(vertexIndex);

			bool isShiftDown = EditSystem::GetSingleton().IsShiftDown();

			HeightMode heightMode = mHeightMode;
			if (isShiftDown)
				heightMode = HM_SMOOTH;

			if (heightMode == HM_RAISE)
				pos[2] += strength * weight;
			else if (heightMode == HM_LOWER)
				pos[2] -= strength * weight;
			else if (heightMode == HM_FLATTEN)
			{
				pos[2] = PageAffectInfo::AverageHeight;
			}
			else if (heightMode == HM_SMOOTH)
			{
				if (weight <= 1.0f)
				{
					float x = pos[0];
					float y = pos[1];
					float spacing = mTerrain->GetSpacing();

					float height = mTerrain->GetHeight(x, y);
					float heightL1 = mTerrain->GetHeight(x-spacing, y);
					float heightR1 = mTerrain->GetHeight(x+spacing, y);
					float heightD1 = mTerrain->GetHeight(x, y-spacing);
					float HeightU1 = mTerrain->GetHeight(x, y+spacing);

					pos[2] = (height + heightL1 + heightR1 + heightD1 + HeightU1)/5.0f;
				}
			}
			else if (heightMode == HM_ZERO)
			{
				pos[2] = 0.0f;
			}

			RawTerrain *terrain = DynamicCast<RawTerrain>(
				info.InfulencedPage->GetParent());
			if (terrain)
			{
				AVector nor = terrain->GetNormal(pos[0], pos[1]);
				normal = Float3(nor.X(), nor.Y(), nor.Z());
			}
		}

		PX2::Renderer::UpdateAll(vBuffer);
	}

	it = infos.begin();
	for (; it!=infos.end(); it++)
	{
		PageAffectInfo &info = *it;

		TerrainPage *page = info.InfulencedPage;
		RawTerrainPage *rawPage = DynamicCast<RawTerrainPage>(page);
		if (rawPage)
			rawPage->UpdateToHighField();
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// TerrainTextureProcess
//----------------------------------------------------------------------------
TerrainTextureProcess::TerrainTextureProcess ()
:
TerrainProcess(TerrainProcess::TPT_TEXTURE),
mTextureMode(TM_INCREASE),
mSelectedLayerIndex(0)
{
}
//----------------------------------------------------------------------------
TerrainTextureProcess::~TerrainTextureProcess ()
{

}
//----------------------------------------------------------------------------
void TerrainTextureProcess::SetLayerUsingTexture (int layerIndex,
												  PX2::Texture2D *texture)
{
	mLayerTextures[layerIndex] = texture;
}
//----------------------------------------------------------------------------
PX2::Texture2D *TerrainTextureProcess::GetLayerUsingTexture (int layerIndex)
{
	std::map<int, PX2::Texture2DPtr>::iterator it = mLayerTextures.begin();

	for (; it!=mLayerTextures.end(); it++)
	{
		if (it->first == layerIndex)
			return it->second;
	}

	return 0;
}
//----------------------------------------------------------------------------
void TerrainTextureProcess::SetSelectedLayerUsingTexture (
	PX2::Texture2D *texture)
{
	SetLayerUsingTexture(mSelectedLayerIndex, texture);
}
//----------------------------------------------------------------------------
PX2::Texture2D *TerrainTextureProcess::GetSelectedLayerUsingTexture ()
{
	return GetLayerUsingTexture(mSelectedLayerIndex);
}
//----------------------------------------------------------------------------
void TerrainTextureProcess::Apply ()
{
	if (!mTerrain)
		return;

	float strength = mBrush->GetStrength();
	PX2_UNUSED(strength);

	mBrush->CalculateInfulencedInfo();
	std::vector<PageAffectInfo> &infos = mBrush->GetInfulencedInfo();

	std::vector<PageAffectInfo>::iterator it = infos.begin();
	for (; it!=infos.end(); it++)
	{
		bool isCenter = it->CenterPage;
		PX2_UNUSED(isCenter);
	//	if (isCenter)
		{
			Texture2D *layerTex = GetSelectedLayerUsingTexture();
			TerrainPage *page = it->InfulencedPage;
			RawTerrainPage *rawPage = DynamicCast<RawTerrainPage>(page);
			if (!rawPage)
				return;

			if (layerTex)
			{
				rawPage->SetTexture(mSelectedLayerIndex, layerTex);
			}

			Texture2D *tex = rawPage->GetTextureAlpha();
			char *buffer = tex->GetData(0);

			int width = tex->GetWidth();
			int height = tex->GetHeight();
			PX2_UNUSED(width);
			PX2_UNUSED(height);

			for (int i=0; i<(int)it->VertexInfoList.size(); i++)
			{
				int index = it->VertexInfoList[i].Index;
				unsigned char *b = (unsigned char*)&buffer[4*index  ]; // B 必须是unsigned char
				unsigned char *g = (unsigned char*)&buffer[4*index+1]; // G
				unsigned char *r = (unsigned char*)&buffer[4*index+2]; // R
				unsigned char *a = (unsigned char*)&buffer[4*index+3]; // A
				int iR = *r;
				int iG = *g;
				int iB = *b;
				int iA = *a;

				float strength = mBrush->GetStrength();
				int add = (int)(it->VertexInfoList[i].Weight * 255 * strength);
				if (mTextureMode == TM_DECREASE)
					add = -add;

				int val = 0;
				if (mSelectedLayerIndex == 0)
				{
					if (add > 0)
					{
						iR -= add/2;
						iB -= add/2;
						iG -= add/2;
						iA -= add/2;

						*r = PX2::Math<int>::Clamp(iR, 0, 255);
						*b = PX2::Math<int>::Clamp(iB, 0, 255);
						*g = PX2::Math<int>::Clamp(iG, 0, 255);
						*a = PX2::Math<int>::Clamp(iA, 0, 255);
					}
				}
				else if (mSelectedLayerIndex == 1)
				{
					val = (*r);
					val += add;
					val = PX2::Math<int>::Clamp(val, 0, 255);
					*r = val;

					if (add > 0)
					{
						iB -= add/2;
						iG -= add/2;
						iA -= add/2;

						*b = PX2::Math<int>::Clamp(iB, 0, 255);
						*g = PX2::Math<int>::Clamp(iG, 0, 255);
						*a = PX2::Math<int>::Clamp(iA, 0, 255);
					}
				}
				else if (mSelectedLayerIndex == 2)
				{
					val = (*g); //< 必须是unsigned 

					val += add;
					val = (PX2::Math<int>::Clamp(val, 0, 255));
					*g = (unsigned char)val;

					if (add > 0)
					{
						iR -= add/2;
						iB -= add/2;
						iA -= add/2;

						*r = PX2::Math<int>::Clamp(iR, 0, 255);
						*b = PX2::Math<int>::Clamp(iB, 0, 255);
						*a = PX2::Math<int>::Clamp(iA, 0, 255);
					}
				}
				else if (mSelectedLayerIndex == 3)
				{
					val = (*b); //< 必须是unsigned 
					val += add;
					val = (PX2::Math<int>::Clamp(val, 0, 255));
					*b = (unsigned char)val;

					if (add > 0)
					{
						iG -= add/2;
						iR -= add/2;
						iA -= add/2;

						*g = PX2::Math<int>::Clamp(iG, 0, 255);
						*r = PX2::Math<int>::Clamp(iR, 0, 255);
						*a = PX2::Math<int>::Clamp(iA, 0, 255);
					}
				}
				else if (mSelectedLayerIndex == 4)
				{
					val = (*a); //< 必须是unsigned 
					val += add;
					val = (PX2::Math<int>::Clamp(val, 0, 255));
					*a = (unsigned char)val;

					if (add > 0)
					{
						iB -= add/2;
						iG -= add/2;
						iR -= add/2;

						*b = PX2::Math<int>::Clamp(iB, 0, 255);
						*g = PX2::Math<int>::Clamp(iG, 0, 255);
						*r = PX2::Math<int>::Clamp(iR, 0, 255);
					}
				}
			}

			Renderer::UpdateAll(tex, 0);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// TerrainJunglerProcess
//----------------------------------------------------------------------------
TerrainJunglerProcess::TerrainJunglerProcess ()
	:
TerrainProcess(TerrainProcess::TPT_JUNGLER),
mMode(JM_ADD),
mWidth(1.0f),
mHeight(2.0f),
mLower(0.0f)
{
}
//----------------------------------------------------------------------------
TerrainJunglerProcess::~TerrainJunglerProcess ()
{
}
//----------------------------------------------------------------------------
void TerrainJunglerProcess::SetWidth (float width)
{
	mWidth = width;
}
//----------------------------------------------------------------------------
void TerrainJunglerProcess::SetHeight (float height)
{
	mHeight = height;
}
//----------------------------------------------------------------------------
void TerrainJunglerProcess::SetLower (float lower)
{
	mLower = lower;
}
//----------------------------------------------------------------------------
void TerrainJunglerProcess::Apply ()
{
	if (!mTerrain || !mUsingTexture)
		return;

	APoint pos = mBrush->GetPos();
	float size = mBrush->GetSize();
	float strength = mBrush->GetStrength();

	if (JM_ADD == mMode)
	{
		mTerrain->AddJunglers(mUsingTexture, pos, size, 
			(int)(strength*1000.0f), mWidth, mHeight, mLower);
	}
	else if (JM_REDUCE == mMode)
	{
		mTerrain->RemoveJunglers(mUsingTexture, pos, size, 
			(int)(strength*1000.0f));
	}
}
//----------------------------------------------------------------------------