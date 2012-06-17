/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	SampleApp.hpp
*
* 版本		:	1.0 (2011/02/02)
*
* 作者		：	more
*
*/

#ifndef SAMPLEAPP_HPP
#define SAMPLEAPP_HPP

#include "PX2Win32Application.hpp"
using namespace PX2;

class AppEventHandler;

class SampleApp : public Win32Application, public EventHandler
{
public:
	SampleApp ();
	virtual ~SampleApp ();

	virtual bool OnInitlize ();
	virtual bool OnTernamate ();

	virtual void OnIdle ();

	void Draw ();

	// Event
	virtual void DoEnter ();
	virtual void DoExecute (Event *event);
	virtual void DoLeave ();

protected:
	void CreateScene ();

	NodePtr mScene;
	NodePtr mTrnNode;
	WirePropertyPtr mWireProperty;
	Culler mCuller;
	Float4 mTextColor;
};

#endif