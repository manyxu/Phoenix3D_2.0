/*
*
* 文件名称	：	PX2Thread.cpp
*
*/

#include "PX2Thread.hpp"
#include "PX2Assert.hpp"
using namespace PX2;

#if defined(WIN32)
//----------------------------------------------------------------------------
#include <windows.h>
//----------------------------------------------------------------------------
Thread::Thread (void* function, void* userData, unsigned int processorNumber,
				unsigned int stackSize)
				:
mFunction(function),
mUserData(userData),
mProcessorNumber(processorNumber),
mStackSize(stackSize)
{
	mThread = CreateThread(NULL, (SIZE_T)stackSize,
		(LPTHREAD_START_ROUTINE)function, (LPVOID)userData, CREATE_SUSPENDED,
		(LPDWORD)&mThreadID);
}
//----------------------------------------------------------------------------
Thread::~Thread ()
{
	// 析构函数中不对线程进行析构。
}
//----------------------------------------------------------------------------
void Thread::Resume ()
{
	DWORD result = ResumeThread((HANDLE)mThread);
	assertion(result != (DWORD)-1, "Failed to resume thread\n");
	PX2_UNUSED(result);
}
//----------------------------------------------------------------------------
void Thread::Suspend ()
{
	DWORD result = SuspendThread((HANDLE)mThread);
	assertion(result != (DWORD)-1, "Failed to suspend thread\n");
	PX2_UNUSED(result);
}
//----------------------------------------------------------------------------
#elif defined(__LINUX__) || defined(__APPLE__) || defined(__ANDROID__)
//----------------------------------------------------------------------------
Thread::Thread (void* function, void* userData, unsigned int processorNumber,
				unsigned int stackSize)
				:
mFunction(function),
mUserData(userData),
mProcessorNumber(processorNumber),
mStackSize(stackSize)
{
	pthread_create(&mThread, 0, function, userData);
}
//----------------------------------------------------------------------------
Thread::~Thread ()
{
	// TODO. 
}
//----------------------------------------------------------------------------
void Thread::Resume ()
{
}
//----------------------------------------------------------------------------
void Thread::Suspend ()
{
	// TODO.
}
//----------------------------------------------------------------------------
#else
#error Other platforms not yet implemented.
#endif
//----------------------------------------------------------------------------
