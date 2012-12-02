/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Main.cpp
*
*/

#include "PX2ApplicationBase.hpp"
using namespace PX2;

#if defined(_WIN32) || defined(WIN32) || __APPLE__ || __LINUX__
//----------------------------------------------------------------------------
int main (int numArguments, char* arguments[])
{
	ApplicationBase::msAppInitlizeFun();

	int exitCode = ApplicationBase::msEntry(numArguments, arguments);

	ApplicationBase::msAppTernamateFun();

	return exitCode;
}
//----------------------------------------------------------------------------

#endif