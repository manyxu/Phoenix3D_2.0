/*
*
* ÎÄ¼þÃû³Æ	£º	SystemManager.cpp
*
*/

#include "PX2SystemManager.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
bool SystemManager::Initialize ()
{
#ifdef PX2_USE_MEMORY
	Memory::Initialize();
#endif

	// Graphics
	GraphicsRoot *root = new GraphicsRoot();
	if (!root)
		return false;

	if (!root->Initlize())
		return false;

	// EditSystem
	EditSystem *editSystem = new0 EditSystem();
	editSystem->Initlize();

	// ResMan
	ResourceManager *resMan = new0 ResourceManager();
	PX2_UNUSED(resMan);

	// Sound
	SoundSystemInitInfo info;
	info.maxchannels = 512;
	info.dopplerscale = 1.0f;
	info.distancefactor = 100.0f;
	info.rolloffscale = 1.2f;
	SoundSystem *soundSys = SoundSystem::CreateSoundSystem(
		SoundSystem::SST_FMOD, info);
	PX2_UNUSED(soundSys);

	return true;
}
//-----------------------------------------------------------------------------
bool SystemManager::Terminate ()
{
	// Sound
	SoundSystem *soundSys = SoundSystem::GetSingletonPtr();
	if (soundSys)
		delete0(soundSys);

	// ResMan
	ResourceManager *resMan = ResourceManager::GetSingletonPtr();
	if (resMan)
		delete0(resMan);

	// EditSystem
	EditSystem *editSystem = EditSystem::GetSingletonPtr();
	if (editSystem)
	{
		editSystem->Terminate();
		delete0(editSystem);
	}

	// Graphics
	GraphicsRoot *graphicsRoot = GraphicsRoot::GetSingletonPtr();
	if (graphicsRoot)
	{
		graphicsRoot->Terminate();
		delete0(graphicsRoot);
	}

#ifdef PX2_USE_MEMORY
	Memory::Terminate("MemoryReport.txt");
#endif

	return true;
}
//-----------------------------------------------------------------------------