/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2SoundSystem.hpp
*
* 版本		:	1.0 (2011/03/30)
*
* 作者		：	more
*
*/

#ifndef PX2SOUNDSYSTEM_HPP
#define PX2SOUNDSYSTEM_HPP

#include "PX2APoint.hpp"
#include "PX2AVector.hpp"
#include "PX2SmartPointer.hpp"
#include "PX2Singleton.hpp"

namespace PX2
{

	class SoundInterface
	{
	public:
		virtual ~SoundInterface() {}

		// 操作
		virtual bool IsPlaying () = 0;
		virtual void SetVolume (float volume) = 0;
		virtual void SetPaused (bool paused) = 0;
		virtual void Stop () = 0;

		// 方位
		/*
		* 以下方法仅对3dSound有效
		*/
		virtual void SetPosition (const APoint &position) = 0;
		virtual void SetVelocity (const AVector &velocity) = 0;
		virtual void SetDistance (float minDistance, float maxDistance) = 0;
	};

	typedef Pointer0<SoundInterface> SoundInterfacePtr;

	struct SoundSystemInitInfo
	{
		int maxchannels;
		float dopplerscale;
		float distancefactor;
		float rolloffscale;
	};

	struct SoundCreateInfo3D
	{
		SoundCreateInfo3D ()
		{
			mindistance = 0.0f;
			maxdistance = 10.0f;
			volume = 1.0f;
			isloop = true;
		}

		float mindistance; 
		float maxdistance;
		float volume;
		APoint position;
		AVector velocity;
		bool isloop;
	};

	class SoundSystem : public Singleton<SoundSystem>
	{
	public:
		virtual ~SoundSystem() {}

		enum SoundSystemType
		{
			SST_FMOD,
			SST_DUMMY
		};

		SoundSystemType GetSystemType ()
		{
			return mType;
		}

		static SoundSystem *CreateSoundSystem (SoundSystemType type,
			const SoundSystemInitInfo &initInfo);

		virtual void Update () = 0;

		//============================================================================
		// 音乐

		/// 在指定通道播放音乐
		/**
		* channel : 播放音乐的通道（0-3）
		* filename : 音乐文件名，为0表示停止当前音乐
		* loop : 是否循环播放
		* fadetick : 淡入淡出时间，为0表示立即最大音量播放
		*/
		virtual void PlayMusic (unsigned int channel, const char *filename,
			bool loop, unsigned int fadetick, float volume=1.0f) = 0;

		/// 设置音量
		/**
		* channel ： 设定音量的通道（0-3）
		* volume ： 设定音量值（0.0f-1.0f）
		*/
		virtual void SetMusicVolume (unsigned int channel, float volume) = 0;

		//============================================================================
		// 声音

		/// 设置声音
		virtual void PlaySound2D (const char *filename, float volume) = 0;
		virtual void PlaySound3D (const char *filename, 
			const SoundCreateInfo3D &createInfo) = 0;

		// 返回ISound接口
		virtual SoundInterface *PlaySound2DControl (const char *filename,
			float volume, bool loop) = 0;
		virtual SoundInterface *PlaySound3DControl (const char *filename, 
			const SoundCreateInfo3D &createInfo) = 0;

		/// 设置监听者
		/**
		* 不关心的参数可以设置为0
		*/
		virtual void SetListener (const APoint *position,
			const AVector *velocity, const AVector *forward,
			const AVector *up) = 0;

	protected:
		SoundSystemType mType;
	};

}

#endif