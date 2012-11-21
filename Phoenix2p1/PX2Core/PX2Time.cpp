/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Time.cpp
*
*/

#include "PX2Time.hpp"

namespace PX2
{

#if defined(WIN32)
	#include <Windows.h>
#endif

#ifdef __APPLE__
#include <sys/time.h>
	static timeval gsInitial;
	static bool gsInitializedTime = false;
#else
#include <sys/timeb.h>
	static long gsInitialSec = 0;
	static long gsInitialUSec = 0;
	static bool gsInitializedTime = false;
#endif

	//----------------------------------------------------------------------------
	int64_t GetTimeInMicroseconds ()
	{
#ifdef __APPLE__
		if (!gsInitializedTime)
		{
			gsInitializedTime = true;
			gettimeofday(&gsInitial, 0);
		}

		struct timeval currentTime;
		gettimeofday(&currentTime, 0);

		struct timeval deltaTime;
		timersub(&currentTime, &gsInitial, &deltaTime);

		return 1000000*deltaTime.tv_sec + deltaTime.tv_usec;
#else
		struct timeb currentTime;

		if (!gsInitializedTime)
		{
			gsInitializedTime = true;
			ftime(&currentTime);
			gsInitialSec = (long)currentTime.time;
			gsInitialUSec = 1000*currentTime.millitm;
		}

		ftime(&currentTime);
		long currentSec = (long)currentTime.time;
		long currentUSec = 1000*currentTime.millitm;
		long deltaSec = currentSec - gsInitialSec;
		long deltaUSec = currentUSec - gsInitialUSec;
		if (deltaUSec < 0)
		{
			deltaUSec += 1000000;
			--deltaSec;
		}

		return 1000000*deltaSec + deltaUSec;
#endif
	}
	//----------------------------------------------------------------------------
	double GetTimeInSeconds ()
	{
		int64_t microseconds = GetTimeInMicroseconds();
		return 1e-06*microseconds;
	}
	//----------------------------------------------------------------------------
	void SleepInSeconds (float seconds)
	{
#if defined(WIN32)
		Sleep((DWORD)(seconds*1000.0));
#elif defined(__LINUX__) || defined(__APPLE__) || defined(__ANDROID__)
		sleep(seconds);
#else
#error Other platforms not yet implemented.
#endif
	}
	//----------------------------------------------------------------------------

}