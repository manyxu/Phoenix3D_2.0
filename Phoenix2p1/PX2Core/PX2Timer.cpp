/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Timer.cpp
*
*/

#include "PX2Timer.hpp"
#include "PX2Eventt.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
// TimerNotification
//----------------------------------------------------------------------------
class TimerNotification : public Notification
{
public:
	TimerNotification (TimedNotificationQueue& queue)
		:
	  mQueue(queue)
	  {
	  }

	  ~TimerNotification()
	  {
	  }

	  virtual bool Execute() = 0;

	  TimedNotificationQueue& GetQueue()
	  {
		  return mQueue;
	  }

private:
	TimedNotificationQueue &mQueue;
};
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// StopNotification
//----------------------------------------------------------------------------
class StopNotification : public TimerNotification
{
public:
	StopNotification (TimedNotificationQueue &queue):
	  TimerNotification(queue)
	  {
	  }

	  ~StopNotification()
	  {
	  }

	  bool Execute()
	  {
		  GetQueue().Clear();
		  return false;
	  }
};
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// CancelNotification
//----------------------------------------------------------------------------
class CancelNotification : public TimerNotification
{
public:
	CancelNotification(TimedNotificationQueue &queue):
	  TimerNotification(queue)
	  {
	  }

	  ~CancelNotification()
	  {
	  }

	  bool Execute()
	  {
		  GetQueue().Clear();
		  mFinished.Set();
		  return true;
	  }

	  void Wait()
	  {
		  mFinished.Wait();
	  }

private:
	Eventt mFinished;
};
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// TaskNotification
//----------------------------------------------------------------------------
class TaskNotification : public TimerNotification
{
public:
	TaskNotification (TimedNotificationQueue& queue, TimerTaskPtr task)
		:
	  TimerNotification(queue),
		  mTask(task)
	  {
	  }

	  ~TaskNotification()
	  {
	  }

	  TimerTask *GetTask()
	  {
		  return mTask;	
	  }

	  bool Execute()
	  {
		  if (!mTask->IsCancelled())
		  {
			  mTask->GetLastExecution().Update();
			  mTask->Run();
		  }
		  return true;
	  }

private:
	TimerTaskPtr mTask;
};
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// PeriodicTaskNotification
//----------------------------------------------------------------------------
class PeriodicTaskNotification : public TaskNotification
{
public:
	PeriodicTaskNotification (TimedNotificationQueue &queue, TimerTask *task,
		long interval)
		:
	  TaskNotification(queue, task),
		  mInterval(interval)
	  {
	  }

	  ~PeriodicTaskNotification()
	  {
	  }

	  bool Execute()
	  {	
		  TaskNotification::Execute();

		  if (!GetTask()->IsCancelled())
		  {
			  Timestamp now;
			  Timestamp nextExecution;
			  nextExecution += static_cast<Timestamp::TimeDiff>(mInterval)*1000;
			  if (nextExecution < now)
				  nextExecution = now;
			  GetQueue().EnqueueNotification(this, nextExecution);
		  }
		  return true;		
	  }

private:
	long mInterval;
};
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// FixedRateTaskNotification
//----------------------------------------------------------------------------
class FixedRateTaskNotification: public TaskNotification
{
public:
	FixedRateTaskNotification(TimedNotificationQueue &queue, TimerTask *task,
		long interval, Timestamp time)
		:
	  TaskNotification(queue, task),
		  mInterval(interval),
		  mNextExecution(time)
	  {
	  }

	  ~FixedRateTaskNotification()
	  {
	  }

	  bool Execute()
	  {	
		  TaskNotification::Execute();

		  if (!GetTask()->IsCancelled())
		  {
			  Timestamp now;
			  mNextExecution += static_cast<Timestamp::TimeDiff>(mInterval)*1000;
			  if (mNextExecution < now)
				  mNextExecution = now;
			  GetQueue().EnqueueNotification(this, mNextExecution);
		  }
		  return true;			
	  }

private:
	long mInterval;
	Timestamp mNextExecution;
};
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Timer
//----------------------------------------------------------------------------
Timer::Timer ()
{
	mThread = new0 Thread();
}
//----------------------------------------------------------------------------
Timer::~Timer ()
{
	mQueue.EnqueueNotification(new0 StopNotification(mQueue), 0);

	mThread->Join();
}
//----------------------------------------------------------------------------
void Timer::Cancel (bool wait)
{
	Pointer0<CancelNotification> ptr = new0 CancelNotification(mQueue);
	mQueue.EnqueueNotification(ptr, 0);

	if (wait)
	{
		ptr->Wait();
	}
}
//----------------------------------------------------------------------------
void Timer::Schedule (TimerTask *task, Timestamp time)
{
	mQueue.EnqueueNotification(new0 TaskNotification(mQueue, task), time);
}
//----------------------------------------------------------------------------
void Timer::Schedule (TimerTask *task, long delay, long interval)
{
	Timestamp time;
	time += static_cast<Timestamp::TimeDiff>(delay)*1000;
	Schedule(task, time, interval);
}
//----------------------------------------------------------------------------
void Timer::Schedule (TimerTask *task, Timestamp time, long interval)
{
	mQueue.EnqueueNotification(new0 PeriodicTaskNotification(mQueue, task, 
		interval), time);
}
//----------------------------------------------------------------------------
void Timer::ScheduleAtFixedRate (TimerTask *task, long delay, long interval)
{
	Timestamp time;
	time += static_cast<Timestamp::TimeDiff>(delay)*1000;
	ScheduleAtFixedRate(task, time, interval);
}
//----------------------------------------------------------------------------
void Timer::ScheduleAtFixedRate (TimerTask *task, Timestamp time, long interval)
{
	mQueue.EnqueueNotification(new0 FixedRateTaskNotification(mQueue, task, 
		interval, time), time);
}
//----------------------------------------------------------------------------
void Timer::Run ()
{
	bool cont = true;
	while (cont)
	{
		Notification *nf = mQueue.WaitDequeueNotification();
		TimerNotification *tnf = (TimerNotification*)nf;
		cont = tnf->Execute();
	}
}
//----------------------------------------------------------------------------