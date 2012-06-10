/*
*
* ÎÄ¼þÃû³Æ	£º	Main.cpp
*
*/

#include "SampleApp.hpp"

static SampleApp *gsTdApp = NULL;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	gsTdApp = new SampleApp();

	gsTdApp->Run();

	delete gsTdApp;

	return 0;
}