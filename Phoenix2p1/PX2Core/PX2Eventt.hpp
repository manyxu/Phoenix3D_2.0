/*
*
* 文件名称	：	PX2Eventt.hpp
*
*/

#ifndef PX2EVENTT_HPP
#define PX2EVENTT_HPP

#include "PX2CorePre.hpp"

#if (defined(_WIN32) || defined(WIN32))
typedef void* EventtType;
#elif defined(__LINUX__) || defined(__APPLE__) || defined(__ANDROID__)
#include <pthread.h>
#endif

namespace PX2
{

	/// 信号
	/**
	* 信号是一个线程同步结构，通常一个线程激活这个信号，其他线程等待
	* 这个信号被激活
	*/
	class Eventt
	{
	public:
		/// 创建一个事件，如果autoReset为true，在Wait()成功后，事件自动Reset，
		/// 变为未激活状态。
		Eventt (bool autoReset=true);
		~Eventt ();

		/// 激活事件，如果autoReset为true，只有一个等待的线程被唤起运行；如果为
		/// false，所有等待的显存都被唤起运行。
		void Set ();

		/// 等待事件被激活
		void Wait ();

		/// 在一段时间内等待事件被激活，如果激活了返回true，否则返回false
		bool Wait (long milliseconds);

		/// 重置事件到未激活状态
		void Reset ();

	protected:
		bool mIsAutoReset;

#if (defined(_WIN32) || defined(WIN32))
		EventtType mEvent;
#elif defined(__LINUX__) || defined(__APPLE__) || defined(__ANDROID__)
		volatile bool mState;
		pthread_mutex_t mMutex;
		pthread_cond_t mCond;
#endif

	private:
		Eventt (const Eventt&);
		Eventt& operator = (const Eventt&);
	};

}

#endif