/*
*
* 文件名称	：	PX2ParticleEmitter.cpp
*
*/

#include "PX2ParticleEmitter.hpp"
#include "PX2ParticleEmitterControl.hpp"
#include "PX2ResourceManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, TriMesh, ParticleEmitter);
PX2_IMPLEMENT_STREAM(ParticleEmitter);
PX2_IMPLEMENT_FACTORY(ParticleEmitter);
PX2_IMPLEMENT_DEFAULT_NAMES(TriMesh, ParticleEmitter);

//----------------------------------------------------------------------------
ParticleEmitter::ParticleEmitter ()
{
	VertexFormat* vformat = VertexFormat::Create(3,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT4, 0);

	SetVertexFormat(vformat);

	mEmitterControl = new0 ParticleEmitterController();
	AttachController(mEmitterControl);

	mEmitterControl->SetMaxQuantity(100);

	UpdateModelBound();

	mMaterial = new0 EffectMaterial("Data/Materials/Effect.pxfx");
	mMaterial->GetAlphaProperty(0, 0)->BlendEnabled = true;
	mMaterial->GetAlphaProperty(0, 0)->SrcBlend = AlphaProperty::SBM_ONE;
	mMaterial->GetAlphaProperty(0, 0)->DstBlend = AlphaProperty::DBM_ONE;
	mMaterial->GetDepthProperty(0, 0)->Writable = false;
	mMaterial->GetPixelShader(0, 0)->SetFilter(0, Shader::SF_NEAREST);

	mMaterialInstance = new0 MaterialInstance(mMaterial, 0);
	mMaterialInstance->SetVertexConstant(0, "gPVWMatrix", 
		new0 PVWMatrixConstant());
	SetTexture("Data/Images/Effect/Particle.dds");
	SetMaterialInstance(mMaterialInstance);
}
//----------------------------------------------------------------------------
ParticleEmitter::~ParticleEmitter ()
{

}
//----------------------------------------------------------------------------
void ParticleEmitter::SetTexture (Texture2D *texture)
{
	mTexture = texture;
	mMaterialInstance->SetPixelTexture(0, "BaseSampler", mTexture);
}
//----------------------------------------------------------------------------
void ParticleEmitter::SetTexture (std::string filename)
{
	mTexture = DynamicCast<Texture2D>(PX2::ResourceManager::GetSingleton()
		.BlockLoad(filename));

	assertion(mTexture!=0, "Load texture %s failed.", filename.c_str());

	SetTexture(mTexture);
}
//----------------------------------------------------------------------------
void ParticleEmitter::GenerateParticles (const Camera* camera)
{ 
	assertion(camera!=0, "camera must exist\n");
	if (!camera)
		return;

	VertexBufferAccessor vba(mVFormat, mVBuffer);
	assertion(vba.HasPosition(), "Positions must exist\n");

	// 计算在粒子模型坐标系下的相机方向
	AVector UpR = WorldTransform.Inverse()*(camera->GetUVector() +
		camera->GetRVector());
	AVector UmR = WorldTransform.Inverse()*(camera->GetUVector() -
		camera->GetRVector());

	int vertexIndex = 0;
	TRecyclingArray<Particle> *arr = mEmitterControl->GetArray();
	for (int i=0; i<arr->GetQuantity(); i++)
	{
		if (!arr->IsUsed(i))
			continue;

		Particle &particle = arr->GetAt(i);

		AVector scaledUpR = UpR * particle.SizeU;
		AVector scaledUmR = UmR * particle.SizeR;

		APoint position = particle.Pos;
		Float4 color;
		color[0] = particle.Color[0];
		color[1] = particle.Color[1];
		color[2] = particle.Color[2];
		color[3] = particle.Alpha;

		vba.Position<Float3>(vertexIndex) = position - scaledUpR;
		vba.Color<Float4>(0, vertexIndex) = color;
		vertexIndex++;

		vba.Position<Float3>(vertexIndex) = position - scaledUmR;
		vba.Color<Float4>(0, vertexIndex) = color;
		vertexIndex++;

		vba.Position<Float3>(vertexIndex) = position + scaledUpR;
		vba.Color<Float4>(0, vertexIndex) = color;
		vertexIndex++;

		vba.Position<Float3>(vertexIndex) = position + scaledUmR;
		vba.Color<Float4>(0, vertexIndex) = color;
		vertexIndex++;

		mVBuffer->SetNumElements(vertexIndex);
		mIBuffer->SetNumElements((int)(1.5f*vertexIndex));
	}

	UpdateModelSpace(GU_MODEL_BOUND_ONLY);
	Renderer::UpdateAll(mVBuffer);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
ParticleEmitter::ParticleEmitter (LoadConstructor value)
:
TriMesh(value)
{
}
//----------------------------------------------------------------------------
void ParticleEmitter::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	TriMesh::Load(source);
	
	source.ReadPointer(mEmitterControl);
	source.ReadPointer(mMaterial);
	source.ReadPointer(mMaterialInstance);
	source.ReadPointer(mTexture);

	PX2_END_DEBUG_STREAM_LOAD(ParticleEmitter, source);
}
//----------------------------------------------------------------------------
void ParticleEmitter::Link (InStream& source)
{
	TriMesh::Link(source);

	source.ResolveLink(mEmitterControl);
	source.ResolveLink(mMaterial);
	source.ResolveLink(mMaterialInstance);
	source.ResolveLink(mTexture);

	GetVertexBuffer()->SetNumElements(0);
}
//----------------------------------------------------------------------------
void ParticleEmitter::PostLink ()
{
	TriMesh::PostLink();
}
//----------------------------------------------------------------------------
bool ParticleEmitter::Register (OutStream& target) const
{
	if (TriMesh::Register(target))
	{
		target.Register(mEmitterControl);
		target.Register(mMaterial);
		target.Register(mMaterialInstance);
		target.Register(mTexture);

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void ParticleEmitter::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	TriMesh::Save(target);

	target.WritePointer(mEmitterControl);
	target.WritePointer(mMaterial);
	target.WritePointer(mMaterialInstance);
	target.WritePointer(mTexture);

	PX2_END_DEBUG_STREAM_SAVE(ParticleEmitter, target);
}
//----------------------------------------------------------------------------
int ParticleEmitter::GetStreamingSize () const
{
	int size = TriMesh::GetStreamingSize()
		+ PX2_POINTERSIZE(mEmitterControl)
		+ PX2_POINTERSIZE(mMaterial)
		+ PX2_POINTERSIZE(mMaterialInstance)
		+ PX2_POINTERSIZE(mTexture);

	return size;
}
//----------------------------------------------------------------------------
