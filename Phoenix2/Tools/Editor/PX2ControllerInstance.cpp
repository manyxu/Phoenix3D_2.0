/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ControllerInstance.cpp
*
*/

#include "PX2ControllerInstance.hpp"
#include "PX2PaneController.hpp"
#include "PX2STRSController.hpp"
#include "PX2TerrainEditController.hpp"
#include "PX2EditSystem.hpp"
using namespace PX2Editor;
using namespace PX2;

ControllerInstance::ControllerInstance()
{
	mPaneController = 0;
}
//-----------------------------------------------------------------------------
ControllerInstance::~ControllerInstance()
{

}
//-----------------------------------------------------------------------------
void ControllerInstance::ResetSelection ()
{

}
//-----------------------------------------------------------------------------
void ControllerInstance::DoSelection (PX2::Renderer *renderer, 
									  const PX2::Vector2f &point,
									  SelectionMode mode)
{
	APoint origin;
	AVector direction;

	float x = renderer->GetWidth() * point.X();
	float y = renderer->GetHeight() * (1.0f - point.Y());

	renderer->GetPickRay((int)x, (int)y, origin, direction);

	Scene *scene = EditSystem::GetSingleton().GetEditMap()->GetScene();

	ActorPicker actorPicker;
	actorPicker.Execute(scene, origin, direction, 0.0f, Mathf::MAX_REAL);

	if (actorPicker.Records.size() > 0)
	{
		const ActorPickRecord &record = actorPicker.GetClosestToZero();
		mSelectPoint = origin + direction*record.T;

		if (mode == SM_REPLACE)
		{
			if (!ActorSelection::GetSingleton().IsActorIn(record.Intersected))
			{
				ActorSelection::GetSingleton().Clear();
				ActorSelection::GetSingleton().AddActor(record.Intersected);
			}
		}
		else if (mode == SM_ADD)
		{
			ActorSelection::GetSingleton().AddActor(record.Intersected);
		}
		else if (mode == SM_SUBTRACT)
		{
			ActorSelection::GetSingleton().RemoveActor(record.Intersected);
		}
	}
	else
	{
		if (ActorSelection::GetSingleton().GetActorQuantity() > 0)
		{
			if (mode == SM_REPLACE)
			{
				ActorSelection::GetSingleton().Clear();
			}
		}
	}
}
//-----------------------------------------------------------------------------
void ControllerInstance::DoSelection (PX2::Renderer *renderer, 
									  const PX2::Vector2f &topLeft,
									  const PX2::Vector2f &bottonRight, 
									  SelectionMode mode)
{
}
//-----------------------------------------------------------------------------
PX2::APoint ControllerInstance::CalculateSelectPoint (PX2::Renderer *renderer,
											   const PX2::Vector2f &point)
{
	APoint origin;
	AVector direction;

	float x = renderer->GetWidth() * point.X();
	float y = renderer->GetHeight() * (1.0f - point.Y());

	renderer->GetPickRay((int)x, (int)y, origin, direction);

	Scene *scene = EditSystem::GetSingleton().GetEditMap()->GetScene();

	ActorPicker actorPicker;
	actorPicker.Execute(scene, origin, direction, 0.0f, Mathf::MAX_REAL);

	mSelectPoint = PX2::APoint::ORIGIN;

	if (actorPicker.Records.size() > 0)
	{
		const ActorPickRecord &record = actorPicker.GetClosestToZero();

		mSelectPoint = origin + direction*record.T;
	}

	return mSelectPoint;
}
//-----------------------------------------------------------------------------
PX2::APoint ControllerInstance::GetSelectPoint ()
{
	return mSelectPoint;
}
//-----------------------------------------------------------------------------
void ControllerInstance::SetInteractionMode (InteractionMode im)
{
	if (im == mInteractionMode)
		return;

	switch (mInteractionMode)
	{
	case IM_SELECT:
		ExitSelectMode();
		break;
	case IM_TRANSLATE:
		ExitTranslateMode();
		break;
	case IM_ROLATE:
		ExitRolateMode();
		break;
	case IM_SCALE:
		ExitScaleMode();
		break;
	case IM_TERRAINHEIGHT:
		ExitTerrainHeightEditMode();
		break;
	case IM_TERRAINTEXTURE:
		ExitTerrainTextureEditMode();
		break;
	}

	mInteractionMode = im;

	switch (mInteractionMode)
	{
	case IM_SELECT:
		EnterSelectMode();
		break;
	case IM_TRANSLATE:
		EnterTranslateMode();
		break;
	case IM_ROLATE:
		EnterRolateMode();
		break;
	case IM_SCALE:
		EnterScaleMode();
		break;
	case IM_TERRAINHEIGHT:
		EnterTerrainHeightEditMode();
		break;
	case IM_TERRAINTEXTURE:
		EnterTerrainTextureEditMode();
		break;
	}
}
//-----------------------------------------------------------------------------
void ControllerInstance::Handle3DPaneLeftDown (RenderViewWindow *win, 
											   wxMouseEvent &e)
{
	mPaneController->HandleLeftDown(win, e);
}
//-----------------------------------------------------------------------------
void ControllerInstance::Handle3DPaneLeftUp (RenderViewWindow *win,
											 wxMouseEvent &e)
{
	mPaneController->HandleLeftUp(win, e);
}
//-----------------------------------------------------------------------------
void ControllerInstance::Handle3DPaneMiddleDown (RenderViewWindow *win,
												 wxMouseEvent &e)
{
	mPaneController->HandleMiddleDown(win, e);
}
//-----------------------------------------------------------------------------
void ControllerInstance::Handle3DPaneMiddleUp (RenderViewWindow *win, 
											   wxMouseEvent &e)
{
	mPaneController->HandleMiddleUp(win, e);
}
//-----------------------------------------------------------------------------
void ControllerInstance::Handler3DPaneMouseWheel (RenderViewWindow *win, 
												  wxMouseEvent &e)
{
	mPaneController->HandleMouseWheel(win, e);
}
//-----------------------------------------------------------------------------
void ControllerInstance::Handle3DPaneRightDown (RenderViewWindow *win,
												wxMouseEvent &e)
{
	mPaneController->HandleRightDown(win, e);
}
//-----------------------------------------------------------------------------
void ControllerInstance::Handle3DPaneRightUp (RenderViewWindow *win, 
											  wxMouseEvent &e)
{
	mPaneController->HandleRightUp(win, e);
}
//-----------------------------------------------------------------------------
void ControllerInstance::Handle3DPaneMotion (RenderViewWindow *win, 
											 wxMouseEvent &e)
{
	mPaneController->HandleMotion(win, e);
}
//-----------------------------------------------------------------------------
void ControllerInstance::Handle3DPaneKeyDown (RenderViewWindow *win, 
											  wxKeyEvent &e)
{
	mPaneController->HandleKeyDown(win, e);
}
//-----------------------------------------------------------------------------
void ControllerInstance::Handle3DPaneKeyUp (RenderViewWindow *win, 
											wxKeyEvent &e)
{
	mPaneController->HandleKeyUp(win, e);
}
//-----------------------------------------------------------------------------
void ControllerInstance::Handle3DPaneChar (RenderViewWindow *win,
										   wxKeyEvent &e)
{
	mPaneController->HandleChar(win, e);
}
//-----------------------------------------------------------------------------
void ControllerInstance::SwitchPaneController (PaneController *ctrl)
{
	if (mPaneController)
		delete mPaneController;

	mPaneController = ctrl;
}
//-----------------------------------------------------------------------------
void ControllerInstance::EnterSelectMode ()
{
	SwitchPaneController(new STRSController(this));
	
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_SELECT);
}
//-----------------------------------------------------------------------------
void ControllerInstance::ExitSelectMode ()
{

}
//-----------------------------------------------------------------------------
void ControllerInstance::EnterTranslateMode ()
{
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_TRANSLATE);

}
//-----------------------------------------------------------------------------
void ControllerInstance::ExitTranslateMode ()
{
}
//-----------------------------------------------------------------------------
void ControllerInstance::EnterRolateMode ()
{
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_ROLATE);
}
//-----------------------------------------------------------------------------
void ControllerInstance::ExitRolateMode ()
{
}
//-----------------------------------------------------------------------------
void ControllerInstance::EnterScaleMode ()
{
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_SCALE);
}
//-----------------------------------------------------------------------------
void ControllerInstance::ExitScaleMode ()
{

}
//-----------------------------------------------------------------------------
void ControllerInstance::EnterTerrainHeightEditMode ()
{
	SwitchPaneController(new TerrainEditController(this));
}
//-----------------------------------------------------------------------------
void ControllerInstance::ExitTerrainHeightEditMode ()
{
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_NONE);
}
//-----------------------------------------------------------------------------
void ControllerInstance::EnterTerrainTextureEditMode ()
{
	SwitchPaneController(new TerrainEditController(this));
}
//-----------------------------------------------------------------------------
void ControllerInstance::ExitTerrainTextureEditMode ()
{
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_NONE);
}
//-----------------------------------------------------------------------------