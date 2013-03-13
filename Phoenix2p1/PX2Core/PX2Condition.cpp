/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Condition.cpp
*
*/

#include "PX2Condition.hpp"
#include "PX2Assert.hpp"

namespace PX2
{

#if (defined(_WIN32) || defined(WIN32)) && !defined(PX2_USE_PTHREAD)
//----------------------------------------------------------------------------
#include <windows.h>
//----------------------------------------------------------------------------
void CreateCondition (ConditionType &cond)
{
	cond = CreateSemaphore(0, 0, 99999, 0);
}
//----------------------------------------------------------------------------
void CloseCondition (ConditionType &cond)
{
	CloseHandle(cond);
}
//----------------------------------------------------------------------------
void PostCondition (ConditionType &cond)
{
	bool b = (ReleaseSemaphore(cond, 1, 0)==1);
	assertion(b, "ReleaseSemaphore failed.");
}
//----------------------------------------------------------------------------
void WaitCondition (ConditionType &cond)
{
	WaitForSingleObject(cond, INFINITE);
}
//----------------------------------------------------------------------------
#elif defined(__LINUX__) || defined(__APPLE__) || defined(__ANDROID__) || defined(PX2_USE_PTHREAD)
#include <semaphore.h>
//----------------------------------------------------------------------------
void CreateCondition (ConditionType &cond)
{
	sem_init(&cond, 0, 0);
}
//----------------------------------------------------------------------------
void CloseCondition (ConditionType &cond)
{
	sem_destroy(&cond);
}
//----------------------------------------------------------------------------
void PostCondition (ConditionType &cond)
{
	sem_post(&cond);
}
//----------------------------------------------------------------------------
void WaitCondition (ConditionType &cond)
{
	sem_wait(&cond);
}
//----------------------------------------------------------------------------
#endif

}