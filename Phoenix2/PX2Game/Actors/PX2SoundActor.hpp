/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2SoundActor.hpp
*
* 版本		:	1.0 (2011/04/10)
*
* 作者		：	more
*
*/

#ifndef PX2SOUNDACTOR_HPP
#define PX2SOUNDACTOR_HPP

#include "PX2Actor.hpp"
#include "PX2Soundable.hpp"

namespace PX2
{

	class SoundActor : public Actor
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(SoundActor);

	public:
		SoundActor (const char *fileName);
		SoundActor (Soundable *soundable);
		~SoundActor ();

		PX2::Soundable *GetSoundable ();
		void Play ();

		// 消息处理
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

	protected:
		PX2::SoundablePtr mSoundable;
	};

	PX2_REGISTER_STREAM(SoundActor);
	typedef Pointer0<SoundActor> SoundActorPtr;
#include "PX2SoundActor.inl"

}

#endif