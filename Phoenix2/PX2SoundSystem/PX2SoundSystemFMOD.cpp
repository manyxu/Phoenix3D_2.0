/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SoundSystemFMod.cpp
*
*/

#include "PX2SoundSystemFMOD.hpp"
#include "PX2Time.hpp"
#include "PX2FileIO.hpp"
using namespace PX2;

FMODSound::FMODSound (FMOD::Channel *channel)
{
	mChannel = channel;
}
//----------------------------------------------------------------------------
FMODSound::~FMODSound ()
{
	if (mChannel)
		mChannel->stop();
}
//----------------------------------------------------------------------------
bool FMODSound::IsPlaying ()
{
	bool isPlaying = false;
	mChannel->isPlaying(&isPlaying);

	return isPlaying;
}
//----------------------------------------------------------------------------
void FMODSound::SetVolume (float volume)
{
	mChannel->setVolume(volume);
}
//----------------------------------------------------------------------------
void FMODSound::SetPaused (bool paused)
{
	mChannel->setPaused(paused);
}
//----------------------------------------------------------------------------
void FMODSound::Stop ()
{
	mChannel->stop();
}
//----------------------------------------------------------------------------
void FMODSound::SetPosition (const APoint &position)
{
	FMOD_VECTOR pos;
	pos.x = position.X();
	pos.y = position.Y();
	pos.z = position.Z();

	if (mChannel)
		mChannel->set3DAttributes(&pos, 0);
}
//----------------------------------------------------------------------------
void FMODSound::SetVelocity (const AVector &velocity)
{
	FMOD_VECTOR vec;
	vec.x = velocity.X();
	vec.y = velocity.Y();
	vec.z = velocity.Z();

	if (mChannel)
		mChannel->set3DAttributes(0, &vec);
}
//----------------------------------------------------------------------------
void FMODSound::SetDistance (float mindist, float maxdist)
{
	if (mChannel)
		mChannel->set3DMinMaxDistance(mindist, maxdist);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// SoundSystemFMOD
//----------------------------------------------------------------------------
FMODSoundSystem::FMODSoundSystem()
{
	mType = SoundSystem::SST_FMOD;
	mFMODSystem = 0;
	mChannelGroupMusic = 0;
	mChannelGroupSound = 0;

	for (int i=0; i<4; i++)
	{
		mMusicChannel[i].channelMain = 0;
		mMusicChannel[i].channelFadein = 0;
		mMusicChannel[i].soundMain = 0;
		mMusicChannel[i].soundFadein = 0;
		mMusicChannel[i].fadeinTimeLength = 0;
		mMusicChannel[i].fadeinTimeLeft = 0;
		mMusicChannel[i].volume = 1.0f;
		mMusicChannel[i].fadeinVolume = 1.0f;
		mMusicChannel[i].mainVolume = 1.0f;
	}

	mTimeLastUpdate = 0;
}
//----------------------------------------------------------------------------
FMODSoundSystem::~FMODSoundSystem ()
{
	Terminate();
}
//----------------------------------------------------------------------------
bool FMODSoundSystem::Initialize (const SoundSystemInitInfo &initInfo)
{
	unsigned int version;
	FMOD_SPEAKERMODE speakermode = FMOD_SPEAKERMODE_STEREO;
	FMOD_CAPS caps;

	if (FMOD::System_Create(&mFMODSystem) != FMOD_OK)
	{
		assertion(false, "FMOD::System_Create failed.");
		
		return false;
	}

	if (mFMODSystem->getVersion(&version) != FMOD_OK)
	{
		assertion(false, "FMOD::getVersion failed.");

		return false;
	}

	if (version < FMOD_VERSION)
		return false;

	if (mFMODSystem->getDriverCaps(0, &caps, 0, 0, &speakermode) != FMOD_OK)
	{
		assertion (false, "FMOD::getDriverCaps failed.");

		return false;
	}

	if (mFMODSystem->setSpeakerMode(speakermode) != FMOD_OK)
	{
		assertion (false, "FMOD::setSpeakerMode failed.");

		return false;
	}

	if (caps&FMOD_CAPS_HARDWARE_EMULATED)
	{
		if (mFMODSystem->setDSPBufferSize(1024, 10) != FMOD_OK)
		{
			assertion (false, "FMOD::setDSPBufferSize failed.");

			return false;
		}
	}

	if (mFMODSystem->init(initInfo.maxchannels, FMOD_INIT_NORMAL, 0) != FMOD_OK)
	{
		assertion (false, "FMOD::init failed.");

		return false;
	}

	mFMODSystem->set3DSettings(initInfo.dopplerscale, initInfo.distancefactor,
		initInfo.rolloffscale);
	mFMODSystem->createChannelGroup(0, &mChannelGroupMusic);
	mFMODSystem->createChannelGroup(0, &mChannelGroupSound);

	return true;
}
//----------------------------------------------------------------------------
bool FMODSoundSystem::Terminate ()
{
	for (int i=0; i<4; i++)
	{
		if (mMusicChannel[i].channelMain)
		{
			mMusicChannel[i].channelMain->stop();
			mMusicChannel[i].channelMain = 0;
			mMusicChannel[i].soundMain->release();
			mMusicChannel[i].soundMain = 0;
		}

		if (mMusicChannel[i].channelFadein)
		{
			mMusicChannel[i].channelFadein->stop();
			mMusicChannel[i].channelFadein = 0;
			mMusicChannel[i].soundFadein->release();
			mMusicChannel[i].soundFadein = 0;
		}
	}

	SoundResourceMap::iterator it = mSoundResourceMap.begin();
	for (; it!=mSoundResourceMap.end(); it++)
	{
		it->second->FMODSound->release();
		delete it->second;
	}
	mSoundResourceMap.clear();

	if (mFMODSystem)
		mFMODSystem->release();

	return true;
}
//----------------------------------------------------------------------------
void FMODSoundSystem::Update ()
{
	unsigned int timeCur = (unsigned int)GetTimeInMicroseconds();
	unsigned int timePass = timeCur - mTimeLastUpdate;

	for (int i=0; i<4; i++)
	{
		if (mMusicChannel[i].fadeinTimeLeft > 0)
		{
			if (mMusicChannel[i].fadeinTimeLeft > timePass)
				mMusicChannel[i].fadeinTimeLeft -= timePass;
			else
				mMusicChannel[i].fadeinTimeLeft = 0;

			float blend = (float)mMusicChannel[i].fadeinTimeLeft/
				(float)mMusicChannel[i].fadeinTimeLength;

			if (mMusicChannel[i].channelMain)
				mMusicChannel[i].channelMain->setVolume(
				mMusicChannel[i].mainVolume*blend);
			if (mMusicChannel[i].channelFadein)
				mMusicChannel[i].channelFadein->setVolume(
				mMusicChannel[i].fadeinVolume*(1.0f-blend));
		}

		if (mMusicChannel[i].fadeinTimeLength!=0 && 
			mMusicChannel[i].fadeinTimeLeft==0)
		{
			if (mMusicChannel[i].channelMain)
			{
				mMusicChannel[i].channelMain->stop();
				mMusicChannel[i].soundMain->release();
			}

			mMusicChannel[i].channelMain = mMusicChannel[i].channelFadein;
			mMusicChannel[i].soundMain = mMusicChannel[i].soundFadein;
			mMusicChannel[i].mainVolume = mMusicChannel[i].fadeinVolume;
			mMusicChannel[i].channelFadein = 0;
			mMusicChannel[i].soundFadein = 0;
			mMusicChannel[i].fadeinTimeLeft = 0;
		}
	}

	mFMODSystem->update();

	mTimeLastUpdate = timeCur;
}
//----------------------------------------------------------------------------
void FMODSoundSystem::PlayMusic (unsigned int channel, const char *filename,
								 bool loop, unsigned int fadeTime,
								 float volume)
{
	FMOD::Sound *sound = 0;
	MusicChannelInfo &info = mMusicChannel[channel];

	if (filename)
	{
		if (info.soundMain && std::string(filename)==info.mainPath)
		{
			ClearMusicChannel(channel, false, true);
			info.fadeinTimeLeft = info.fadeinTimeLength = 0;
			info.mainVolume = volume;
			info.channelMain->setVolume(volume);
			return;
		}
		else if (info.soundFadein && std::string(filename)==info.fadeinPath)
		{
			info.fadeinVolume = volume;
			return;
		}
		else if (mFMODSystem->createStream(filename, FMOD_2D|FMOD_LOOP_NORMAL,
			0, &sound) != FMOD_OK)
		{
			sound = 0;
		}
	}

	PlayMusicInternal(channel, sound, loop, fadeTime, volume);
}
//----------------------------------------------------------------------------
void FMODSoundSystem::PlayMusicInternal(unsigned int channel, 
										FMOD::Sound *sound, bool loop,
										unsigned int fadeTime,
										float volume, const char *path)
{
	assertion(channel<4, "channel should be less than 4.");

	mMusicChannel[channel].fadeinTimeLength = fadeTime;
	mMusicChannel[channel].fadeinTimeLeft = fadeTime;

	if (fadeTime == 0)
	{
		ClearMusicChannel(channel, true, true);

		if (sound)
		{
			mFMODSystem->playSound(FMOD_CHANNEL_FREE, sound, true, 
				&mMusicChannel[channel].channelMain);
			mMusicChannel[channel].soundMain = sound;
			mMusicChannel[channel].mainVolume = volume;
			mMusicChannel[channel].channelMain->setChannelGroup(mChannelGroupMusic);
			mMusicChannel[channel].channelMain->setVolume(volume);

			if (loop)
				mMusicChannel[channel].channelMain->setLoopCount(-1);
			else
				mMusicChannel[channel].channelMain->setLoopCount(0);

			mMusicChannel[channel].channelMain->setPaused(false);
		}

		mMusicChannel[channel].mainPath = std::string(path);
	}
	else
	{
		ClearMusicChannel(channel, false, true);

		if (sound)
		{
			mFMODSystem->playSound(FMOD_CHANNEL_FREE, sound, true, 
				&mMusicChannel[channel].channelFadein);
			mMusicChannel[channel].soundFadein = sound;
			mMusicChannel[channel].fadeinVolume = volume;
			mMusicChannel[channel].channelFadein->setChannelGroup(mChannelGroupMusic);
			mMusicChannel[channel].channelFadein->setVolume(0.0f);
			
			if (loop)
				mMusicChannel[channel].channelFadein->setLoopCount(-1);
			else
				mMusicChannel[channel].channelFadein->setLoopCount(0);

			mMusicChannel[channel].channelFadein->setPaused(false);
		}

		mMusicChannel[channel].fadeinPath = std::string(path);
	}
}
//----------------------------------------------------------------------------
void FMODSoundSystem::SetMusicVolume (unsigned int channel, float volume)
{
	assertion(channel<4, "channel should be less than 4.");

	mMusicChannel[channel].volume = volume;

	if (mMusicChannel[channel].channelMain)
		mMusicChannel[channel].channelMain->setVolume(volume);

	if (mMusicChannel[channel].channelFadein)
		mMusicChannel[channel].channelFadein->setVolume(volume);
}
//----------------------------------------------------------------------------
void FMODSoundSystem::PlaySound2D (const char *filename, float volume)
{
	FMOD::Sound* sound = GetSoundResource(filename, ST_2D);

	if (sound)
	{
		FMOD::Channel *channel;
		mFMODSystem->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
		channel->setChannelGroup(mChannelGroupSound);
		channel->setVolume(volume);
		channel->setLoopCount(0);
		channel->setPaused(false);
	}
}
//----------------------------------------------------------------------------
void FMODSoundSystem::PlaySound3D (const char *filename, 
						  const SoundCreateInfo3D &createInfo)
{
	FMOD::Sound *sound = GetSoundResource(filename, ST_3D);

	if (sound)
	{
		FMOD::Channel *channel;
		mFMODSystem->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
		channel->setChannelGroup(mChannelGroupSound);
		channel->setVolume(createInfo.volume);
		channel->setLoopCount(createInfo.isloop ? -1:0);
		channel->set3DMinMaxDistance(createInfo.mindistance, 
			createInfo.maxdistance);
		
		FMOD_VECTOR pos;
		pos.x = createInfo.position.X();
		pos.y = createInfo.position.Y();
		pos.z = createInfo.position.Z();
		FMOD_VECTOR vec;
		vec.x = createInfo.velocity.X();
		vec.y = createInfo.velocity.Y();
		vec.z = createInfo.velocity.Z();
		channel->set3DAttributes(&pos, &vec);
		channel->setPaused(false);
	}
}
//----------------------------------------------------------------------------
SoundInterface *FMODSoundSystem::PlaySound2DControl (const char *filename,
													 float volume, bool loop)
{
	FMOD::Sound* sound = GetSoundResource(filename, ST_2D);
	FMODSound *soundObj = 0;

	if (sound)
	{
		FMOD::Channel *channel;
		mFMODSystem->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
		channel->setChannelGroup(mChannelGroupSound);
		channel->setVolume(volume);
		if (loop)
			channel->setLoopCount(-1);
		else
			channel->setLoopCount(0);
		channel->setPaused(false);

		soundObj = new FMODSound(channel);
	}

	return soundObj;
}
//----------------------------------------------------------------------------
SoundInterface *FMODSoundSystem::PlaySound3DControl (const char *filename,
													 const SoundCreateInfo3D 
													 &createInfo)
{
	FMOD::Sound *sound = GetSoundResource(filename, ST_3D);
	FMODSound *soundObj = 0;

	if (sound)
	{
		FMOD::Channel *channel;
		mFMODSystem->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
		channel->setChannelGroup(mChannelGroupSound);
		channel->setVolume(createInfo.volume);
		if (createInfo.isloop)
			channel->setLoopCount(-1);
		else
			channel->setLoopCount(0);
		channel->set3DMinMaxDistance(createInfo.mindistance, 
			createInfo.maxdistance);
		FMOD_VECTOR pos;
		pos.x = createInfo.position.X();
		pos.y = createInfo.position.Y();
		pos.z = createInfo.position.Z();
		FMOD_VECTOR vec;
		vec.x = createInfo.velocity.X();
		vec.y = createInfo.velocity.Y();
		vec.z = createInfo.velocity.Z();
		channel->set3DAttributes(&pos, &vec);
		channel->setPaused(false);

		soundObj = new FMODSound(channel);
	}

	return soundObj;
}
//----------------------------------------------------------------------------
void FMODSoundSystem::SetListener (const APoint *position,
								   const AVector *velocity, 
								   const AVector *forward, const AVector *up)
{
	bool hasPos = false;
	FMOD_VECTOR pos;
	if (position)
	{
		hasPos = true;
		pos.x = position->X();
		pos.y = position->Y();
		pos.z = position->Z();
	}

	bool hasVec = false;
	FMOD_VECTOR vec;
	if (velocity)
	{
		hasVec = true;
		vec.x = velocity->X();
		vec.y = velocity->Y();
		vec.z = velocity->Z();
	}

	bool hasForward = false;
	FMOD_VECTOR forw;
	if (forward)
	{
		hasForward = true;
		forw.x = forward->X();
		forw.y = forward->Y();
		forw.z = forward->Z();
	}

	bool hasUp = false;
	FMOD_VECTOR upTemp;
	if (up)
	{
		hasUp = true;
		upTemp.x = up->X();
		upTemp.y = up->Y();
		upTemp.z = up->Z();
	}

	mFMODSystem->set3DListenerAttributes(0, 
		hasPos ? &pos : 0,
		hasVec ? &vec : 0,
		hasForward ? &forw : 0,
		hasUp? &upTemp : 0);
}
//----------------------------------------------------------------------------
void FMODSoundSystem::ClearMusicChannel (int channel, bool main, bool fadein)
{
	MusicChannelInfo &info = mMusicChannel[channel];
	if (main && info.channelMain)
	{
		info.channelMain->stop();
		info.channelMain = 0;
		if (info.soundMain)
		{
			info.soundMain->release();
			info.soundMain = 0;
		}
	}

	if (fadein && info.channelFadein)
	{
		info.channelFadein->stop();
		info.channelFadein = 0;
		if (info.soundFadein)
		{
			info.soundFadein->release();
			info.soundFadein = 0;
		}
	}
}
//----------------------------------------------------------------------------
FMOD::Sound *FMODSoundSystem::GetSoundResource (const char *fileName,
												SoundType type)
{
	if (!fileName)
		return 0;

	SoundResourceMap::iterator it = mSoundResourceMap.find(fileName);
	if (it != mSoundResourceMap.end())
	{
		return (*it).second->FMODSound;
	}

	FMOD::Sound *sound = 0;
	FMOD_MODE mode = FMOD_LOOP_NORMAL|FMOD_3D_LINEARROLLOFF|FMOD_HARDWARE
		|FMOD_OPENMEMORY;

	if (type == ST_2D)
		mode |= FMOD_2D;
	else
		mode |= FMOD_3D;

	char *buffer;
	int bufferSize;
	if (!FileIO::Load(fileName, true, bufferSize, buffer))
	{
		assertion(false, "Open sound file failed: %s", fileName);
	}
	else
	{
		FMOD_CREATESOUNDEXINFO exinfo;
		memset(&exinfo, 0, sizeof(exinfo));
		exinfo.cbsize = sizeof(exinfo);
		exinfo.length = bufferSize;

		if (mFMODSystem->createSound((const char*)buffer, mode, &exinfo, 
			&sound) != FMOD_OK)
		{
			assertion(false, "createSound %s failed.", fileName);
		}
	}

	FMODSoundResource *res = new FMODSoundResource;
	res->soundName = std::string(fileName);
	res->FMODSound = sound;
	mSoundResourceMap[res->soundName] = res;

	return sound;
}
//----------------------------------------------------------------------------