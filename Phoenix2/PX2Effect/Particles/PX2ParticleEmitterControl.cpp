/*
*
* 文件名称	：	PX2ParticleEmitterControl.cpp
*
*/

#include "PX2ParticleEmitterControl.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2Movable.hpp"
#include "PX2ParticleEmitter.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Controller, ParticleEmitterController);
PX2_IMPLEMENT_STREAM(ParticleEmitterController);
PX2_IMPLEMENT_FACTORY(ParticleEmitterController);

//----------------------------------------------------------------------------
ParticleEmitterController::ParticleEmitterController ()
:
mParticleArray(0),
mMaxQuantity(100),
mEmitRate(5.0f),
mEmitRateStep(0.0f),
mCreatedParticlesQuantity(0),
mNumNewParticlesExcess(0.0f),
mLastApplicationTime(0.0f),
mbFirstFrame(true)
{
}
//----------------------------------------------------------------------------
ParticleEmitterController::~ParticleEmitterController ()
{
	EventIt it = mEvents.begin();
	for (it; it!=mEvents.end(); it++)
	{
		if (*it)
			*it = 0;
	}
	mEvents.clear();

	if (mParticleArray)
	{
		delete0(mParticleArray);
		mParticleArray = 0;
	}
}
//----------------------------------------------------------------------------
void ParticleEmitterController::SetMaxQuantity (int quantity)
{
	mMaxQuantity = quantity;
	mParticleArray = new0 TRecyclingArray<Particle>(mMaxQuantity);

	ParticleEmitter *emitter = DynamicCast<ParticleEmitter>(mObject);
	if (!emitter)
		return;

	//if (emitter->GetVertexBuffer())
	//{
	//	if (mMaxQuantity*4 == emitter->GetVertexBuffer()->GetNumElements())
	//		return;
	//}

	VertexBufferPtr newVBuffer = new0 VertexBuffer(mMaxQuantity*4, 
		emitter->GetVertexFormat()->GetStride(), Buffer::BU_DYNAMIC);
	VertexBufferAccessor vba(emitter->GetVertexFormat(), newVBuffer);
	assertion(vba.HasTCoord(0),
		"Texture coordinates must exist and use channel 0\n");
	int i, j;
	for (i = 0, j = 0; i < mMaxQuantity; ++i)
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

	IndexBufferPtr newIBuffer = new0 IndexBuffer(mMaxQuantity*6, 4, 
		Buffer::BU_DYNAMIC);
	int iFI, iFIp1, iFIp2, iFIp3;
	int* indices = (int*)newIBuffer->GetData();
	for (i = 0; i < mMaxQuantity; ++i)
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
}
//----------------------------------------------------------------------------
int ParticleEmitterController::AttachEffectEvent (EffectEvent *event)
{
	assertion(event!=0, "event must not be 0.");

	int quantity = (int)mEvents.size();
	for (int i=0; i<quantity; i++)
	{
		if (mEvents[i] == 0)
		{
			mEvents[i] = event;
			return i;
		}
	}

	mEvents.push_back(event);

	return quantity;
}
//----------------------------------------------------------------------------
int ParticleEmitterController::DetachEffectEvent (EffectEvent *event)
{
	if (event)
	{
		for (int i=0; i<(int)mEvents.size(); i++)
		{
			if (mEvents[i] == event)
			{
				mEvents[i] = 0;
				return i;
			}
		}
	}

	return -1;
}
//----------------------------------------------------------------------------
EffectEvent *ParticleEmitterController::DetachEffectEventAt (int i)
{
	if (0<=i && i<(int)mEvents.size())
	{
		EffectEventPtr event = mEvents[i];
		if (event)
		{
			mEvents[i] = 0;
		}
		return event;
	}

	return 0;
}
//----------------------------------------------------------------------------
EffectEvent *ParticleEmitterController::SetEffectEvent (int i,
														EffectEvent *event)
{
	if (0 <= i && i < (int)mEvents.size())
	{
		EffectEventPtr preEvent = mEvents[i];

		mEvents[i] = event;

		return preEvent;
	}

	// 游标超出范围，增加数组的大小，加入新的节点
	mEvents.push_back(event);

	return 0;
}
//----------------------------------------------------------------------------
EffectEvent *ParticleEmitterController::GetEffectEvent (int i)
{
	if (0<=i && i<(int)mEvents.size())
		return mEvents[i];

	return 0;
}
//----------------------------------------------------------------------------
int ParticleEmitterController::GetNumEvents ()
{
	return (int)mEvents.size();
}
//----------------------------------------------------------------------------
void ParticleEmitterController::Reset ()
{
	mbFirstFrame = true;
	mCreatedParticlesQuantity = 0;
	mNumNewParticlesExcess = 0.0f;
	mLastApplicationTime = 0.0f;

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
void ParticleEmitterController::ConfigeAllEvents ()
{
	NailDowmRandTime();
	SortEvents();
	CreateEventList();

	Reset();
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

	if (mbFirstFrame)
	{
		mLastApplicationTime = applicationTime;
		mbFirstFrame = false;

		return true;
	}

	float elapsedTime = (float)(mApplicationTime - mLastApplicationTime);
	mLastApplicationTime = mApplicationTime;

	if (!mParticleArray)
		return false;

	ParticleEmitter *emitter = DynamicCast<ParticleEmitter>(mObject);
	if (!emitter)
		return false;

	// update emitter events
	UpdateEmitterEvents();

	// update particle events
	for (int i=0; i<mParticleArray->GetQuantity(); i++)
	{
		// 粒子活着
		if (mParticleArray->IsUsed(i))
		{
			Particle &particle = mParticleArray->GetAt(i);

			if (!particle.Update(elapsedTime))
			{
				mParticleArray->Delete(&particle);
			}
			else
			{
				UpdateParticleEvents(particle);
			}
		}
	} // for (int i=0;

	// new particles
	mEmitRate += mEmitRateStep * elapsedTime;

	float emitNum = mEmitRate * elapsedTime;
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
		NewAParticle();
	}

	// 生成粒子
	emitter->GenerateParticles(GraphicsRoot::GetSingleton().GetCamera());

	return true;
}
//----------------------------------------------------------------------------
void ParticleEmitterController::SortEvents ()
{
	EffectEvent_CompareFun CF;
	sort(mEvents.begin(), mEvents.end(), CF);
}
//----------------------------------------------------------------------------
void ParticleEmitterController::CreateEventList ()
{
	EventIt it = mEvents.begin();
	for (; it!=mEvents.end(); it++)
	{
		(*it)->NextEvent = 0;
	}

	EventIt it0 = mEvents.begin();
	EventIt it1;
	for (it0; it0!=mEvents.end(); it0++)
	{
		for (it1=it0; it1!=mEvents.end(); it1++)
		{
			if (it1!=it0
				&& (*it0)->GetRttiType().IsExactly((*it1)->GetRttiType())
				&& (*it1)->IsFadeTo())
			{
				(*it0)->NextEvent = (*it1);
				break;
			}
		}
	}
}
//----------------------------------------------------------------------------
void ParticleEmitterController::NailDowmRandTime ()
{
	EventIt it = mEvents.begin();
	for (it; it!=mEvents.end(); it++)
	{
		(*it)->SetActivateTime((*it)->GetTimeRange().GetRandomInRange());
	}
}
//----------------------------------------------------------------------------
void ParticleEmitterController::NewAParticle()
{
	Particle *particle = 0;
	particle = mParticleArray->New();

	if (!particle)
		return;

	particle->CurEvent = mEvents.begin();

	// 使用初始化事件,初始化
	EventIt it = mEvents.begin();
	for (; it!=mEvents.end() && ((*it)->GetActivateTime() == 0.0f); it++)
	{
		(*it)->UpdateParticle(*particle);
	}

	particle->CurEvent = it;

	mCreatedParticlesQuantity++;
}
//----------------------------------------------------------------------------
void ParticleEmitterController::UpdateEmitterEvents ()
{
	EventIt it = mEvents.begin();
	for ( ; it!=mEvents.end(); it++)
	{
		(*it)->UpdateParticleEmitter(*this);
	}
}
//----------------------------------------------------------------------------
void ParticleEmitterController::UpdateParticleEvents (Particle &particle)
{
	// 运行已经到激活时间的事件
	EventIt it = mEvents.begin();
	for (it=particle.CurEvent; 
		it!=mEvents.end()&&(*it)->GetActivateTime()<=particle.EventTime;
		it++)
	{
		float oldEventTime = particle.EventTime;

		(*it)->UpdateParticle(particle);

		// 时间改变了粒子的EventTime，需要重新计算粒子的当前事件
		// 通常这种事件是一个“时间事件”，将粒子的事件时间向前调
		if (particle.EventTime != oldEventTime)
		{
			EventIt itRecalc = mEvents.begin();
			for (itRecalc; 
				itRecalc!=mEvents.end()&&((*itRecalc)->GetActivateTime()<particle.EventTime);
				itRecalc++);

			if (itRecalc == mEvents.begin())
			{
				it = mEvents.begin();
				break;
			}
			else
			{
				it = itRecalc - 1;
			}
		}
	}

	particle.CurEvent = it;
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

	for (int i = 0; i <(int)mEvents.size(); i++)
	{
		EffectEvent* event = mEvents[i];
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

	for (int i=0; i<(int)mEvents.size(); i++)
	{
		EffectEvent *event = mEvents[i];
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
mMaxQuantity(100),
mEmitRate(5.0f),
mEmitRateStep(0.0f),
mCreatedParticlesQuantity(0),
mNumNewParticlesExcess(0.0f),
mLastApplicationTime(0.0f),
mbFirstFrame(true)
{
}
//----------------------------------------------------------------------------
void ParticleEmitterController::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Controller::Load(source);

	source.Read(mMaxQuantity);

	int numEvents = 0;
	source.Read(numEvents);
	if (numEvents > 0)
	{
		mEvents.resize(numEvents);
		source.ReadPointerVV(numEvents, &mEvents[0]);
	}

	PX2_END_DEBUG_STREAM_LOAD(ParticleEmitterController, source);
}
//----------------------------------------------------------------------------
void ParticleEmitterController::Link (InStream& source)
{
	Controller::Link(source);

	const int numEvents = (int)mEvents.size();
	for (int i=0; i<numEvents; ++i)
	{
		if (mEvents[i])
		{
			source.ResolveLink(mEvents[i]);
		}
	}
}
//----------------------------------------------------------------------------
void ParticleEmitterController::PostLink ()
{
	Controller::PostLink();

	mParticleArray = new0 TRecyclingArray<Particle>(mMaxQuantity);

	ConfigeAllEvents();
}
//----------------------------------------------------------------------------
bool ParticleEmitterController::Register (OutStream& target) const
{
	if (Controller::Register(target))
	{
		const int numEvents = (int)mEvents.size();
		for (int i=0; i<numEvents; ++i)
		{
			if (mEvents[i])
			{
				target.Register(mEvents[i]);
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

	target.Write(mMaxQuantity);

	const int numEvents = (int)mEvents.size();
	target.Write(numEvents);
	for (int i=0; i<numEvents; ++i)
	{
		if (mEvents[i])
		{
			target.WritePointer(mEvents[i]);
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
	int numEvents = (int)mEvents.size();

	int size = Controller::GetStreamingSize()
		+ sizeof(mMaxQuantity)
		+ sizeof(numEvents) // numEvents
		+ PX2_POINTERSIZE(mEvents[i])*numEvents; 

	return size;
}
//----------------------------------------------------------------------------
