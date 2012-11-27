/*
*
* ÎÄ¼þÃû³Æ	£º	PX2LogFileHandler.cpp
*
*/

#include "PX2LogOutputWindowHandler.hpp"
#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#elif defined __ANDROID__
#include <android/log.h>
#endif
using namespace PX2;

//----------------------------------------------------------------------------
OutputWindowHandler::OutputWindowHandler (unsigned int levels)
	:
LogHandler(levels)
{
}
//----------------------------------------------------------------------------
OutputWindowHandler::~OutputWindowHandler ()
{
}
//----------------------------------------------------------------------------
bool OutputWindowHandler::Handle (const char *filename, int line, 
	unsigned int level,	const char *str)
{
	PX2_UNUSED(filename);
	PX2_UNUSED(line);
	PX2_UNUSED(level);

#if defined(_WIN32) || defined(WIN32)
	OutputDebugString(str);
#elif defined __ANDROID__
	__android_log_print(ANDROID_LOG_INFO, "phoenix3d.px2",  str);
#endif

	return true;
}
//----------------------------------------------------------------------------