/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Condition.hpp
*
*/

#ifndef PX2CONDITION_HPP
#define PX2CONDITION_HPP

#include "PX2CorePre.hpp"
#include "PX2ConditionType.hpp"

namespace PX2
{
	void PX2CreateCondition (ConditionType &cond);
	void PX2CloseCondition (ConditionType &cond);
	void PX2PostCondition (ConditionType &cond);
	void PX2WaitCondition (ConditionType &cond);
	void PX2Sleep (float seconds);
}

#endif