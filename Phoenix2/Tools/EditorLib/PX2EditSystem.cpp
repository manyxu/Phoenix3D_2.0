/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditorOptions.cpp
*
*/

#include "PX2EditSystem.hpp"
#include "PX2EditMap.hpp"
#include "PX2TerrainEdit.hpp"
#include "PX2EffectEdit.hpp"
#include "PX2ActorSelection.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditCommand.hpp"
using namespace PX2;
using namespace PX2Editor;

//----------------------------------------------------------------------------
EditSystem::EditSystem ()
{
	mEditorEventWorld = 0;
	mEditMap = 0;
}
//----------------------------------------------------------------------------
EditSystem::~EditSystem ()
{
}
//----------------------------------------------------------------------------
void EditSystem::SetEditMode (EditSystem::EditMode mode)
{
	mMode = mode;

	Event *event = 0;
	event = EditorEventSpace::CreateEvent(EditorEventSpace::SetEditMode);
	event->SetData<EditSystem::EditMode>(mMode);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	if (mode == EditSystem::EM_TERRAIN_HEIGHT)
	{
		mTerrainEdit->SetEditType(TerrainProcess::TPT_HEIGHT);
		mTerrainEdit->EnableEdit();
	}
	else if (mode == EditSystem::EM_TERRAIN_TEXTURE)
	{
		mTerrainEdit->SetEditType(TerrainProcess::TPT_TEXTURE);
		mTerrainEdit->EnableEdit();
	}
	else
	{
		mTerrainEdit->DisableEdit();
	}

	mHelpScene->Update();
}
//----------------------------------------------------------------------------
EditSystem::EditMode EditSystem::GetEditMode ()
{
	return mMode;
}
//----------------------------------------------------------------------------
bool EditSystem::Initlize ()
{
	mEditorEventWorld = new0 EventWorld();
	PX2_UNUSED(mEditorEventWorld);

	mTerrainEdit = new TerrainEdit();
	mEditorEventWorld->ComeIn(mTerrainEdit);

	mEffectEdit = new EffectEdit();

	mHelpScene = new0 Node();
	mHelpScene->AttachChild(mTerrainEdit->GetBrush()->GetRenderable());

	mEditMap = new0 EditMap();

	ActorSelection *selection = new0 ActorSelection;
	PX2_UNUSED(selection);

	EditCommandManager *editCommandManager = new0 EditCommandManager;
	PX2_UNUSED(editCommandManager);

	return true;
}
//----------------------------------------------------------------------------
bool EditSystem::Terminate ()
{
	ActorSelection *selection = ActorSelection::GetSingletonPtr();
	if (selection)
		delete0(selection);

	if (mEditMap)
	{
		delete0(mEditMap);
		mEditMap = 0;
	}

	if (mTerrainEdit)
	{
		delete mTerrainEdit;
		mTerrainEdit = 0;
	}

	if (mEffectEdit)
	{
		delete mEffectEdit;
		mEffectEdit = 0;
	}

	if (mEditorEventWorld)
	{
		delete0(mEditorEventWorld);
		mEditorEventWorld = 0;
	}

	EditCommandManager *manager = EditCommandManager::GetSingletonPtr();
	if (manager)
	{
		delete0(manager);
	}

	return true;
}
//----------------------------------------------------------------------------
void EditSystem::SetPreViewObject (PX2::Object *obj)
{
	mPreViewObject = obj;

	Event *ent = EditorEventSpace::CreateEvent(
		EditorEventSpace::SetPreViewObject);
	ent->SetData<PX2::Object*>(obj);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
PX2::Object *EditSystem::GetPreViewObject ()
{
	return mPreViewObject;
}
//----------------------------------------------------------------------------
void EditSystem::SetSelectedResource (PX2::Object *obj)
{
	mSelectedResource = obj;
}
//----------------------------------------------------------------------------
void EditSystem::SetSelectedResourceName (std::string name)
{
	mSelectedResourceName = name;
}
//----------------------------------------------------------------------------
PX2::Object *EditSystem::GetSelectedResource ()
{
	return mSelectedResource;
}
//----------------------------------------------------------------------------
std::string EditSystem::GetSelectedResourceName ()
{
	return mSelectedResourceName;
}
//----------------------------------------------------------------------------