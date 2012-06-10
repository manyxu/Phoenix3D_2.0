/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SoundSystem.cpp
*
*/

#include "PX2SoundSystem.hpp"
#include "PX2SoundSystemFMOD.hpp"
using namespace PX2;

SoundSystem *SoundSystem::CreateSoundSystem (SoundSystemType type,
											 const SoundSystemInitInfo &initInfo)
{
	if(type == SST_FMOD)
	{
		FMODSoundSystem *soundSystem = new0 FMODSoundSystem();
		if (!soundSystem->Initialize(initInfo))
		{
			delete0(soundSystem);
			return 0;
		}

		return soundSystem;
	}
	else
	{
		assertion(false, "Not supported now.");
	}

	return 0;
}
//----------------------------------------------------------------------------