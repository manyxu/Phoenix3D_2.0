/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Condition.cpp
*
*/

#include "PX2Condition.hpp"
#include "PX2Assert.hpp"
using namespace PX2;

#if defined(WIN32)
//----------------------------------------------------------------------------
#include <windows.h>
//----------------------------------------------------------------------------
void PX2CreateCondition (ConditionType &cond)
{
	cond = ::CreateSemaphore(0, 0, 99999, 0);
}
//----------------------------------------------------------------------------
void PX2CloseCondition (ConditionType &cond)
{
	::CloseHandle(cond);
}
//----------------------------------------------------------------------------
void PX2PostCondition (ConditionType &cond)
{
	bool b = (::ReleaseSemaphore(cond, 1, 0)==1);
	assertion(b, "ReleaseSemaphore failed.");
}
//----------------------------------------------------------------------------
void PX2WaitCondition (ConditionType &cond)
{
	::WaitForSingleObject(cond, INFINITE);
}
//----------------------------------------------------------------------------
void PX2Sleep (float seconds)
{
	::Sleep((DWORD)(seconds*1000.0));
}
//----------------------------------------------------------------------------
#elif defined(__LINUX__) || defined(__APPLE__) || defined(__ANDROID__)
#include <semaphore.h>
//----------------------------------------------------------------------------
void PX2CreateCondition (ConditionType &cond, int maxNum)
{
	sem_init(&cond, 0, 0);
}
//----------------------------------------------------------------------------
void PX2CloseCondition (ConditionType &cond)
{
	sem_destroy(&cond);
}
//----------------------------------------------------------------------------
void PX2PostCondition (ConditionType &cond)
{
	sem_post(&cond);
}
//----------------------------------------------------------------------------
void PX2WaitCondition (ConditionType &cond)
{
	sem_wait(&cond);
}
//----------------------------------------------------------------------------
void PX2Sleep (float seconds)
{
	sleep(seconds);
}
//----------------------------------------------------------------------------
#else
#error Other platforms not yet implemented.
#endif