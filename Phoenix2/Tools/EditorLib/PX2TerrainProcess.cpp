/*
*
* 文件名称	：	PX2TerrainProcess.cpp
*
*/

#include "PX2TerrainProcess.hpp"

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
		RawTerrainPagePtr page = info.InfulencedPage;
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

			if (mHeightMode == HM_RAISE)
				pos[2] += strength * weight;
			else if (mHeightMode == HM_LOWER)
				pos[2] -= strength * weight;
			else if (mHeightMode == HM_FLATTEN)
			{
				pos[2] = PageAffectInfo::AverageHeight;
			}
			else if (mHeightMode == HM_SMOOTH)
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

		info.InfulencedPage->UpdateToHighField();
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

			if (layerTex)
				it->InfulencedPage->SetTexture(mSelectedLayerIndex, layerTex);

			Texture2D *tex = it->InfulencedPage->GetTextureAlpha();
			char *buffer = tex->GetData(0);

			int width = tex->GetWidth();
			int height = tex->GetHeight();
			PX2_UNUSED(width);
			PX2_UNUSED(height);

			for (int i=0; i<(int)it->VertexInfoList.size(); i++)
			{
				int index = it->VertexInfoList[i].Index;
				char *b = &buffer[4*index  ]; // B
				char *g = &buffer[4*index+1]; // G
				char *r = &buffer[4*index+2]; // R
				char *a = &buffer[4*index+3]; // A

				float strength = mBrush->GetStrength();
				int add = (int)(it->VertexInfoList[i].Weight * 255 * strength);
				if (mTextureMode == TM_DECREASE)
					add = -add;

				int val = 0;
				if (mSelectedLayerIndex == 1)
				{
					val = (unsigned char)(*r); //< 必须是unsigned 
					val += add;
					*r = (char)(PX2::Math<int>::Clamp(val, 0, 255));

					//float left = 1.0f - (float)(*r)/255.0f;
					//*b = (char)(*b * left);
					//*g = (char)(*g * left);
					//*a = (char)(*a * left);
				}
				else if (mSelectedLayerIndex == 2)
				{
					val = (unsigned char)(*g); //< 必须是unsigned 
					val += add;
					*g = (char)(PX2::Math<int>::Clamp(val, 0, 255));

					//float left = 1.0f - (float)(*g)/255.0f;
					//*r = (char)(*r * left);
					//*b = (char)(*b * left);
					//*a = (char)(*a * left);
				}
				else if (mSelectedLayerIndex == 3)
				{
					val = (unsigned char)(*b); //< 必须是unsigned 
					val += add;
					val = (char)(PX2::Math<int>::Clamp(val, 0, 255));
					*b = (char)(255);

					//float left = 1.0f - (float)(*b)/255.0f;
					//*g = (char)(*g * left);
					//*r = (char)(*r * left);
					//*a = (char)(*a * left);
				}
				else if (mSelectedLayerIndex == 4)
				{
					val = (unsigned char)(*a); //< 必须是unsigned 
					val += add;
					*a = (char)(PX2::Math<int>::Clamp(val, 0, 255));

					//float left = 1.0f - (float)(*a)/255.0f;
					//*b = (char)(*b * left);
					//*g = (char)(*g * left);
					//*r = (char)(*r * left);
				}
			}

			Renderer::UpdateAll(tex, 0);
		}
	}
}
//----------------------------------------------------------------------------