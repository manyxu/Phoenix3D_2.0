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

	void CreateCondition (ConditionType &cond);
	void CloseCondition (ConditionType &cond);
	void PostCondition (ConditionType &cond);
	void WaitCondition (ConditionType &cond);

}

#endif