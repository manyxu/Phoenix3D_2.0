/*
*
* ÎÄ¼þÃû³Æ	£º	PX2LogFileHandler.cpp
*
*/

#include "PX2LogFileHandler.hpp"
using namespace PX2;

FileLogHandler::FileLogHandler (unsigned int levels, const char *filename)
:
LogHandler(levels)
{
	mFile = fopen(filename, "wt");
}
//----------------------------------------------------------------------------
FileLogHandler::~FileLogHandler ()
{
	if (mFile)
		fclose(mFile);
}
//----------------------------------------------------------------------------
bool FileLogHandler::Handle (const char *filename, int line,
							 unsigned int level, const char *str)
{
	PX2_UNUSED(filename);
	PX2_UNUSED(line);
	PX2_UNUSED(level);

	if (mFile)
	{
		fprintf(mFile, "%s\n", str);
		fflush(mFile);
		
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------