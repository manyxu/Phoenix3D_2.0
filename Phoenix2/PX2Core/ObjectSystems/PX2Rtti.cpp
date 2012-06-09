/*
*
* ÎÄ¼şÃû³Æ	£º	PX2Rtti.cpp
*
*/

#include "PX2Rtti.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Rtti::Rtti (const char* name, const Rtti* baseType)
{
    mName = name;
    mBaseType = baseType;
}
//----------------------------------------------------------------------------
Rtti::~Rtti ()
{
}
//----------------------------------------------------------------------------
bool Rtti::IsDerived (const Rtti& type) const
{
    const Rtti* search = this;
    while (search)
    {
        if (search == &type)
        {
            return true;
        }
        search = search->mBaseType;
    }
    return false;
}
//----------------------------------------------------------------------------
