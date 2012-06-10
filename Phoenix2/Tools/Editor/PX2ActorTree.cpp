/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ActorTree.cpp
*
*/

#include "PX2ActorTree.hpp"
#include "PX2ActorTreeItem.hpp"
#include "PX2EditEventType.hpp"
#include "PX2ActorSelection.hpp"
using namespace PX2Editor;
using namespace PX2;

#define ID_ACTORTREE wxID_HIGHEST + 1000

BEGIN_EVENT_TABLE(ActorTree, wxTreeCtrl)
	EVT_TREE_SEL_CHANGED(ID_ACTORTREE, ActorTree::OnSelChanged)
	EVT_TREE_ITEM_ACTIVATED(ID_ACTORTREE, ActorTree::OnItemActivated)
	EVT_TREE_SEL_CHANGING(ID_ACTORTREE, ActorTree::OnSelChanging)
END_EVENT_TABLE()

ActorTree::ActorTree (wxWindow *parent)
:
wxTreeCtrl(parent, ID_ACTORTREE)
{
	mRootItemId = AddRoot(wxT("Scene"), 0);
	mSkyItemId = AppendItem(mRootItemId, wxT("Sky"), 0);
	mTerrainItemId = AppendItem(mRootItemId, wxT("Terrain"), 0);
	mWaterItemId = AppendItem(mRootItemId, wxT("Water"), 0);
	mObjectsItemId = AppendItem(mRootItemId, wxT("Objects"), 0);
	mLightsItemId = AppendItem(mRootItemId, wxT("Light"), 2);
	mEnvItemId = AppendItem(mRootItemId, wxT("Environment"), 0);

	ExpandAll();
}
//-----------------------------------------------------------------------------
ActorTree::~ActorTree ()
{
	RemoveAllActors();
}
//-----------------------------------------------------------------------------
ActorTreeItem *ActorTree::AddActor (wxTreeItemId parentID, PX2::Actor *actor)
{
	ActorTreeItem *item = new ActorTreeItem(this, parentID, actor);

	mItems.push_back(item);

	return item;
}
//-----------------------------------------------------------------------------
void ActorTree::RemoveActor (PX2::Actor *actor)
{
	std::vector<ActorTreeItem*>::iterator iter = mItems.begin();

	for (; iter!=mItems.end(); iter++)
	{
		if ((*iter)->GetActor() == actor)
		{
			delete *iter;

			mItems.erase(iter);

			return;
		}
	}
}
//-----------------------------------------------------------------------------
void ActorTree::RemoveAllActors ()
{
	for (int i=0; i<(int)mItems.size(); i++)
	{
		delete mItems[i];
	}

	mItems.clear();
}
//-----------------------------------------------------------------------------
ActorTreeItem *ActorTree::GetItem (wxTreeItemId id)
{
	for (int i=0; i<(int)mItems.size(); i++)
	{
		if (id == mItems[i]->GetItemID())
			return mItems[i];
	}

	return 0;
}
//-----------------------------------------------------------------------------
ActorTreeItem *ActorTree::GetItem (PX2::Actor *actor)
{
	for (int i=0; i<(int)mItems.size(); i++)
	{
		if (actor == mItems[i]->GetActor())
			return mItems[i];
	}

	return 0;
}
//-----------------------------------------------------------------------------
void ActorTree::OnItemActivated (wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();

	ActorTreeItem *item = GetItem(id);

	if (item && (item->GetItemID()!=mEnvItemId))
	{
		ActorSelection::GetSingleton().Clear();
		PX2::Actor *actor = item->GetActor();
		if (actor)
			ActorSelection::GetSingleton().AddActor(item->GetActor());
	}
}
//-----------------------------------------------------------------------------
void ActorTree::OnSelChanged (wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();

	ActorTreeItem *item = GetItem(id);

	if (item && (item->GetItemID()!=mEnvItemId))
	{
		ActorSelection::GetSingleton().Clear();
		PX2::Actor *actor = item->GetActor();
		if (actor)
			ActorSelection::GetSingleton().AddActor(item->GetActor());
	}

//	if (item->GetItemID() == mEnvItemId)
	{

	}
}
//-----------------------------------------------------------------------------
void ActorTree::OnSelChanging (wxTreeEvent& event)
{

}
//-----------------------------------------------------------------------------
void ActorTree::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void ActorTree::DoUpdate ()
{

}
//-----------------------------------------------------------------------------
void ActorTree::DoExecute (Event *event)
{
	if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::NewScene))
	{
		RefleshScene();
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::LoadedScene))
	{
		RefleshScene();
	}

	if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::CreateTerrainAndAddToScene))
	{
		RawTerrainActor *terrainActor = event->GetData<RawTerrainActor*>();
		AddActor(mTerrainItemId, terrainActor);
		ExpandAllChildren(mTerrainItemId);
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::CreateLightActor))
	{
		LightActor *lightActor = event->GetData<LightActor*>();
		AddActor(mLightsItemId, lightActor);
		ExpandAllChildren(mLightsItemId);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::
		AddActor))
	{
		Actor *actor = event->GetData<Actor*>();
		AddActor(mObjectsItemId, actor);
		ExpandAllChildren(mObjectsItemId);
	}

	if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::ObjectNamePropertyChanged))
	{
		Object *object = event->GetData<Object*>();

		if (object)
		{
			PX2::Actor *actor = DynamicCast<Actor>(object);

			if (actor)
			{
				ActorTreeItem *item = GetItem(actor);
				if (item)
				{
					item->SetName(actor->GetName());
				}
			}
		}
	}

	if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::RemoveActor))
	{
		Actor *actor = event->GetData<Actor*>();
		RemoveActor(actor);
	}
}
//-----------------------------------------------------------------------------
void ActorTree::DoLeave ()
{

}
//-----------------------------------------------------------------------------
void ActorTree::RefleshScene ()
{
	RemoveAllActors();

	PX2::Scene *scene = EditSystem::GetSingleton().GetEditMap()->GetScene();
	int actorQuantity = scene->GetActorQuantity();

	for (int i=0; i<actorQuantity; i++)
	{
		Actor *actor = scene->GetActor(i);

		if (actor->IsExactly(LODTerrainActor::TYPE))
		{
			AddActor(mTerrainItemId, actor);
		}
		else if (actor->IsExactly(RawTerrainActor::TYPE))
		{
			AddActor(mTerrainItemId, actor);
		}
		else if (actor->IsExactly(LightActor::TYPE))
		{
			AddActor(mLightsItemId, actor);
		}
		else if (actor->IsExactly(AmbientRegionActor::TYPE))
		{
			AddActor(mEnvItemId, actor);
		}
		else
		{
			AddActor(mObjectsItemId, actor);
		}
	}
}
//-----------------------------------------------------------------------------