/*
*
* ÎÄ¼þÃû³Æ	£º	PX2CrashMiniDump.hpp
*
*/

#ifndef PX2CRASHMINIDUMP_HPP
#define PX2CRASHMINIDUMP_HPP

#include "PX2CorePre.hpp"
#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

namespace PX2
{

	class CrashMiniDump
	{
	public:
		CrashMiniDump ();
		~CrashMiniDump ();

		static void Set (const char *appName);

	private:
#if defined(_WIN32) || defined(WIN32)
		static LONG WINAPI MyExceptionFilter (struct _EXCEPTION_POINTERS *exceptPtrs);
#endif

		static std::string mAppName;
	};

}

#endif