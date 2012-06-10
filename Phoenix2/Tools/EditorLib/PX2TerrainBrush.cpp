/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainBrush.cpp
*
*/

#include "PX2TerrainBrush.hpp"
#include "PX2EditEventType.hpp"
using namespace PX2Editor;
using namespace PX2;

float PageAffectInfo::AverageHeight = 0.0f;
int PageAffectInfo::VertexNum = 0;
//----------------------------------------------------------------------------
TerrainBrush::TerrainBrush ()
{
	mInterplateMode = IM_COS;

	mVertexFormat = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT3, 0);
	int vstride = mVertexFormat->GetStride();
	PX2_UNUSED(vstride);

	StandardMesh sdm(mVertexFormat, false);
	
	mCircleSegment = sdm.Circle(1.0f, 25);
	mCircleSegment->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());

	SetSize(4.0f);
	SetStrength(0.04f);
}
//----------------------------------------------------------------------------
TerrainBrush::~TerrainBrush ()
{

}
//----------------------------------------------------------------------------
void TerrainBrush::SetPos (PX2::APoint pos)
{
	Brush::SetPos(pos);

	mCircleSegment->LocalTransform.SetTranslate(pos);
	mCircleSegment->Update();
}
//----------------------------------------------------------------------------
void TerrainBrush::SetSize (float size)
{
	Brush::SetSize(size);

	mCircleSegment->LocalTransform.SetUniformScale(size);
	mCircleSegment->Update();
}
//----------------------------------------------------------------------------
void TerrainBrush::SelectPage ()
{
	mPageInfoList.clear();
	PageAffectInfo::AverageHeight = 0.0f;
	PageAffectInfo::VertexNum = 0;

	if (!mTerrain)
		return;

	mSelectedTerrainPage  = mTerrain->GetCurrentPage(mPos.X(), mPos.Y());

	Event *ent = EditorEventSpace::CreateEvent(EditorEventSpace
		::SelectTerrainPage);
	ent->SetData<PX2::RawTerrainPage*>(mSelectedTerrainPage);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
PX2::RawTerrainPage *TerrainBrush::GetSelectedPage ()
{
	return mSelectedTerrainPage;
}
//----------------------------------------------------------------------------
void TerrainBrush::CalculateInfulencedInfo ()
{
	mPageInfoList.clear();
	PageAffectInfo::AverageHeight = 0.0f;
	PageAffectInfo::VertexNum = 0;

	if (!mTerrain)
		return;

	APoint point0;
	APoint point1;
	APoint point2;
	APoint point3;

	float sizeScale = mSize*1.5f;

	point0 = APoint(mPos.X()-sizeScale, mPos.Y()-sizeScale, 0.0f);
	point1 = APoint(mPos.X()+sizeScale, mPos.Y()-sizeScale, 0.0f);
	point2 = APoint(mPos.X()+sizeScale, mPos.Y()+sizeScale, 0.0f);
	point3 = APoint(mPos.X()-sizeScale, mPos.Y()+sizeScale, 0.0f);

	RawTerrainPagePtr page  = mTerrain->GetCurrentPage(mPos.X(), mPos.Y());
	RawTerrainPagePtr page0 = mTerrain->GetCurrentPage(point0.X(), point0.Y());
	RawTerrainPagePtr page1 = mTerrain->GetCurrentPage(point1.X(), point1.Y());
	RawTerrainPagePtr page2 = mTerrain->GetCurrentPage(point2.X(), point2.Y());
	RawTerrainPagePtr page3 = mTerrain->GetCurrentPage(point3.X(), point3.Y());

	if (page)
	{
		PageAffectInfo info;
		info.CenterPage = true;
		info.InfulencedPage = page;
		mPageInfoList.push_back(info);
	}

	if (page0 && page0!=page)
	{
		PageAffectInfo info;
		info.InfulencedPage = page0;
		mPageInfoList.push_back(info);
	}

	if (page1 && page1!=page && page1!=page0)
	{
		PageAffectInfo info;
		info.InfulencedPage = page1;
		mPageInfoList.push_back(info);
	}

	if (page2 && page2!=page && page2!=page0 && page2!=page1)
	{
		PageAffectInfo info;
		info.InfulencedPage = page2;
		mPageInfoList.push_back(info);
	}

	if (page3 && page3!=page && page3!=page0 && page3!=page1 && page3!=page2)
	{
		PageAffectInfo info;
		info.InfulencedPage = page3;
		mPageInfoList.push_back(info);
	}

	for (int i=0; i<(int)mPageInfoList.size(); i++)
	{
		PageAffectInfo &pInfo = mPageInfoList[i];

		pInfo.VertexInfoList.clear();

		RawTerrainPagePtr page = pInfo.InfulencedPage;
		VertexBufferPtr vBuffer = page->GetVertexBuffer();
		VertexBufferAccessor vba;
		vba.ApplyTo(page);

		int vertexNum = vBuffer->GetNumElements();

		for (int j=0; j<vertexNum; j++)
		{
			Float3 vPos = vba.Position<Float3>(j);
			APoint vPoint = APoint(vPos);
			vPoint.Z() = 0.0f;
			APoint center(mPos);
			center.Z() = 0.0f;

			if (vPoint.X() < point0.X() || vPoint.Y() < point0.Y()
				|| vPoint.X() > point2.X() || vPoint.Y() > point2.Y())
			{
				continue;
			}
			else
			{
				VertexAffectInfo vInfo;

				vInfo.Index = j;
				AVector diff = vPoint - center;
				float length = diff.Length();
				vInfo.Length = length;

				if (length <= mSize)
				{
					if (mInterplateMode == IM_NONE)
					{
						vInfo.Weight = 1.0f;
					}
					else if (mInterplateMode == IM_LINER)
					{
						float linear = (mSize-length)/mSize;
						linear = Mathf::Clamp(linear, 0.0f, 1.0f);
						vInfo.Weight = linear;
					}
					else if (mInterplateMode == IM_SQUARE)
					{
						float linear = (mSize-length)/mSize;
						linear = Mathf::Clamp(linear, 0.0f, 1.0f);
						vInfo.Weight = linear*linear;
					}
					else if (mInterplateMode == IM_COS)
					{
						float linear = length/mSize;
						linear = Mathf::Clamp(linear, 0.0f, 1.0f);
						vInfo.Weight = Mathf::Cos(linear*Mathf::HALF_PI);
					}

					PageAffectInfo::AverageHeight += vPos[2];
					PageAffectInfo::VertexNum++;

					pInfo.VertexInfoList.push_back(vInfo);
				}
			}
		}
	}

	PageAffectInfo::AverageHeight /= (float)(PageAffectInfo::VertexNum);
}
//----------------------------------------------------------------------------