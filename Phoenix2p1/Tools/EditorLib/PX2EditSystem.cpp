/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditSystem.cpp
*
*/

#include "PX2EditSystem.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditMap.hpp"
#include "PX2ActorSelection.hpp"
using namespace PX2;
using namespace PX2Editor;

//----------------------------------------------------------------------------
EditSystem::EditSystem ()
	:
mEditMode(EM_NONE),
mEditMap(0),
mSelection(0)
{
}
//----------------------------------------------------------------------------
EditSystem::~EditSystem ()
{
}
//----------------------------------------------------------------------------
bool EditSystem::Initlize ()
{
#ifdef PX2_USE_MEMORY
	Memory::Initialize();
#endif

	EventWorld *entWorld = new0 EventWorld();
	PX2_UNUSED(entWorld);

	GraphicsRoot *root = new0 GraphicsRoot();
	if (root)
	{
		root->Initlize();
	}
	else
	{
		return false;
	}

	ResourceManager *resMan = new0 ResourceManager();
	PX2_UNUSED(resMan);

	mEditMap = new0 EditMap();
	mSelection = new0 ActorSelection();

	mHelpScene = new0 Node();

	return true;
}
//----------------------------------------------------------------------------
bool EditSystem::Terminate ()
{
	mHelpScene = 0;

	if (mSelection)
	{
		delete0(mSelection);
		mSelection = 0;
	}

	if (mEditMap)
	{
		delete0(mEditMap);
		mEditMap = 0;
	}

	ResourceManager *resMan = ResourceManager::GetSingletonPtr();
	if (resMan)
	{
		delete0(resMan);
	}

	GraphicsRoot *graphicsRoot = GraphicsRoot::GetSingletonPtr();
	if (graphicsRoot)
	{
		graphicsRoot->Terminate();
		delete0(graphicsRoot);
	}

	EventWorld *entWorld = EventWorld::GetSingletonPtr();
	if (entWorld)
	{
		delete0(entWorld);
	}

#ifdef PX2_USE_MEMORY
	Memory::Terminate("PX2Editor_MemoryReport.txt", false);
#endif

	return true;
}
//----------------------------------------------------------------------------
void EditSystem::SetEditMode (EditSystem::EditMode mode)
{
	mEditMode = mode;

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(EditorEventSpace::SetEditMode);
	event->SetData<EditSystem::EditMode>(mEditMode);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	mHelpScene->Update();
}
//----------------------------------------------------------------------------