/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainEdit.cpp
*
*/

#include "PX2TerrainEdit.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditSystem.hpp"
#include "PX2TerrainEdit.hpp"
#include "PX2EditMap.hpp"
using namespace PX2Editor;
using namespace PX2;

TerrainEdit::TerrainEdit ()
{
	mBrush = new TerrainBrush();
	mHeightProcess = new TerrainHeightProcess();
	mHeightProcess->SetBrush(mBrush);
	mTextureProcess = new TerrainTextureProcess();
	mTextureProcess->SetBrush(mBrush);
	mActiveProcess = mHeightProcess;

	SetEditType(TerrainProcess::TPT_HEIGHT);
}
//----------------------------------------------------------------------------
TerrainEdit::~TerrainEdit ()
{
	if (mHeightProcess)
		delete mHeightProcess;

	if (mTextureProcess)
		delete mTextureProcess;

	if (mBrush)
		delete mBrush;
}
//----------------------------------------------------------------------------
void TerrainEdit::EnableEdit ()
{
	PX2::RawTerrainActor *actor = EditSystem::GetSingleton().GetEditMap()
		->GetScene()->GetRawTerrainActor();

	if (actor)
	{
		mBrush->GetRenderable()->Culling = Renderable::CULL_DYNAMIC;
		SetTerrain(actor->GetTerrain());
	}
	else
	{
		mBrush->GetRenderable()->Culling = Renderable::CULL_ALWAYS;
	}
}
//----------------------------------------------------------------------------
void TerrainEdit::DisableEdit ()
{
	SetTerrain(0);
	
	mBrush->GetRenderable()->Culling = Renderable::CULL_ALWAYS;
}
//----------------------------------------------------------------------------
void TerrainEdit::SetTerrain (RawTerrain *terrain)
{
	mTerrain = terrain;

	if (mBrush)
		mBrush->SetTerrain(terrain);

	if (mHeightProcess)
		mHeightProcess->SetTerrain(terrain);

	if (mTextureProcess)
		mTextureProcess->SetTerrain(terrain);

	if (mTerrain)
		CreateTerrainHelpGrid();
	else
		DestoryTerrainHelpGrid();
}
//----------------------------------------------------------------------------
void TerrainEdit::CreateTerrainHelpGrid ()
{
	EditSystem::GetSingleton().GetHelpScene()->DetachChild(mTerrainHelpGrid);
	mTerrainHelpGrid = 0;

	if (!mTerrain)
		return;

	float pageWidth = (mTerrain->GetSize()-1) * mTerrain->GetSpacing();
	int rowNum = mTerrain->GetRowQuantity();
	int colNum = mTerrain->GetColQuantity();
	float terrainRowWidth = pageWidth*rowNum;
	float terrainColWidth = pageWidth*colNum;

	VertexFormat *format = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT4, 0);

	StandardMesh stdMesh(format);
	mTerrainHelpGrid = stdMesh.LineRectangleForEditor1(rowNum+1, colNum+1, 
		terrainRowWidth/2.0f, terrainColWidth/2.0f, Float4(1.0f, 1.0f, 0.0f, 0.0f));
	mTerrainHelpGrid->SetMaterialInstance(VertexColor4Material
		::CreateUniqueInstance());
	mTerrainHelpGrid->LocalTransform.SetTranslate(APoint(terrainRowWidth/2.0f,
		terrainColWidth/2.0f, 0.0f));

	EditSystem::GetSingleton().GetHelpScene()->AttachChild(mTerrainHelpGrid);
	EditSystem::GetSingleton().GetHelpScene()->Update();
}
//----------------------------------------------------------------------------
void TerrainEdit::DestoryTerrainHelpGrid ()
{
	EditSystem::GetSingleton().GetHelpScene()->DetachChild(mTerrainHelpGrid);
	mTerrainHelpGrid = 0;
	EditSystem::GetSingleton().GetHelpScene()->Update();
}
//----------------------------------------------------------------------------
void TerrainEdit::SetEditType (TerrainProcess::TerProType type)
{
	if (type == TerrainProcess::TPT_HEIGHT)
		mActiveProcess = mHeightProcess;
	else if (type == TerrainProcess::TPT_TEXTURE)
		mActiveProcess = mTextureProcess;
}
//----------------------------------------------------------------------------
TerrainProcess::TerProType TerrainEdit::GetEditType ()
{
	if (mActiveProcess)
		return mActiveProcess->GetTerProType();

	return TerrainProcess::TPT_MAX_TYPE;
}
//----------------------------------------------------------------------------
void TerrainEdit::Apply ()
{
	if (mActiveProcess)
		mActiveProcess->Apply();
}
//----------------------------------------------------------------------------
void TerrainEdit::DoEnter ()
{

}
//----------------------------------------------------------------------------
void TerrainEdit::DoUpdate ()
{

}
//----------------------------------------------------------------------------
void TerrainEdit::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::RemoveActor))
	{
		Actor *actor = event->GetData<Actor*>();

		if (actor->GetMovable() == mTerrain)
		{
			SetTerrain(0);
		}
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::NewScene))
	{

	}
}
//----------------------------------------------------------------------------
void TerrainEdit::DoLeave ()
{

}
//----------------------------------------------------------------------------