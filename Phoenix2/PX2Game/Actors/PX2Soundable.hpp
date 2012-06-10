/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Soundable.hpp
*
* 版本		:	1.0 (2011/02/25)
*
* 作者		：	more
*
*/

#ifndef PX2SOUNDABLE_HPP
#define PX2SOUNDABLE_HPP

#include "PX2GamePrerequisites.hpp"
#include "PX2Movable.hpp"

namespace PX2
{

	class Soundable : public Movable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Soundable);

	public:
		Soundable (); //< 未初始化
		Soundable (const char *fileName, const SoundCreateInfo3D &createInfo);
		virtual ~Soundable ();

		void Play ();
		bool IsPlaying ();
		void Pause (bool pause);
		void Stop ();

		void SetSoundFile (std::string filename);
		std::string GetSoundFile ();

		void Set2d (bool is2d);
		bool Is2d ();
		void SetVolume (float volume);
		float GetVolume ();
		void SetVelocity (const AVector &velocity);
		AVector GetVelocity ();
		void SetDistance (float minDistance, float maxDistance);
		void SetMinDistance (float minDistance);
		void SetMaxDistance (float maxDistance);
		float GetMinDistance ();
		float GetMaxDistance ();
		void SetLoop (bool loop);
		bool IsLoop ();

		virtual void OnAttach ();
		virtual void OnDetach ();

	protected:
		virtual void UpdateWorldData (double applicationTime);
		virtual void UpdateWorldBound ();
		virtual void GetVisibleSet (Culler& culler, bool);

		std::string mFilename;
		bool mIs2d;
		SoundCreateInfo3D mCreateInfo;
		SoundInterfacePtr mSound;
	};

	PX2_REGISTER_STREAM(Soundable);
	typedef Pointer0<Soundable> SoundablePtr;
#include "PX2Soundable.inl"

}

#endif