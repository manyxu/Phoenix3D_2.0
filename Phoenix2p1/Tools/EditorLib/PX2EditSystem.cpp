/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditSystem.cpp
*
*/

#include "PX2EditSystem.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditMap.hpp"
#include "PX2ObjectSelection.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2UIManager.hpp"
#include "PX2Project.hpp"
#include "PX2Actor.hpp"
using namespace PX2;
using namespace PX2Editor;

//----------------------------------------------------------------------------
EditSystem::EditSystem ()
	:
mEditMode(EM_SELECT),
mSelectEditEnable(false),
mCM(0),
mTerrainEdit(0),
mEditMap(0),
mCurveEdit(0),
mSelection(0),
mIsShiftDown(false)
{
}
//----------------------------------------------------------------------------
EditSystem::~EditSystem ()
{
}
//----------------------------------------------------------------------------
bool EditSystem::Initlize ()
{
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

	UIManager *uiMan = new0 UIManager();
	PX2_UNUSED(uiMan);
	EventWorld::GetSingleton().ComeIn(uiMan);

	mEditMap = new0 EditMap();
	mCM = new0 EditCommandManager();
	mTerrainEdit = new0 TerrainEdit();
	mSelection = new0 ObjectSelection();
	mCurveEdit = new0 CurveEdit();

	mHelpScene = new0 Node();
	mHelpScene->AttachChild(mTerrainEdit->GetBrush()->GetRenderable());

	StandardMesh stdMesh(VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT4, 0));
	mXYPlane = stdMesh.Rectangle(2, 2, 10000.0f, 10000.0f);
	mXYPlane->Update();

	mXZPlane = stdMesh.Rectangle(2, 2, 10000.0f, 10000.0f);
	mXZPlane->WorldTransform.SetRotate(Matrix3f().MakeEulerXYZ(Mathf::HALF_PI,
		0.0f, 0.0f));
	mXZPlane->WorldTransformIsCurrent = true;
	mXZPlane->Update();

	mYZPlane = stdMesh.Rectangle(2, 2, 10000.0f, 10000.0f);
	mYZPlane->WorldTransform.SetRotate(Matrix3f().MakeEulerXYZ(0.0f,
		Mathf::HALF_PI, 0.0f));
	mYZPlane->WorldTransformIsCurrent = true;
	mYZPlane->Update();

	return true;
}
//----------------------------------------------------------------------------
bool EditSystem::Terminate ()
{
	mHelpScene = 0;

	if (mCurveEdit)
	{
		delete0(mCurveEdit);
		mCurveEdit = 0;
	}

	if (mSelection)
	{
		delete0(mSelection);
		mSelection = 0;
	}

	if (mTerrainEdit)
	{
		delete0(mTerrainEdit);
		mTerrainEdit = 0;
	}

	if (mCM)
	{
		delete0(mCM);
		mCM = 0;
	}

	if (mEditMap)
	{
		delete0(mEditMap);
		mEditMap = 0;
	}

	UIManager *uiMan = UIManager::GetSingletonPtr();
	if (uiMan)
	{
		EventWorld::GetSingleton().GoOut(uiMan);
		delete0(uiMan);
		UIManager::Set(0);
	}

	ResourceManager *resMan = ResourceManager::GetSingletonPtr();
	if (resMan)
	{
		delete0(resMan);
		ResourceManager::Set(0);
	}

	GraphicsRoot *graphicsRoot = GraphicsRoot::GetSingletonPtr();
	if (graphicsRoot)
	{
		graphicsRoot->Terminate();
		delete0(graphicsRoot);
		GraphicsRoot::Set(0);
	}

	EventWorld *entWorld = EventWorld::GetSingletonPtr();
	if (entWorld)
	{
		delete0(entWorld);
		EventWorld::Set(0);
	}

	return true;
}
//----------------------------------------------------------------------------
void EditSystem::Reset ()
{
	SetEditMode(EditSystem::EM_SELECT);

	if (mTerrainEdit)
	{
		mTerrainEdit->DisableEdit();
	}

	if (mSelection)
	{
		mSelection->Clear();
	}

	if (mCM)
	{
		mCM->Clear();
	}
}
//----------------------------------------------------------------------------
void EditSystem::Update (double elapsedSeconds)
{
	if (EventWorld::GetSingletonPtr())
		EventWorld::GetSingleton().Update((float)elapsedSeconds);

	double appTime = GetTimeInSeconds();

	UIView *view = UIManager::GetSingleton().GetDefaultView();
	if (view)
	{
		view->Update(appTime, elapsedSeconds);
	}

	if (mHelpScene)
		mHelpScene->Update(appTime, false);

	Scene *scene = 0;
	if (!Project::GetSingletonPtr())
		return;

	scene = Project::GetSingleton().GetScene();
	if (scene)
	{
		scene->Update(appTime, elapsedSeconds);
	}
}
//----------------------------------------------------------------------------
bool EditSystem::DeleteSelection ()
{
	bool deleted = false;

	int numObjs = GetSelection()->GetNumObjects();
	for (int i=0; i<numObjs; i++)
	{
		Object *obj = GetSelection()->GetObjectAt(i);
		Actor *actor = DynamicCast<Actor>(obj);
		if (actor)
		{
			GetEditMap()->RemoveActor(actor);
			deleted = true;
		}
		else if (GetEditMap()->RemoveUI(obj))
		{
			deleted = true;
		}
		else if (GetEditMap()->RemoveCtrl(obj))
		{
			deleted = true;
		}
	}

	if (deleted)
	{
		GetSelection()->Clear();
	}

	return deleted;
}
//----------------------------------------------------------------------------
void EditSystem::EnableSelectEdit (bool enable)
{
	if (false == enable)
	{
		mSelectEditEnable = enable;
		SetEditMode(EM_SELECT);
	}
	else
	{
		int num = GetSelection()->GetNumObjects();
		if (1 == num)
		{
			Object *obj = GetSelection()->GetObjectAt(0);
			TerrainActor *terActor = DynamicCast<TerrainActor>(obj);
			if (terActor)
			{
				SetEditMode(EM_TERRAIN);
			}

			mSelectEditEnable = enable;
		}
	}
}
//----------------------------------------------------------------------------
void EditSystem::SetEditMode (EditSystem::EditMode mode)
{
	mEditMode = mode;

	if (mode == EM_TERRAIN)
	{
		GetTerrainEdit()->EnableEdit();
	}
	else
	{
		GetTerrainEdit()->DisableEdit();
	}

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(EditorEventSpace::SetEditMode);
	event->SetData<EditSystem::EditMode>(mEditMode);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	mHelpScene->Update();
}
//----------------------------------------------------------------------------
void EditSystem::SetPreViewObject (PX2::Object *obj)
{
	mPreViewObject = obj;

	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::SetPreView);
	ent->SetData<PX2::Object*>(obj);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------