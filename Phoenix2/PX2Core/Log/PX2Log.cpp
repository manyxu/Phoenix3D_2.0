/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Log.cpp
*
*/

#include "PX2LogFileHandler.hpp"
#include "PX2Log.hpp"
#include "PX2Assert.hpp"
#include "PX2Memory.hpp"

namespace PX2
{

static const char *sFilename;
static int sLine;
static unsigned int sLogLevel;
const int MAX_HANDLER = 16;
static LogHandler *sHandlers[MAX_HANDLER];
static int sNumHandlers = 0;

//----------------------------------------------------------------------------
LogHandler::LogHandler (unsigned int levels)
:
mLevelFlags(levels)
{
}
//----------------------------------------------------------------------------
LogHandler::~LogHandler ()
{
}
//----------------------------------------------------------------------------
unsigned int LogHandler::GetLevels ()
{
	return mLevelFlags;
}
//----------------------------------------------------------------------------
bool LogInitlize ()
{
	sFilename = 0;
	sLine = 0;
	sLogLevel = 0;
	sNumHandlers = 0;

	return true;
}
//----------------------------------------------------------------------------
void LogRelease ()
{
	for (int i=0; i<sNumHandlers; i++)
	{
		delete sHandlers[i];
	}
}
//----------------------------------------------------------------------------
int LogAddHandler (LogHandler *handler)
{
	if (!handler)
		return -1;

	if (sNumHandlers == MAX_HANDLER)
		return -1;

	for (int i=0; i<sNumHandlers; i++)
	{
		if (sHandlers[i] == handler)
			return i;
	}

	sHandlers[sNumHandlers++] = handler;
	
	return (sNumHandlers-1);
}
//----------------------------------------------------------------------------
int LogAddFileHandler (const char *filename, int line, unsigned int levels)
{
	PX2_UNUSED(line);

	FileLogHandler *handler = new FileLogHandler(levels, filename);

	return LogAddHandler(handler);
}
//----------------------------------------------------------------------------
void LogSetCurParam (const char *filename, int line, unsigned int level)
{
	sFilename = filename;
	sLine = line;
	sLogLevel = level;
}
//----------------------------------------------------------------------------
void LogMessage (const char *format, ...)
{
	assertion(*(unsigned int *)format != 0xcdcdcdcd, "");

	va_list argptr;
	char buffer[4096];

	va_start(argptr, format);
	vsprintf(buffer, format, argptr);
	va_end(argptr);

	for (int i=0; i<sNumHandlers; i++)
	{
		LogHandler *handler = sHandlers[i];
		if (sLogLevel&handler->GetLevels())
		{
			handler->Handle(sFilename, sLine, sLogLevel, buffer);
		}
	}
}
//----------------------------------------------------------------------------

}