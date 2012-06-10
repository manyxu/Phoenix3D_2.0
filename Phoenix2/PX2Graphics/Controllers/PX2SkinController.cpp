/*
*
* 文件名称	：	PX2SkinController.cpp
*
*/

#include "PX2SkinController.hpp"
#include "PX2Renderer.hpp"
#include "PX2VertexBufferAccessor.hpp"
#include "PX2Renderable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Controller, SkinController);
PX2_IMPLEMENT_STREAM(SkinController);
PX2_IMPLEMENT_FACTORY(SkinController);
PX2_IMPLEMENT_DEFAULT_NAMES(Controller, SkinController);

//----------------------------------------------------------------------------
SkinController::SkinController (int numVertices, int numBones)
:
mNumVertices(numVertices),
mNumBones(numBones)
{
	mBones = new1<Node*>(mNumBones);
	mWeights = new2<float>(mNumBones, mNumVertices);
	mOffsets = new2<APoint>(mNumBones, mNumVertices);
}
//----------------------------------------------------------------------------
SkinController::~SkinController ()
{
	delete1(mBones);
	delete2(mWeights);
	delete2(mOffsets);
}
//----------------------------------------------------------------------------
bool SkinController::Update (double applicationTime)
{
	if (!Controller::Update(applicationTime))
	{
		return false;
	}

	// 获得要访问的VertexBuffer
	Renderable* renderable = StaticCast<Renderable>(mObject);
	assertion(mNumVertices == renderable->GetVertexBuffer()->GetNumElements(),
		"Controller must have the same number of vertices as the buffer\n");
	VertexBufferAccessor vba(renderable);

	// skin中的网格的顶点在网格的坐标系（世界坐标系）中。mOffsets记录顶点相对各
	// 个骨骼的位置，左乘骨骼变换矩阵得到该骨骼下的网格坐标系位置。

	renderable->WorldTransform = Transform::IDENTITY;
	renderable->WorldTransformIsCurrent = true;

	// 计算skin顶点位置
	for (int vertex = 0; vertex < mNumVertices; ++vertex)
	{
		APoint position = APoint::ORIGIN;
		for (int bone = 0; bone < mNumBones; ++bone)
		{
			float weight = mWeights[vertex][bone];
			if (weight != 0.0f)
			{
				APoint offset = mOffsets[vertex][bone];
				APoint worldOffset = mBones[bone]->WorldTransform*offset;
				position += weight*worldOffset;
			}
		}
		vba.Position<Float3>(vertex) = position;
	}

	renderable->UpdateModelSpace(Renderable::GU_NORMALS);
	Renderer::UpdateAll(renderable->GetVertexBuffer());
	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
SkinController::SkinController (LoadConstructor value)
:
Controller(value),
mNumVertices(0),
mNumBones(0),
mBones(0),
mWeights(0),
mOffsets(0)
{
}
//----------------------------------------------------------------------------
void SkinController::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Controller::Load(source);

	source.Read(mNumVertices);
	source.Read(mNumBones);

	int numWeightsOffsets = mNumVertices*mNumBones;
	mWeights = new2<float>(mNumBones, mNumVertices);
	mOffsets = new2<APoint>(mNumBones, mNumVertices);
	source.ReadVV(numWeightsOffsets, mWeights[0]);
	source.ReadAggregateVV(numWeightsOffsets, mOffsets[0]);

	source.ReadPointerVR(mNumBones, mBones);

	PX2_END_DEBUG_STREAM_LOAD(SkinController, source);
}
//----------------------------------------------------------------------------
void SkinController::Link (InStream& source)
{
	Controller::Link(source);

	source.ResolveLink(mNumBones, mBones);
}
//----------------------------------------------------------------------------
void SkinController::PostLink ()
{
	Controller::PostLink();
}
//----------------------------------------------------------------------------
bool SkinController::Register (OutStream& target) const
{
	if (Controller::Register(target))
	{
		target.Register(mNumBones, mBones);
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void SkinController::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Controller::Save(target);

	target.Write(mNumVertices);
	target.Write(mNumBones);

	int numWeightsOffsets = mNumVertices*mNumBones;
	target.WriteN(numWeightsOffsets, mWeights[0]);
	target.WriteAggregateN(numWeightsOffsets, mOffsets[0]);

	target.WritePointerN(mNumBones, mBones);

	PX2_END_DEBUG_STREAM_SAVE(SkinController, target);
}
//----------------------------------------------------------------------------
int SkinController::GetStreamingSize () const
{
	int size = Controller::GetStreamingSize();
	size += sizeof(mNumVertices);
	size += sizeof(mNumBones);

	int numWeightsOffsets = mNumVertices*mNumBones;
	size += numWeightsOffsets*sizeof(mWeights[0][0]);
	size += numWeightsOffsets*sizeof(mOffsets[0][0]);

	size += mNumBones*PX2_POINTERSIZE(mBones[0]);

	return size;
}
//----------------------------------------------------------------------------