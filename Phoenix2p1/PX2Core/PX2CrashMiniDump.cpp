/*
*
* ÎÄ¼þÃû³Æ	£º	PX2CrashMiniDump.cpp
*
*/

#include "PX2CrashMiniDump.hpp"
#include "PX2Log.hpp"

#if defined(_WIN32) || defined(WIN32)
#include <shlwapi.h>
#include <Dbghelp.h>
#endif

using namespace PX2;

std::string CrashMiniDump::mAppName;
//----------------------------------------------------------------------------
CrashMiniDump::CrashMiniDump ()
{
}
//----------------------------------------------------------------------------
CrashMiniDump::~CrashMiniDump ()
{
}
//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
LONG WINAPI CrashMiniDump::MyExceptionFilter (struct _EXCEPTION_POINTERS *exceptPtrs)
{
	if(0 == exceptPtrs)
	{
		__try
		{
			RaiseException(EXCEPTION_BREAKPOINT, 0, 0, 0);
		}
		__except(MyExceptionFilter(GetExceptionInformation()), EXCEPTION_CONTINUE_EXECUTION)
		{

		}
	}

	// Create the date/time string
	time_t curtime = time(NULL);
	tm pTime;
	localtime_s(&pTime, &curtime);
	char filename[MAX_PATH+1];
	HANDLE hDumpFile = INVALID_HANDLE_VALUE;

	// Create the directory first
	if(!PathFileExists("CrashDumps"))
		CreateDirectory("CrashDumps", NULL);

	// Writing Simple Dump
	sprintf_s(filename, "CrashDumps\\%s-%02d%02d%02d_%02d%02d%02d_%u_s.dmp",
		mAppName.c_str(), pTime.tm_year+1900, pTime.tm_mon+1, pTime.tm_mday,
		pTime.tm_hour, pTime.tm_min, pTime.tm_sec, GetCurrentThreadId());

	hDumpFile = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, 0);

	if (hDumpFile == INVALID_HANDLE_VALUE)
	{
		PX2_LOG_ERROR("Could Not Create Dump File");
	}
	else
	{
		MINIDUMP_EXCEPTION_INFORMATION info;
		info.ClientPointers = FALSE;
		info.ExceptionPointers = exceptPtrs;
		info.ThreadId = GetCurrentThreadId();

		PX2_LOG_ERROR("Writing Simple Dump...");
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
			hDumpFile, MiniDumpNormal, &info, 0, 0);
		CloseHandle(hDumpFile);
		PX2_LOG_ERROR("Simple Dump Finished: %s", filename);
	}

	// Writing Full Dump
	sprintf_s(filename, "CrashDumps\\%s-%02d%02d%02d_%02d%02d%02d_%u_f.dmp",
		mAppName.c_str(), pTime.tm_year+1900, pTime.tm_mon+1, pTime.tm_mday,
		pTime.tm_hour, pTime.tm_min, pTime.tm_sec, GetCurrentThreadId());

	hDumpFile = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, 0);

	if(hDumpFile == INVALID_HANDLE_VALUE)
	{
		PX2_LOG_ERROR("Could Not Create Dump File");
	}
	else
	{
		MINIDUMP_EXCEPTION_INFORMATION info;
		info.ClientPointers = FALSE;
		info.ExceptionPointers = exceptPtrs;
		info.ThreadId = GetCurrentThreadId();

		PX2_LOG_ERROR("Writing Full Dump...");
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
			hDumpFile, MiniDumpWithFullMemory, &info, 0, 0);
		CloseHandle(hDumpFile);
		PX2_LOG_ERROR("Full Dump Finished: %s", filename);
	}

	return EXCEPTION_CONTINUE_SEARCH;
}
#endif
//----------------------------------------------------------------------------
void CrashMiniDump::Set (const char *appName)
{
	mAppName = appName;

#if defined(_WIN32) || defined(WIN32)
	SetUnhandledExceptionFilter(MyExceptionFilter);
#endif
}
//----------------------------------------------------------------------------