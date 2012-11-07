/*
*
* Filename	:	SampleApp.hpp
*
*/

#ifndef SAMPLEAPP_H
#define SAMPLEAPP_H

#include "PX2WindowApplication.hpp"
using namespace PX2;

class SampleApp : public WindowApplication
{
public:
	PX2_DECLARE_WINDOW_APPLICATION(SampleApp);
	
	SampleApp ();
	virtual ~SampleApp ();

	virtual bool OnInitlize ();
	virtual bool OnTernamate ();

	virtual void OnIdle ();

protected:
	void CreateScene ();

	Float4 mTextColor;
	NodePtr mScene;
	Culler mCuller;
};

PX2_REGISTER_WINDOW_APPLICATION(SampleApp)

#endif