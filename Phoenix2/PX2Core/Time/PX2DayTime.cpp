/*
*
* ÎÄ¼þÃû³Æ	£º	PX2DayTime.cpp
*
*/

#include "PX2DayTime.hpp"
using namespace PX2;

DayTime::DayTime ()
:
Year(0),
Month(0),
Day(0),
Hour(0),
Minute(0),
Second(0),
Minsecond(0)
{
}
//----------------------------------------------------------------------------
DayTime::DayTime (unsigned int year, unsigned int month, unsigned int day, 
				  unsigned int hour, unsigned int minute, unsigned int second,
				  unsigned int minsecond)
		 :
Year(year),
Month(month),
Day(day),
Hour(hour),
Minute(minute),
Second(second),
Minsecond(minsecond)
{
}
//----------------------------------------------------------------------------

#if defined(WIN32)
//----------------------------------------------------------------------------
#include <windows.h>
//----------------------------------------------------------------------------
DayTime GetDateTime (bool isUtc)
{
	SYSTEMTIME systime;

	if (isUtc)
		GetSystemTime(&systime);
	else
		GetLocalTime(&systime);

	return DayTime(systime.wYear, systime.wMonth, systime.wDay, systime.wHour,
		systime.wMinute, systime.wSecond, systime.wMilliseconds);
}
//----------------------------------------------------------------------------
#elif defined(__LINUX__) || defined(__APPLE__)
//----------------------------------------------------------------------------
DayTime GetDateTime (bool isUtc)
{
	struct timeval tp;
	time_t timep;
	struct tm *p = 0;
	time(&timep);

	if (isUtc)
		p = gmtime(&timep);
	else
		p = localtime(&timep);

	gettimeofday(&tp, NULL);

	if (!p)
		return DayTime();

	return DayTime(1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour,
		p->tm_min, p->tm_sec, (unsigned int)(tp.tv_usec/1000.0f));
}
//----------------------------------------------------------------------------
#else
#error Other platforms not yet implemented.
#endif
//----------------------------------------------------------------------------
