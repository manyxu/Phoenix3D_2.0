/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ConditionType.hpp
*
*/

#ifndef PX2CONDITIONTYPE_HPP
#define PX2CONDITIONTYPE_HPP

#include "PX2CorePre.hpp"

#if defined(WIN32)
namespace PX2
{
	typedef void *ConditionType;
}
#elif defined(__LINUX__) || defined(__APPLE__) || defined(__ANDROID__)
#include <semaphore.h>
namespace PX2
{
	typedef sem_t ConditionType;
}
#else
#error Other platforms not yet implemented.
#endif

#endif
