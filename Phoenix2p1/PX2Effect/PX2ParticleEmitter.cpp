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
	:
mEffectPlayType(EPT_FOREVER),
mEffectPlayLife(10.0f),
mIsPlaying(false),
mIsFixedBound(true),
mFixedBoundRadius(5.0f),
mIsLocal(false),
mFaceType(FT_CAMERA),
mRotateAxisType(RAT_D)
{
	VertexFormat* vformat = VertexFormat::Create(3,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT4, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);

	SetVertexFormat(vformat);

	mMaterial = new0 EffectMaterial();
	mMaterial->GetCullProperty(0, 0)->Enabled = false;
	mMaterialInstance = new0 MaterialInstance(mMaterial, 0);
	SetTexture("Data/engine/star.png");
	SetMaterialInstance(mMaterialInstance);
	SetLocal(false);
	SetFaceType(FT_CAMERA);
	SetRotateAxisType(RAT_D);
	SetBlendMode(2);

	mEmitterControl = new0 ParticleEmitterController();
	AttachController(mEmitterControl);
	mEmitterControl->SetMaxNumParticles(100);

	SetFixedBound(true);

	if (!mIsFixedBound)
	{
		UpdateModelBound();
	}
}
//----------------------------------------------------------------------------
ParticleEmitter::~ParticleEmitter ()
{
}
//----------------------------------------------------------------------------
void ParticleEmitter::SetEffectPlayType (EffectPlayType type)
{
	mEffectPlayType = type;
}
//----------------------------------------------------------------------------
void ParticleEmitter::Play ()
{
	mEmitterControl->Reset();
	mIsPlaying = true;
}
//----------------------------------------------------------------------------
void ParticleEmitter::Stop ()
{
	mIsPlaying = false;
}
//----------------------------------------------------------------------------
void ParticleEmitter::SetFixedBound (bool fixed)
{
	mIsFixedBound = fixed;

	if (mIsFixedBound)
	{
		mModelBound.SetRadius(mFixedBoundRadius);
	}
}
//----------------------------------------------------------------------------
void ParticleEmitter::SetFixedBoundCenter (const APoint &center)
{
	mFixedCenter = center;

	if (mIsFixedBound)
	{
		mModelBound.SetCenter(mFixedCenter);
	}
}
//----------------------------------------------------------------------------
void ParticleEmitter::SetFixedBoundRadius (float radius)
{
	mFixedBoundRadius = radius;

	if (mIsFixedBound)
	{
		mModelBound.SetRadius(mFixedBoundRadius);
	}
}
//----------------------------------------------------------------------------
void ParticleEmitter::SetLocal (bool l)
{
	if (!mMaterialInstance)
		return;

	mIsLocal = l;

	if (mIsLocal)
	{
		mMaterialInstance->SetVertexConstant(0, "gPVWMatrix",
			new0 PVWMatrixConstant());
	}
	else
	{
		mMaterialInstance->SetVertexConstant(0, "gPVWMatrix", 
			new0 PVMatrixConstant());
	}

	if (mEmitterControl)
		mEmitterControl->Reset();
}
//----------------------------------------------------------------------------
void ParticleEmitter::SetFaceType (FaceType type)
{
	mFaceType = type;
}
//----------------------------------------------------------------------------
void ParticleEmitter::SetRotateAxisType (RotateAxisType type)
{
	mRotateAxisType = type;
}
//----------------------------------------------------------------------------
void ParticleEmitter::SetBlendMode (int mode)
{
	mBlendMode = mode;

	if (!mMaterial)
		return;

	bool BlendEnabled = false;
	AlphaProperty::SrcBlendMode SrcBlend = AlphaProperty::SBM_SRC_ALPHA;
	AlphaProperty::DstBlendMode DstBlend = AlphaProperty::DBM_ONE_MINUS_SRC_ALPHA;
	bool CompareEnabled = false;
	AlphaProperty::CompareMode Compare = AlphaProperty::CM_ALWAYS;
	float Reference = 0.0f;

	if (0 == mode)
	{
		BlendEnabled = false;
		CompareEnabled = false;
	}
	else if (1 == mode)
	{
		BlendEnabled = false;
		CompareEnabled = true;
		Reference = 0.33f;
		Compare = AlphaProperty::CM_GEQUAL;
	}
	else if (2 == mode)
	{
		BlendEnabled = true;
		SrcBlend = AlphaProperty::SBM_SRC_ALPHA;
		DstBlend = AlphaProperty::DBM_ONE_MINUS_SRC_ALPHA;
		CompareEnabled = true;
		Reference = 0.0f;
		Compare = AlphaProperty::CM_GREATER;
	}
	else if (3 == mode)
	{
		BlendEnabled = true;
		SrcBlend = AlphaProperty::SBM_ONE;
		DstBlend = AlphaProperty::DBM_ONE_MINUS_SRC_ALPHA;
		CompareEnabled = false;
	}
	else if (4 == mode)
	{
		BlendEnabled = true;
		SrcBlend = AlphaProperty::SBM_ONE;
		DstBlend = AlphaProperty::DBM_ONE;
		CompareEnabled = false;
	}
	else if (5 == mode)
	{
		BlendEnabled = true;
		SrcBlend = AlphaProperty::SBM_DST_COLOR;
		DstBlend = AlphaProperty::DBM_ZERO;
		CompareEnabled = false;
	}
	else if (6 == mode)
	{
		BlendEnabled = true;
		SrcBlend = AlphaProperty::SBM_DST_COLOR;
		DstBlend = AlphaProperty::DBM_SRC_COLOR;
		CompareEnabled = false;
	}

	AlphaProperty *aProp = mMaterial->GetAlphaProperty(0, 0);
	aProp->BlendEnabled = BlendEnabled;
	aProp->SrcBlend = SrcBlend;
	aProp->DstBlend = DstBlend;
	aProp->CompareEnabled = CompareEnabled;
	aProp->Compare = Compare;
	aProp->Reference = Reference;

	if (0==mode || 1==mode)
	{
		mMaterial->GetDepthProperty(0, 0)->Writable = true;
		mMaterial->GetDepthProperty(0, 0)->Enabled = true;
	}
	else
	{
		mMaterial->GetDepthProperty(0, 0)->Writable = false;
		mMaterial->GetDepthProperty(0, 0)->Enabled = true;
	}
}
//----------------------------------------------------------------------------
void ParticleEmitter::SetTexture (Texture2D *texture)
{
	mTexture = texture;
	mMaterialInstance->SetPixelTexture(0, "gDiffuseSampler", mTexture);
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
void ParticleEmitter::GenerateParticles ()
{ 
	VertexBufferAccessor vba(mVFormat, mVBuffer);
	assertion(vba.HasPosition(), "Positions must exist\n");

	// 计算在粒子模型坐标系下的相机方向
	AVector UpR = AVector::UNIT_X;
	AVector UmR = AVector::UNIT_X;

	int vertexIndex = 0;
	TRecyclingArray<Particle> *arr = mEmitterControl->GetArray();
	for (int i=0; i<arr->GetQuantity(); i++)
	{
		if (!arr->IsUsed(i))
			continue;

		Particle &particle = arr->GetAt(i);

		UpR = particle.UVector + particle.RVector;
		UpR.Normalize();
		UmR = particle.UVector - particle.RVector;
		UmR.Normalize();

		if (mIsLocal)
		{
			UpR = WorldTransform.Inverse() * UpR;
			UmR = WorldTransform.Inverse() * UmR;
		}

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
		vba.TCoord<Float2>(0, vertexIndex) = Float2(0.0f, 0.0f);
		vertexIndex++;

		vba.Position<Float3>(vertexIndex) = position - scaledUmR;
		vba.Color<Float4>(0, vertexIndex) = color;
		vba.TCoord<Float2>(0, vertexIndex) = Float2(1.0f, 0.0f);
		vertexIndex++;

		vba.Position<Float3>(vertexIndex) = position + scaledUpR;
		vba.Color<Float4>(0, vertexIndex) = color;
		vba.TCoord<Float2>(0, vertexIndex) = Float2(1.0f, 1.0f);
		vertexIndex++;

		vba.Position<Float3>(vertexIndex) = position + scaledUmR;
		vba.Color<Float4>(0, vertexIndex) = color;
		vba.TCoord<Float2>(0, vertexIndex) = Float2(0.0f, 1.0f);
		vertexIndex++;
	}
	mVBuffer->SetNumElements(vertexIndex);
	mIBuffer->SetNumElements((int)(1.5f*vertexIndex));
	
	if (mIsFixedBound)
	{
		mModelBound.SetRadius(mFixedBoundRadius);
		mModelBound.SetCenter(mFixedCenter);
	}
	else
	{
		UpdateModelSpace(GU_MODEL_BOUND_ONLY);

		if (!mIsLocal)
		{
			APoint center = mModelBound.GetCenter();
			center -= WorldTransform.GetTranslate();
			mModelBound.SetCenter(center);
		}
	}

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
	source.ReadEnum(mEffectPlayType);
	source.Read(mEffectPlayLife);
	source.ReadBool(mIsPlaying);
	source.ReadBool(mIsFixedBound);
	source.ReadAggregate(mFixedCenter);
	source.Read(mFixedBoundRadius);
	source.ReadBool(mIsLocal);
	source.ReadEnum(mFaceType);
	source.ReadEnum(mRotateAxisType);
	source.ReadPointer(mMaterial);
	source.ReadPointer(mMaterialInstance);
	source.Read(mBlendMode);
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
	target.WriteEnum(mEffectPlayType);
	target.Write(mEffectPlayLife);
	target.WriteBool(mIsPlaying);
	target.WriteBool(mIsFixedBound);
	target.WriteAggregate(mFixedCenter);
	target.Write(mFixedBoundRadius);
	target.WriteBool(mIsLocal);
	target.WriteEnum(mFaceType);
	target.WriteEnum(mRotateAxisType);
	target.WritePointer(mMaterial);
	target.WritePointer(mMaterialInstance);
	target.Write(mBlendMode);
	target.WritePointer(mTexture);

	PX2_END_DEBUG_STREAM_SAVE(ParticleEmitter, target);
}
//----------------------------------------------------------------------------
int ParticleEmitter::GetStreamingSize () const
{
	int size = TriMesh::GetStreamingSize()
		+ PX2_POINTERSIZE(mEmitterControl)
		+ PX2_ENUMSIZE(mEffectPlayType)
		+ sizeof(mEffectPlayLife)
		+ PX2_BOOLSIZE(mIsPlaying)
		+ PX2_BOOLSIZE(mIsFixedBound)
		+ sizeof(mFixedCenter)
		+ sizeof(mFixedBoundRadius)
		+ PX2_BOOLSIZE(mIsLocal)
		+ PX2_ENUMSIZE(mFaceType)
		+ PX2_ENUMSIZE(mRotateAxisType)
		+ PX2_POINTERSIZE(mMaterial)
		+ PX2_POINTERSIZE(mMaterialInstance)
		+ sizeof(mBlendMode)
		+ PX2_POINTERSIZE(mTexture);

	return size;
}
//----------------------------------------------------------------------------
