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

	virtual void OnIdle ();
	virtual bool OnResume();
	virtual bool OnPause();

protected:
	void CreateScene ();

	Float4 mTextColor;
	ScenePtr mScene;
	NodePtr mSceneGraph;
	Culler mCuller;
	WirePropertyPtr mWireProperty;
	CullPropertyPtr mCullProperty;
	bool mInited;
};

PX2_REGISTER_APPLICATION(GamePlayApp)

#endif