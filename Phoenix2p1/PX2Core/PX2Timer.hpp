/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Timer.hpp
*
*/

#ifndef PX2TIMER_HPP
#define PX2TIMER_HPP

#include "PX2CorePre.hpp"
#include "PX2Runnable.hpp"
#include "PX2TimerTask.hpp"
#include "PX2TimedNotificationQueue.hpp"
#include "PX2Thread.hpp"

namespace PX2
{

	class Timer : public Runnable
	{
	public:
		Timer ();
		~Timer ();

		void Cancel (bool wait=false);

		void Schedule (TimerTask *task, Timestamp time);
		void Schedule (TimerTask *task, long delay, long interval);
		void Schedule (TimerTask *task, Timestamp time, long interval);
		void ScheduleAtFixedRate (TimerTask *task, long delay, long interval);
		void ScheduleAtFixedRate (TimerTask *task, Timestamp time, long interval);

	protected:
		void Run ();

	private:
		Timer (const Timer &);
		Timer& operator= (const Timer&);

		TimedNotificationQueue mQueue;
		Thread *mThread;
	};

}

#endif