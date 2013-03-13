/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TimerTask.hpp
*
*/

#ifndef PX2TIMERTASK_HPP
#define PX2TIMERTASK_HPP

#include "PX2CorePre.hpp"
#include "PX2Timestamp.hpp"
#include "PX2SmartPointer.hpp"
#include "PX2Runnable.hpp"

namespace PX2
{

	class TimerTask : public Runnable
	{
	public:
		TimerTask();
		virtual ~TimerTask();

		void Cancel();
		bool IsCancelled() const;

		Timestamp GetLastExecution() const;

	private:
		TimerTask (const TimerTask&);
		TimerTask& operator = (const TimerTask&);

		Timestamp mLastExecution;
		bool mIsCancelled;
	};

	typedef Pointer0<TimerTask> TimerTaskPtr;

#include "PX2TimerTask.inl"

}

#endif