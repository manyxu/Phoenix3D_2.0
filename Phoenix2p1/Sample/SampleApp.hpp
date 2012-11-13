/*
*
* Filename	:	SampleApp.hpp
*
*/

#ifndef SAMPLEAPP_H
#define SAMPLEAPP_H

#include "PX2Application.hpp"
using namespace PX2;

class SampleApp : public Application
{
public:
	PX2_DECLARE_APPLICATION(SampleApp);
	
	SampleApp ();
	virtual ~SampleApp ();

	virtual bool OnInitlize ();
	virtual bool OnTernamate ();

	virtual void OnIdle ();
	virtual bool OnResume();
	virtual bool OnPause();

protected:
	void CreateScene ();

	Float4 mTextColor;
	NodePtr mScene;
	Culler mCuller;
};

PX2_REGISTER_APPLICATION(SampleApp)

#endif