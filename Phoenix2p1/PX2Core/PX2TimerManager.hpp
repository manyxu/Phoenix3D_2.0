/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TimerManager.hpp
*
*/

#ifndef PX2TIMERMANAGER_HPP
#define PX2TIMERMANAGER_HPP

#include "PX2CorePre.hpp"
#include "PX2Singleton.hpp"
#include "PX2Thread.hpp"

namespace PX2
{

	class TimerManager : public Singleton<TimerManager>
	{
	public:
		TimerManager ();
		~TimerManager ();

		void Update ();
	};

}

#endif