/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ObjectTree.cpp
*
*/

#include "PX2ObjectTree.hpp"
#include "PX2ObjectTreeItem.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2EditSystem.hpp"
#include "PX2EditEventType.hpp"
#include "PX2SkyActor.hpp"
#include "PX2EffectActor.hpp"
#include "PX2AmbientRegionActor.hpp"
#include "PX2TerrainActor.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIPicBox.hpp"
#include "PX2UIStaticText.hpp"
#include "PX2UIManager.hpp"
#include "PX2Project.hpp"

using namespace PX2Editor;
using namespace PX2;

#define ID_OBJECTTREE wxID_HIGHEST + 5100

#define IC_PROJECT 0
#define IC_SCENE 1
#define IC_SKY 2
#define IC_TERRAIN 3
#define IC_ROAD 4
#define IC_WATER 5
#define IC_OBJECT 6
#define IC_EFFECT 7
#define IC_LIGHT 8
#define IC_SOUND 9
#define IC_ENVIRONMENT 10
#define IC_UI 11

BEGIN_EVENT_TABLE(ObjectTree, wxTreeCtrl)
EVT_TREE_SEL_CHANGED(ID_OBJECTTREE, ObjectTree::OnSelChanged)
EVT_TREE_ITEM_ACTIVATED(ID_OBJECTTREE, ObjectTree::OnItemActivated)
EVT_TREE_SEL_CHANGING(ID_OBJECTTREE, ObjectTree::OnSelChanging)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
ObjectTree::ObjectTree (wxWindow *parent)
:
wxTreeCtrl(parent, ID_OBJECTTREE, wxDefaultPosition, wxDefaultSize,
	wxTR_DEFAULT_STYLE),
mMainFrameItem(0)
{
	//mImageList = new wxImageList(16, 16);
	//mImageList->Add(wxIcon(wxT("ToolRes/icons/project.png"), wxBITMAP_TYPE_PNG));
	//mImageList->Add(wxIcon(wxT("ToolRes/icons/scene.png"), wxBITMAP_TYPE_PNG));
	//mImageList->Add(wxIcon(wxT("ToolRes/icons/sky.png"), wxBITMAP_TYPE_PNG));
	//mImageList->Add(wxIcon(wxT("ToolRes/icons/terrain.png"), wxBITMAP_TYPE_PNG));
	//mImageList->Add(wxIcon(wxT("ToolRes/icons/road.png"), wxBITMAP_TYPE_PNG));
	//mImageList->Add(wxIcon(wxT("ToolRes/icons/water.png"), wxBITMAP_TYPE_PNG));
	//mImageList->Add(wxIcon(wxT("ToolRes/icons/object.png"), wxBITMAP_TYPE_PNG));
	//mImageList->Add(wxIcon(wxT("ToolRes/icons/effect.png"), wxBITMAP_TYPE_PNG));
	//mImageList->Add(wxIcon(wxT("ToolRes/icons/light.png"), wxBITMAP_TYPE_PNG));
	//mImageList->Add(wxIcon(wxT("ToolRes/icons/sound.png"), wxBITMAP_TYPE_PNG));
	//mImageList->Add(wxIcon(wxT("ToolRes/icons/environment.png"), wxBITMAP_TYPE_PNG));
	//mImageList->Add(wxIcon(wxT("ToolRes/icons/ui.png"), wxBITMAP_TYPE_PNG));
	//SetImageList(mImageList);
	mRootItemId = AddRoot(PX2_LM.GetValue("Project"), IC_PROJECT);	

	mSceneItemId = AppendItem(mRootItemId, PX2_LM.GetValue("Scene"), IC_SCENE);
	mSkyItemId = AppendItem(mSceneItemId, PX2_LM.GetValue("Sky"), IC_SKY);
	mTerrainItemId = AppendItem(mSceneItemId, PX2_LM.GetValue("Terrain"), IC_TERRAIN);
	mWaterItemId = AppendItem(mSceneItemId, PX2_LM.GetValue("Water"), IC_WATER);
	mObjectsItemId = AppendItem(mSceneItemId, PX2_LM.GetValue("Objects"), IC_OBJECT);
	mEffectsItemId = AppendItem(mSceneItemId, PX2_LM.GetValue("Effects"), IC_EFFECT);
	mLightsItemId = AppendItem(mSceneItemId, PX2_LM.GetValue("Lights"), IC_LIGHT);
	mSoundsItemId = AppendItem(mSceneItemId, PX2_LM.GetValue("Sounds"), IC_SOUND);
	mEnvItemId = AppendItem(mSceneItemId, PX2_LM.GetValue("Environments"), IC_ENVIRONMENT);

	mUIId = AppendItem(mRootItemId, PX2_LM.GetValue("UI"), IC_UI);

	if (Project::GetSingletonPtr())
	{
		UIFrame *frame = Project::GetSingleton().GetUI();
		if (frame)
		{
			mMainFrameItem = new ObjectTreeItem(this, mUIId, 0,	frame, IC_UI);
		}
	}

	Expand(mRootItemId);
	Expand(mSceneItemId);
	Expand(mUIId);
	SetItemBold(mSceneItemId, true);
	SetItemBold(mUIId, true);

	RefreshScene();
}
//-----------------------------------------------------------------------------
ObjectTree::~ObjectTree ()
{
	ClearProject();
}
//-----------------------------------------------------------------------------
ObjectTreeItem *ObjectTree::GetItem (wxTreeItemId id)
{
	ObjectTreeItem *item = 0;

	for (int i=0; i<(int)mSceneItems.size(); i++)
	{
		if (mSceneItems[i])
		{
			item = mSceneItems[i]->GetItem(id);
			if (item)
			{
				return item;
			}
		}
	}

	if (mMainFrameItem)
	{
		item = mMainFrameItem->GetItem(id);
		if (item)
		{
			return item;
		}
	}

	return 0;
}
//-----------------------------------------------------------------------------
ObjectTreeItem *ObjectTree::GetItem (PX2::Object *obj)
{
	ObjectTreeItem *item = 0;

	for (int i=0; i<(int)mSceneItems.size(); i++)
	{
		item = mSceneItems[i]->GetItem(obj);
		if (item)
		{
			return item;
		}
	}

	if (mMainFrameItem)
	{
		item = mMainFrameItem->GetItem(obj);
		if (item)
		{
			return item;
		}
	}

	return 0;
}
//-----------------------------------------------------------------------------
void ObjectTree::OnItemActivated (wxTreeEvent& event)
{
}
//-----------------------------------------------------------------------------
void ObjectTree::OnSelChanged (wxTreeEvent& event)
{
	if (!Project::GetSingletonPtr())
		return;

	wxTreeItemId id = event.GetItem();

	ObjectTreeItem *item = GetItem(id);
	if (item)
	{
		Object *obj = item->GetObject();
		if (obj)
		{
			EditSystem::GetSingleton().GetSelection()->Clear();
			EditSystem::GetSingleton().GetSelection()->AddObject(obj);
		}
	}
	else
	{
		wxString itemName = GetItemText(id);
		if (PX2_LM.GetValue("Project") == itemName)
		{
			Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::SelectPSU);
			ent->SetData<int>(1);
			EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
		}
		else if (PX2_LM.GetValue("Scene") == itemName)
		{
			Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::SelectPSU);
			ent->SetData<int>(2);
			EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
		}
		else if (PX2_LM.GetValue("UI") == itemName)
		{
			Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::SelectPSU);
			ent->SetData<int>(3);
			EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
		}
	}
}
//-----------------------------------------------------------------------------
void ObjectTree::OnSelChanging (wxTreeEvent& event)
{

}
//-----------------------------------------------------------------------------
void ObjectTree::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void ObjectTree::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::NewProject))
	{
		RefreshProject();
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::LoadedProject))
	{
		RefreshProject();
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::ClosedProject))
	{
		ClearProject();
	}
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::NewScene))
	{
		RefreshScene();
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::LoadedScene))
	{
		RefreshScene();
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::CloseScene))
	{
		ClearScene();
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::AddActor))
	{
		Actor *actor = event->GetData<Actor*>();
		AddActor(actor);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::RemoveActor))
	{
		Actor *actor = event->GetData<Actor*>();
		RemoveActor(actor);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::ObjectNameChanged))
	{
		Object *obj = event->GetData<Object*>();
		ObjectTreeItem *item = GetItem(obj);
		if (item)
		{
			item->SetName(obj->GetName());
		}
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::AddUI))
	{
		Object *obj = event->GetData<Object*>();
		Movable *mov = DynamicCast<Movable>(obj);
		if (mov)
		{
			ObjectTreeItem *itemPar = GetItem(mov->GetParent());
			if (itemPar)
			{
				itemPar->AddChild(mov);
				Expand(itemPar->GetItemId());
			}
		}
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::RemoveUI))
	{
		Object *obj = event->GetData<Object*>();
		ObjectTreeItem *item = GetItem(obj);
		ObjectTreeItem *parItem = item->GetParent();
		if (parItem)
		{
			parItem->RemoveChild(obj);
		}
	}
}
//-----------------------------------------------------------------------------
void ObjectTree::DoLeave ()
{

}
//-----------------------------------------------------------------------------
void ObjectTree::RefreshProject ()
{
	ClearProject();
	RefreshScene();
	RefreshUI();
}
//-----------------------------------------------------------------------------
void ObjectTree::RefreshScene ()
{
	ClearScene();

	Scene *scene = 0;

	if (Project::GetSingletonPtr())
	{
		scene = Project::GetSingleton().GetScene();
	}

	if (!scene)
		return;

	for (int i=0; i<scene->GetActorQuantity(); i++)
	{
		Actor *actor = scene->GetActor(i);
		if (actor)
		{
			AddActor(actor);
		}
	}
}
//-----------------------------------------------------------------------------
void ObjectTree::ClearProject ()
{
	ClearScene();
	ClearUI();
}
//-----------------------------------------------------------------------------
void ObjectTree::ClearScene ()
{
	for (int i=0; i<(int)mSceneItems.size(); i++)
	{
		if (mSceneItems[i])
		{
			delete0(mSceneItems[i]);
		}
	}

	mSceneItems.clear();
}
//-----------------------------------------------------------------------------
void ObjectTree::RefreshUI ()
{
	ClearUI();

	Project *proj = Project::GetSingletonPtr();
	if (proj)
	{
		UIFrame *frame = proj->GetUI();
		if (frame)
		{
			mMainFrameItem = new ObjectTreeItem(this, mUIId, 0,	frame, IC_UI);
		}
	}
}
//-----------------------------------------------------------------------------
void ObjectTree::ClearUI()
{
	if (mMainFrameItem)
	{
		delete mMainFrameItem;
		mMainFrameItem = 0;
	}
}
//-----------------------------------------------------------------------------
void ObjectTree::AddActor (PX2::Actor *actor)
{
	wxTreeItemId id = mObjectsItemId;
	int icId = IC_OBJECT;
	
	if (actor)
	{
		if (actor->IsDerived(TerrainActor::TYPE))
		{
			id = mTerrainItemId;
			icId = IC_TERRAIN;
		}
		else if (actor->IsDerived(EffectActor::TYPE))
		{
			id = mEffectsItemId;
			icId = IC_EFFECT;
		}
		else if (actor->IsDerived(AmbientRegionActor::TYPE))
		{
			id = mEnvItemId;
			icId = IC_ENVIRONMENT;
		}
		else if (actor->IsDerived(SkyActor::TYPE))
		{
			id = mSkyItemId;
			icId = IC_SKY;
		}
		else
		{
			id = mObjectsItemId;
			icId = IC_OBJECT;
		}

		ObjectTreeItem *item = new ObjectTreeItem(this, id, 0, actor, icId);
		mSceneItems.push_back(item);
	}
}
//-----------------------------------------------------------------------------
void ObjectTree::RemoveActor (PX2::Actor *actor)
{
	ObjectTreeItem *item = GetItem(actor);
	if (item)
	{
		std::vector<ObjectTreeItem*>::iterator it = mSceneItems.begin();
		for (; it!=mSceneItems.end(); it++)
		{
			if (item == *it)
			{
				mSceneItems.erase(it);
				delete0(item);
				return;
			}
		}
	}
}
//-----------------------------------------------------------------------------