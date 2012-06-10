/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2SoundSystemFMod.hpp
*
* 版本		:	1.0 (2011/03/30)
*
* 作者		：	more
*
*/

#ifndef PX2SOUNDSYSTEMFMOD_HPP
#define PX2SOUNDSYSTEMFMOD_HPP

#include "PX2SoundSystemPrerequisites.hpp"
#include "PX2SoundSystem.hpp"

namespace PX2
{

	class FMODSound : public SoundInterface
	{
	public:
		FMODSound (FMOD::Channel *channel);
		virtual ~FMODSound ();

		virtual bool IsPlaying ();
		virtual void SetVolume (float volume);
		virtual void SetPaused (bool paused);
		virtual void Stop ();

		virtual void SetPosition (const APoint &position);
		virtual void SetVelocity (const AVector &velocity);
		virtual void SetDistance (float mindist, float maxdist);

	private:
		FMOD::Channel *mChannel;
	};

	struct  FMODSoundResource
	{
		std::string soundName;
		FMOD::Sound *FMODSound;
		unsigned int refCount;
	};

	typedef std::map<std::string, FMODSoundResource*> SoundResourceMap;

	class FMODSoundSystem : public SoundSystem
	{
	public:
		FMODSoundSystem ();
		virtual ~FMODSoundSystem ();

		bool Initialize (const SoundSystemInitInfo &initInfo);
		bool Terminate ();

		virtual void Update ();

		virtual void PlayMusic (unsigned int channel, const char *filename,
			bool loop, unsigned int fadeTime, float volume=1.0f);
		virtual void PlayMusicInternal(unsigned int channel, 
			FMOD::Sound *sound, bool loop, unsigned int fadeTime, 
			float volume=1.0f, const char *path="");

		virtual void SetMusicVolume (unsigned int channel, float volume);

		virtual void PlaySound2D (const char *filename, float volume);
		virtual void PlaySound3D (const char *filename, 
			const SoundCreateInfo3D &createInfo);

		virtual SoundInterface *PlaySound2DControl (const char *filename,
			float volume, bool loop);
		virtual SoundInterface *PlaySound3DControl (const char *filename, 
			const SoundCreateInfo3D &createInfo);

		virtual void SetListener (const APoint *position,
			const AVector *velocity, const AVector *forward,
			const AVector *up);

	protected:
		void ClearMusicChannel (int channel, bool main, bool fadein);

		enum SoundType
		{
			ST_2D,
			ST_3D
		};

		FMOD::Sound *GetSoundResource (const char *fileName, SoundType type);

		FMOD::System *mFMODSystem;

		// Music
		FMOD::ChannelGroup *mChannelGroupMusic;
		struct MusicChannelInfo
		{
			FMOD::Channel *channelMain;
			FMOD::Channel *channelFadein;
			FMOD::Sound *soundMain;
			FMOD::Sound *soundFadein;
			unsigned int fadeinTimeLength;
			unsigned int fadeinTimeLeft;
			float mainVolume;
			float fadeinVolume;
			float volume;
			std::string mainPath;
			std::string fadeinPath;
		};
		MusicChannelInfo mMusicChannel[4];

		// Sound
		FMOD::ChannelGroup *mChannelGroupSound;
		SoundResourceMap mSoundResourceMap;

		unsigned int mTimeLastUpdate;
	};

}

#endif