/*
*
* 文件名称	：	PX2ParticleEmitterControl.cpp
*
*/

#include "PX2ParticleEmitterControl.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2Movable.hpp"
#include "PX2ParticleEmitter.hpp"
#include "PX2EM_P_LifeInit.hpp"
#include "PX2EM_P_SizeInit.hpp"
#include "PX2EM_P_SizeByAge.hpp"
#include "PX2EM_P_SpeedInit.hpp"
#include "PX2EM_P_SpeedDirInit.hpp"
#include "PX2EM_P_Accelerate.hpp"
#include "PX2EM_P_AccelerateDir.hpp"
#include "PX2EM_P_ColorInit.hpp"
#include "PX2EM_P_AlphaInit.hpp"
#include "PX2EM_P_AlphaByAge.hpp"
#include "PX2EM_P_RotateDegreeInit.hpp"
#include "PX2EM_P_RotateSpeedInit.hpp"
#include "PX2EM_P_RotateSpeedByAge.hpp"
#include "PX2EM_P_FaceAxisInit.hpp"
#include "PX2EM_E_EmitRate.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Controller, ParticleEmitterController);
PX2_IMPLEMENT_STREAM(ParticleEmitterController);
PX2_IMPLEMENT_FACTORY(ParticleEmitterController);

//----------------------------------------------------------------------------
ParticleEmitterController::ParticleEmitterController ()
	:
mParticleArray(0),
	mMaxNumParticles(1000),
	mCurEmitRate(5.0f),
	mCreatedParticlesQuantity(0),
	mNumNewParticlesExcess(0.0f)
{
	MaxTime = Mathf::MAX_REAL;
	mPlacerType = PT_SPHERE;

	mPlacerInLength = 0.0f;
	mPlacerOutLength = 1.0f;
	mPlacerInWidth = 0.0f;
	mPlacerOutWidth = 1.0f;
	mPlacerInHeight = 0.0f;
	mPlacerOutHeight = 1.0f;

	// default modules
	//EM_P_LifeInitPtr pLife = new0 EM_P_LifeInit();
	//AddModule(pLife);

	//EM_P_SizeInitPtr pSizeInit = new0 EM_P_SizeInit();
	//AddModule(pSizeInit);

	//EM_P_SizeByAgePtr pSizeByAge = new0 EM_P_SizeByAge();
	//AddModule(pSizeByAge);

	//EM_P_SpeedInitPtr pSpeedInit = new0 EM_P_SpeedInit();
	//AddModule(pSpeedInit);

	//EM_P_SpeedDirInitPtr pSpeedDirInit = new0 EM_P_SpeedDirInit();
	//AddModule(pSpeedDirInit);

	//EM_P_AcceleratePtr pAccelerate = new0 EM_P_Accelerate();
	//AddModule(pAccelerate);

	//EM_P_AccelerateDirPtr pAccelerateDir = new0 EM_P_AccelerateDir();
	//AddModule(pAccelerateDir);

	//EM_P_ColorInitPtr pColorInit = new0 EM_P_ColorInit();
	//AddModule(pColorInit);

	//EM_P_AlphaInitPtr pAlphaInit = new0 EM_P_AlphaInit();
	//AddModule(pAlphaInit);

	//EM_P_AlphaByAgePtr pAlphaByAge = new0 EM_P_AlphaByAge();
	//AddModule(pAlphaByAge);

	//EM_P_FaceAxisInitPtr pFaceAxisInit = new0 EM_P_FaceAxisInit();
	//AddModule(pFaceAxisInit);

	//EM_P_RotateDegreeInitPtr pRotateDegreeInit = new0 EM_P_RotateDegreeInit();
	//AddModule(pRotateDegreeInit);

	//EM_P_RotateSpeedInitPtr pRotateSpeedInit = new0 EM_P_RotateSpeedInit();
	//AddModule(pRotateSpeedInit);
	//
	//EM_P_RotateSpeedByAgePtr pRotateSpeedByAge = new0 EM_P_RotateSpeedByAge();
	//AddModule(pRotateSpeedByAge);

	EM_E_EmitRatePtr eEmitRate = new0 EM_E_EmitRate();
	AddModule(eEmitRate);
}
//----------------------------------------------------------------------------
ParticleEmitterController::~ParticleEmitterController ()
{
	if (mParticleArray)
	{
		delete0(mParticleArray);
		mParticleArray = 0;
	}
}
//----------------------------------------------------------------------------
void ParticleEmitterController::SetPlacerType (PlacerType type)
{
	mPlacerType = type;
}
//----------------------------------------------------------------------------
void ParticleEmitterController::SetPlacerInLength (float val)
{
	mPlacerInLength = val;
}
//----------------------------------------------------------------------------
void ParticleEmitterController::SetPlacerOutLength (float val)
{
	mPlacerOutLength = val;
}
//----------------------------------------------------------------------------
void ParticleEmitterController::SetPlacerInWidth (float val)
{
	mPlacerInWidth = val;
}
//----------------------------------------------------------------------------
void ParticleEmitterController::SetPlacerOutWidth (float val)
{
	mPlacerOutWidth = val;
}
//----------------------------------------------------------------------------
void ParticleEmitterController::SetPlacerInHeight (float val)
{
	mPlacerInHeight = val;
}
//----------------------------------------------------------------------------
void ParticleEmitterController::SetPlacerOutHeight (float val)
{
	mPlacerOutHeight = val;
}
//----------------------------------------------------------------------------
void ParticleEmitterController::SetMaxNumParticles (int num)
{
	if (num > 10000)
		num = 10000;

	mMaxNumParticles = num;
	if (mParticleArray)
	{
		delete0(mParticleArray);
		mParticleArray = 0;
	}
	mParticleArray = new0 TRecyclingArray<Particle>(mMaxNumParticles);

	ParticleEmitter *emitter = DynamicCast<ParticleEmitter>(mObject);
	if (!emitter)
		return;

	VertexBufferPtr newVBuffer = new0 VertexBuffer(mMaxNumParticles*4, 
		emitter->GetVertexFormat()->GetStride(), Buffer::BU_DYNAMIC);
	VertexBufferAccessor vba(emitter->GetVertexFormat(), newVBuffer);
	assertion(vba.HasTCoord(0),
		"Texture coordinates must exist and use channel 0\n");
	int i, j;
	for (i = 0, j = 0; i < mMaxNumParticles; ++i)
	{
		vba.Position<Float3>(j)	   = Float3(0.0f, 0.0f, 0.0f);
		vba.TCoord<Float2>(0, j++) = Float2(0.0f, 0.0f);
		vba.Position<Float3>(j)	   = Float3(1.0f, 0.0f, 0.0f);
		vba.TCoord<Float2>(0, j++) = Float2(1.0f, 0.0f);
		vba.Position<Float3>(j)	   = Float3(1.0f, 0.0f, 1.0f);
		vba.TCoord<Float2>(0, j++) = Float2(1.0f, 1.0f);
		vba.Position<Float3>(j)	   = Float3(0.0f, 0.0f, 1.0f);
		vba.TCoord<Float2>(0, j++) = Float2(0.0f, 1.0f);
	}
	emitter->SetVertexBuffer(newVBuffer);
	newVBuffer->SetNumElements(0);

	IndexBufferPtr newIBuffer = new0 IndexBuffer(mMaxNumParticles*6, 2, 
		Buffer::BU_DYNAMIC);
	unsigned short iFI, iFIp1, iFIp2, iFIp3;
	unsigned short* indices = (unsigned short*)newIBuffer->GetData();
	for (i = 0; i < mMaxNumParticles; ++i)
	{
		iFI = 4*i;
		iFIp1 = iFI+1;
		iFIp2 = iFI+2;
		iFIp3 = iFI+3;
		*indices++ = iFI;
		*indices++ = iFIp1;
		*indices++ = iFIp2;
		*indices++ = iFI;
		*indices++ = iFIp2;
		*indices++ = iFIp3;
	}
	emitter->SetIndexBuffer(newIBuffer);
	newIBuffer->SetNumElements(0);

	Reset();
}
//----------------------------------------------------------------------------
void ParticleEmitterController::AddModule (EffectModule *event)
{
	assertion(event!=0, "event must not be 0.");

	mModules.push_back(event);
}
//----------------------------------------------------------------------------
void ParticleEmitterController::RemoveModule (EffectModule *event)
{
	ModuleList::iterator it = mModules.begin();
	for (; it!=mModules.end(); it++)
	{
		if (*it == event)
		{
			(*it)->OnRemove(*this);

			mModules.erase(it);

			return;
		}
	}
}
//----------------------------------------------------------------------------
bool ParticleEmitterController::IsHasModule (std::string moduleRttiName)
{
	ModuleList::iterator it = mModules.begin();
	for (; it!=mModules.end(); it++)
	{
		std::string rttiName = (*it)->GetRttiType().GetName();
		if (rttiName == moduleRttiName)
		{
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
EffectModule *ParticleEmitterController::GetModule (int i)
{
	if (0<=i && i<(int)mModules.size())
		return mModules[i];

	return 0;
}
//----------------------------------------------------------------------------
int ParticleEmitterController::GetNumModules ()
{
	return (int)mModules.size();
}
//----------------------------------------------------------------------------
void ParticleEmitterController::Reset ()
{
	mIsTimeInited = false;
	mInitedApplicationIime = 0.0f;
	mLastApplicationTime = 0.0f;
	mApplicationTime = 0.0f;
	mCreatedParticlesQuantity = 0;
	mNumNewParticlesExcess = 0.0f;

	if (mParticleArray)
	{
		mParticleArray->DeleteAll();
	}

	ParticleEmitter *emitter = DynamicCast<ParticleEmitter>(mObject);
	if (!emitter)
		return;

	VertexBuffer *vBuffer = emitter->GetVertexBuffer();
	IndexBuffer *iBuffer = emitter->GetIndexBuffer();
	if (vBuffer)
	{
		vBuffer->SetNumElements(0);
	}
	if (iBuffer)
	{
		iBuffer->SetNumElements(0);
	}
}
//----------------------------------------------------------------------------
bool ParticleEmitterController::Update (double applicationTime)
{
	if (applicationTime == 0.0f)
		return true;

	if (!Controller::Update(applicationTime))
	{
		return false;
	}

	double runTime = GetRunTime();
	double ctrlTime = GetControlTime(applicationTime);
	double elapsedTime = GetElapsedTime();

	if (!mParticleArray)
		return false;

	ParticleEmitter *emitter = DynamicCast<ParticleEmitter>(mObject);
	if (!emitter)
		return false;

	EffectPlayType playType = emitter->GetEffectPlayType();
	float effectLife = emitter->GetEffectPlayLife();
	if (EPT_ONCE == playType)
	{
		if (runTime > effectLife)
		{
			emitter->Stop();
			return true;
		}
	}

	// update emitter events
	UpdateEmitterEvents(ctrlTime);

	// update particle events
	for (int i=0; i<mParticleArray->GetQuantity(); i++)
	{
		// 粒子活着
		if (mParticleArray->IsUsed(i))
		{
			Particle &particle = mParticleArray->GetAt(i);

			if (!particle.Update(emitter, (float)elapsedTime))
			{
				mParticleArray->Delete(&particle);
			}
			else
			{
				UpdateParticleEvents(particle, ctrlTime);
			}
		}
	} // for (int i=0;

	// new particles
	float emitNum = mCurEmitRate * (float)elapsedTime;
	int iNewNum= (int)emitNum;
	mNumNewParticlesExcess += (emitNum - iNewNum);

	if (mNumNewParticlesExcess > 1.0f)
	{
		iNewNum += (int)mNumNewParticlesExcess;
		mNumNewParticlesExcess -= (int)mNumNewParticlesExcess;
	}

	// 创建新的粒子
	for (int i=0; i<iNewNum && mParticleArray->GetFreeQuantity()>0; i++)
	{
		NewAParticle(ctrlTime);
	}

	// 生成粒子
	emitter->GenerateParticles();

	return true;
}
//----------------------------------------------------------------------------
void ParticleEmitterController::NewAParticle(double ctrlTime)
{
	Particle *particle = 0;
	particle = mParticleArray->New();

	if (!particle)
		return;

	ParticleEmitter *emitter = (ParticleEmitter*)mObject;
	if (!emitter)
		return;

	float halfOutLength = mPlacerOutLength/2.0f;
	float halfInLength = mPlacerInLength/2.0f;
	float halfOutWidth = mPlacerOutWidth/2.0f;
	float halfInWidth = mPlacerInWidth/2.0f;
	float halfOutHeight = mPlacerOutHeight/2.0f;
	float halfInHeight = mPlacerInHeight/2.0f;

	float signLength = Mathf::Sign(Mathf::SymmetricRandom());
	float signWidth = Mathf::Sign(Mathf::SymmetricRandom());
	float signHeight = Mathf::Sign(Mathf::SymmetricRandom());
	if (0 == signLength)
		signLength = 1.0f;
	if (0 == signWidth)
		signWidth = 1.0f;
	if (0 == signHeight)
		signHeight = 1.0f;

	APoint pos = APoint::ORIGIN;
	if (PT_BOX == mPlacerType)
	{
		float halfLength = Mathf::IntervalRandom(halfInLength, halfOutLength)*signLength;
		float halfWidth = Mathf::IntervalRandom(halfInWidth, halfOutWidth)*signWidth;
		float halfHeight = Mathf::IntervalRandom(halfInHeight, halfOutHeight)*signHeight;

		pos = APoint(halfLength, halfWidth, halfHeight);
	}
	else if (PT_SPHERE == mPlacerType)
	{
		AVector dir = AVector(Mathf::SymmetricRandom(), 
			Mathf::SymmetricRandom(),
			Mathf::SymmetricRandom());
		float length = dir.Normalize();
		if (0.0f == length)
		{
			dir = AVector::UNIT_X;
		}

		float halfLength = Mathf::IntervalRandom(halfInLength, halfOutLength)*signLength;
		pos = APoint::ORIGIN + dir * halfLength;
	}
	else if (PT_COLUMN == mPlacerType)
	{
		AVector dir = AVector(Mathf::SymmetricRandom(), 
			Mathf::SymmetricRandom(), 0.0f);
		float length = dir.Normalize();
		if (0.0f == length)
		{
			dir = AVector::UNIT_X;
		}
		
		float halfLength = Mathf::IntervalRandom(halfInLength, halfOutLength)*signLength;
		float halfHeight = Mathf::IntervalRandom(halfInHeight, halfOutHeight)*signHeight;
		pos = APoint::ORIGIN + dir*halfLength + AVector::UNIT_Z*halfHeight;
	}

	if (!emitter->IsLocal())
	{
		pos += emitter->WorldTransform.GetTranslate();
	}

	particle->Pos = pos;

	for (int i=0; i<(int)mModules.size(); i++)
	{
		if (mModules[i])
		{
			mModules[i]->UpdateParticle(*particle, ctrlTime);
		}
	}

	particle->Update(emitter, 0.0f);

	mCreatedParticlesQuantity++;
}
//----------------------------------------------------------------------------
void ParticleEmitterController::UpdateEmitterEvents (double ctrlTime)
{
	for (int i=0; i<(int)mModules.size(); i++)
	{
		if (mModules[i])
		{
			mModules[i]->UpdateParticleEmitter(*this, ctrlTime);
		}
	}
}
//----------------------------------------------------------------------------
void ParticleEmitterController::UpdateParticleEvents (Particle &particle,
	double ctrlTime)
{
	for (int i=0; i<(int)mModules.size(); i++)
	{
		if (mModules[i])
		{
			mModules[i]->UpdateParticle(particle, ctrlTime);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* ParticleEmitterController::GetObjectByName (const std::string& name)
{
	Object* found = Controller::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	for (int i = 0; i <(int)mModules.size(); i++)
	{
		EffectModule* event = mModules[i];
		if (event)
		{
			PX2_GET_OBJECT_BY_NAME(event, name, found);
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
void ParticleEmitterController::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	Controller::GetAllObjectsByName(name, objects);

	for (int i=0; i<(int)mModules.size(); i++)
	{
		EffectModule *event = mModules[i];
		if (event)
		{
			PX2_GET_ALL_OBJECTS_BY_NAME(event, name, objects);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
ParticleEmitterController::ParticleEmitterController (LoadConstructor value)
	:
Controller(value),
	mParticleArray(0),
	mMaxNumParticles(100),
	mCurEmitRate(5.0f),
	mCreatedParticlesQuantity(0),
	mNumNewParticlesExcess(0.0f)
{
}
//----------------------------------------------------------------------------
void ParticleEmitterController::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Controller::Load(source);

	source.Read(mMaxNumParticles);

	source.ReadEnum(mPlacerType);
	source.Read(mPlacerInLength);
	source.Read(mPlacerOutLength);
	source.Read(mPlacerInWidth);
	source.Read(mPlacerOutWidth);
	source.Read(mPlacerInHeight);
	source.Read(mPlacerOutHeight);

	int numModules = 0;
	source.Read(numModules);
	if (numModules > 0)
	{
		mModules.resize(numModules);
		source.ReadPointerVV(numModules, &mModules[0]);
	}

	PX2_END_DEBUG_STREAM_LOAD(ParticleEmitterController, source);
}
//----------------------------------------------------------------------------
void ParticleEmitterController::Link (InStream& source)
{
	Controller::Link(source);

	const int numModules = (int)mModules.size();
	for (int i=0; i<numModules; ++i)
	{
		if (mModules[i])
		{
			source.ResolveLink(mModules[i]);
		}
	}
}
//----------------------------------------------------------------------------
void ParticleEmitterController::PostLink ()
{
	Controller::PostLink();

	mParticleArray = new0 TRecyclingArray<Particle>(mMaxNumParticles);
}
//----------------------------------------------------------------------------
bool ParticleEmitterController::Register (OutStream& target) const
{
	if (Controller::Register(target))
	{
		const int numModules = (int)mModules.size();
		for (int i=0; i<numModules; ++i)
		{
			if (mModules[i])
			{
				target.Register(mModules[i]);
			}
		}

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void ParticleEmitterController::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Controller::Save(target);

	target.Write(mMaxNumParticles);

	target.WriteEnum(mPlacerType);
	target.Write(mPlacerInLength);
	target.Write(mPlacerOutLength);
	target.Write(mPlacerInWidth);
	target.Write(mPlacerOutWidth);
	target.Write(mPlacerInHeight);
	target.Write(mPlacerOutHeight);

	const int numModules = (int)mModules.size();
	target.Write(numModules);
	for (int i=0; i<numModules; ++i)
	{
		if (mModules[i])
		{
			target.WritePointer(mModules[i]);
		}
		else
		{
			target.WritePointer((Movable*)0);
		}
	}

	PX2_END_DEBUG_STREAM_SAVE(ParticleEmitterController, target);
}
//----------------------------------------------------------------------------
int ParticleEmitterController::GetStreamingSize () const
{
	int numModules = (int)mModules.size();

	int size = Controller::GetStreamingSize()
		+ sizeof(mMaxNumParticles)
		+ PX2_ENUMSIZE(mPlacerType)
		+ 6*sizeof(float)
		+ sizeof(numModules) // numModules
		+ PX2_POINTERSIZE(mModules[i])*numModules; 

	return size;
}
//----------------------------------------------------------------------------
