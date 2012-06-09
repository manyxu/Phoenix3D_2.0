/*
*
* ÎÄ¼şÃû³Æ	£º	PX2Help.cpp
*
*/

#include "PX2Help.hpp"
using namespace PX2;
using namespace std;

std::string Help::IntToString (int i)
{
	static char c[10];
	string str;
	sprintf(c, "%d", i);
	str = c;
	return str;
}
//----------------------------------------------------------------------------