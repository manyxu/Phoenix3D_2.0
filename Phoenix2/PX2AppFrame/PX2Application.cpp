/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Application.cpp
*
*/

#include "PX2Application.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Application::Application ()
:
mRoot(0)
{
}
//----------------------------------------------------------------------------
Application::~Application ()
{
}
//----------------------------------------------------------------------------
bool Application::Initlize ()
{
#ifdef PX2_USE_MEMORY
	Memory::Initialize();
#endif

	mRoot = new0 GraphicsRoot();
	if (mRoot)
		mRoot->Initlize();

	return true;
}
//----------------------------------------------------------------------------
bool Application::Ternamate ()
{
	if (mRoot)
		mRoot->Terminate();

	delete0(mRoot);

#ifdef PX2_USE_MEMORY
	Memory::Terminate("MemoryReport.txt");
#endif

	return true;
}
//----------------------------------------------------------------------------
void Application::Run ()
{
}
//----------------------------------------------------------------------------