/*
*
* 文件名称	：	PX2Soundable.cpp
*
*/

#include "PX2Soundable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Movable, Soundable);
PX2_IMPLEMENT_STREAM(Soundable);
PX2_IMPLEMENT_FACTORY(Soundable);

//----------------------------------------------------------------------------
Soundable::Soundable ()
{
	mIs2d = false;
}
//----------------------------------------------------------------------------
Soundable::Soundable (const char *fileName,
					  const SoundCreateInfo3D &createInfo)
{	
	mCreateInfo = createInfo;
	mFilename = std::string(fileName);
	mIs2d = false;
	mSound = 0;
}
//----------------------------------------------------------------------------
Soundable::~Soundable ()
{
	mSound = 0;
}
//----------------------------------------------------------------------------
void Soundable::Play ()
{
	mSound = 0;
	mCreateInfo.position = WorldTransform.GetTranslate();

	if (!mIs2d)
	{
		mCreateInfo.position = WorldTransform.GetTranslate();
		mSound = SoundSystem::GetSingletonPtr()->PlaySound3DControl(
			mFilename.c_str(), mCreateInfo);
	}
	else
	{
		mSound = SoundSystem::GetSingletonPtr()->PlaySound2DControl(
			mFilename.c_str(), 1.0f, mCreateInfo.isloop);
	}
}
//----------------------------------------------------------------------------
bool Soundable::IsPlaying ()
{
	if (!mSound)
		return false;

	return mSound->IsPlaying();
}
//----------------------------------------------------------------------------
void Soundable::SetVolume (float volume)
{
	mCreateInfo.volume = volume;

	if (mSound)
		mSound->SetVolume(volume);
}
//----------------------------------------------------------------------------
float Soundable::GetVolume ()
{
	return mCreateInfo.volume;
}
//----------------------------------------------------------------------------
void Soundable::Pause (bool pause)
{
	if (mSound)
		mSound->SetPaused(pause);
}
//----------------------------------------------------------------------------
void Soundable::Stop ()
{
	mSound = 0;
}
//----------------------------------------------------------------------------
void Soundable::SetVelocity (const AVector &velocity)
{
	mCreateInfo.velocity = velocity;

	if (mSound)
		mSound->SetVelocity(velocity);
}
//----------------------------------------------------------------------------
AVector Soundable::GetVelocity ()
{
	return mCreateInfo.velocity;
}
//----------------------------------------------------------------------------
void Soundable::SetDistance (float minDistance, float maxDistance)
{
	mCreateInfo.mindistance = minDistance;
	mCreateInfo.maxdistance = maxDistance;

	if (mSound)
		mSound->SetDistance(minDistance, maxDistance);
}
//----------------------------------------------------------------------------
void Soundable::SetMinDistance (float minDistance)
{
	mCreateInfo.mindistance = minDistance;

	if (minDistance > mCreateInfo.maxdistance)
		mCreateInfo.maxdistance = minDistance;

	if (mSound)
		mSound->SetDistance(mCreateInfo.mindistance, mCreateInfo.maxdistance);
}
//----------------------------------------------------------------------------
void Soundable::SetMaxDistance (float maxDistance)
{
	if (maxDistance < mCreateInfo.mindistance)
		mCreateInfo.mindistance = maxDistance;

	mCreateInfo.maxdistance = maxDistance;

	if (mSound)
		mSound->SetDistance(mCreateInfo.mindistance, mCreateInfo.maxdistance);
}
//----------------------------------------------------------------------------
float Soundable::GetMinDistance ()
{
	return mCreateInfo.mindistance;
}
//----------------------------------------------------------------------------
float Soundable::GetMaxDistance ()
{
	return mCreateInfo.maxdistance;
}
//----------------------------------------------------------------------------
void Soundable::SetLoop (bool loop)
{
	mCreateInfo.isloop = loop;
}
//----------------------------------------------------------------------------
bool Soundable::IsLoop ()
{
	return mCreateInfo.isloop;
}
//----------------------------------------------------------------------------
void Soundable::SetSoundFile (std::string filename)
{
	bool isPlaying = IsPlaying();

	mFilename = filename;

	if (isPlaying)
		Play();
}
//----------------------------------------------------------------------------
std::string Soundable::GetSoundFile ()
{
	return mFilename;
}
//----------------------------------------------------------------------------
void Soundable::OnAttach ()
{
}
//----------------------------------------------------------------------------
void Soundable::OnDetach ()
{
}
//----------------------------------------------------------------------------
void Soundable::UpdateWorldData (double applicationTime)
{
	Movable::UpdateWorldData(applicationTime);

	if (mSound)
		mSound->SetPosition(WorldTransform.GetTranslate());
}
//----------------------------------------------------------------------------
void Soundable::UpdateWorldBound ()
{
	/* Nothing to do. */
}
//----------------------------------------------------------------------------
void Soundable::GetVisibleSet (Culler& culler, bool)
{
	/* Nothing to do. */
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* Soundable::GetObjectByName (const std::string& name)
{
	Object* found = Movable::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void Soundable::GetAllObjectsByName (const std::string& name,
								 std::vector<Object*>& objects)
{
	Movable::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Soundable::Soundable (LoadConstructor value)
:
Movable(value)
{
}
//----------------------------------------------------------------------------
void Soundable::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Movable::Load(source);

	source.ReadString(mFilename);
	source.ReadBool(mIs2d);

	// mCreateInfo
	source.Read(mCreateInfo.mindistance);
	source.Read(mCreateInfo.maxdistance);
	source.Read(mCreateInfo.volume);
	source.ReadAggregate(mCreateInfo.position);
	source.ReadAggregate(mCreateInfo.velocity);
	source.ReadBool(mCreateInfo.isloop);

	PX2_END_DEBUG_STREAM_LOAD(Soundable, source);
}
//----------------------------------------------------------------------------
void Soundable::Link (InStream& source)
{
	Movable::Link(source);
}
//----------------------------------------------------------------------------
void Soundable::PostLink ()
{
	Movable::PostLink();
}
//----------------------------------------------------------------------------
bool Soundable::Register (OutStream& target) const
{
	if (Movable::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void Soundable::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Movable::Save(target);
	
	target.WriteString(mFilename);
	target.WriteBool(mIs2d);

	// mCreateInfo
	target.Write(mCreateInfo.mindistance);
	target.Write(mCreateInfo.maxdistance);
	target.Write(mCreateInfo.volume);
	target.WriteAggregate(mCreateInfo.position);
	target.WriteAggregate(mCreateInfo.velocity);
	target.WriteBool(mCreateInfo.isloop);

	PX2_END_DEBUG_STREAM_SAVE(Soundable, target);
}
//----------------------------------------------------------------------------
int Soundable::GetStreamingSize () const
{
	int size = Movable::GetStreamingSize();
	size += PX2_STRINGSIZE(mFilename);
	size += PX2_BOOLSIZE(mIs2d);
	size += sizeof(mCreateInfo.mindistance);
	size += sizeof(mCreateInfo.maxdistance);
	size += sizeof(mCreateInfo.volume);
	size += sizeof(mCreateInfo.position);
	size += sizeof(mCreateInfo.velocity);
	size += PX2_BOOLSIZE(mCreateInfo.isloop);

	return size;
}
//----------------------------------------------------------------------------
