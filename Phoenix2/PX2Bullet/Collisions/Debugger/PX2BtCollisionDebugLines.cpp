/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionDebugLines.cpp
*
*/

#include "PX2BtCollisionDebugLines.hpp"
using namespace TdBt;
using namespace PX2;

//----------------------------------------------------------------------------
DebugLines::DebugLines ()
{
	mVFormat = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT4, 0);

	mMaterial = new0 VertexColor4Material();

	mDrawn = false;
	mMaxNumPoints = 0;
}
//----------------------------------------------------------------------------
DebugLines::~DebugLines ()
{ 
    Clear();
}
//----------------------------------------------------------------------------
void DebugLines::AddLine (const PX2::APoint &start, const PX2::APoint &end)
{
	Clear();

	mPoints.push_back(start);
	mPoints.push_back(end);
}
//----------------------------------------------------------------------------
void DebugLines::AddLine (float startX, float startY, float startZ, float endX,
			  float endY, float endZ)
{
	AddLine(PX2::APoint(startX, startY, startZ), PX2::APoint(endX, endY, endZ)); 
}
//----------------------------------------------------------------------------
void DebugLines::Clear ()
{
	if (mDrawn)
	{
		mDrawn = false;
		mPoints.clear();
	}
}
//----------------------------------------------------------------------------
void DebugLines::Draw (PX2::Renderer *renderer)
{
	int numPoints = (int)mPoints.size();

	if (mMaxNumPoints < numPoints)
	{
		mMaxNumPoints = numPoints;
		mVBuffer = new0 VertexBuffer(mMaxNumPoints, mVFormat->GetStride(),
			Buffer::BU_DYNAMIC);
		mSegment = new0 Polysegment(mVFormat, mVBuffer, false);
		mSegment->SetMaterialInstance(mMaterial->CreateInstance());
	}

	if (mSegment)
	{
		VertexBufferAccessor vba;
		vba.ApplyTo(mSegment);
		for (int i=0; i<numPoints; i++)
		{
			vba.Position<Float3>(i) = Float3(mPoints[i].X(), mPoints[i].Y(), 
				mPoints[i].Z());
			vba.Color<Float4>(0, i) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
		}
		mVBuffer->SetNumElements(numPoints);

		Renderer::UpdateAll(mVBuffer);

		if (numPoints > 0)
			renderer->Draw(mSegment);
	}

	mDrawn = true;
}
//----------------------------------------------------------------------------