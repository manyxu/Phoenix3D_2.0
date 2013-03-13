/*
*
* Filename	:	GamePlayApp.hpp
*
*/

#ifndef GAMEPLAYAPP_H
#define GAMEPLAYAPP_H

#include "PX2Application.hpp"
using namespace PX2;

class GamePlayApp : public Application
{
public:
	PX2_DECLARE_APPLICATION(GamePlayApp);
	
	GamePlayApp ();
	virtual ~GamePlayApp ();

	virtual bool OnInitlize ();
	virtual bool OnTernamate ();

	virtual void WillEnterForeground ();
	virtual void DidEnterBackground ();

	virtual void OnIdle ();
	virtual bool OnResume();
	virtual bool OnPause();

	virtual void DoEnter ();
	virtual void DoExecute (Event *event);
	virtual void DoLeave ();

protected:
	void CreateProject ();
	void ZoomCamera (float zoom);
	void MoveCamera (const float &horz, const float &vert);
	void RolateCamera (const float &horz, const float &vert);
	void SimplifyTerrain ();

	Float4 mTextColor;
	Culler mCuller;
	WirePropertyPtr mWireProperty;
	CullPropertyPtr mCullProperty;
	DepthPropertyPtr mDepthProperty;
	bool mInited;
	Float2 mTouchPos;
};

PX2_REGISTER_APPLICATION(GamePlayApp)

#endif