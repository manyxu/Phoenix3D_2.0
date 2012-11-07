/*
* Phoenix 3D 引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Names.hpp
*
* 版本		:	1.0 (2011/01/30)
*
* 作者		：	more
*
*/

#ifndef PX2NAMES_HPP
#define PX2NAMES_HPP

#include "PX2CorePre.hpp"

//----------------------------------------------------------------------------
#define PX2_DECLARE_NAMES \
public: \
    virtual Object* GetObjectByName (const std::string& name); \
    virtual void GetAllObjectsByName (const std::string& name, \
        std::vector<Object*>& objects)
//----------------------------------------------------------------------------
#define PX2_IMPLEMENT_DEFAULT_NAMES(baseclassname, classname) \
Object* classname::GetObjectByName (const std::string& name) \
{ \
    return baseclassname::GetObjectByName(name); \
} \
\
void classname::GetAllObjectsByName (const std::string& name, \
    std::vector<Object*>& objects) \
{ \
    baseclassname::GetAllObjectsByName(name, objects); \
}
//----------------------------------------------------------------------------
#define PX2_GET_OBJECT_BY_NAME(source, name, found) \
if (source) \
{ \
    found = source->GetObjectByName(name); \
    if (found) \
    { \
        return found; \
    } \
}
//----------------------------------------------------------------------------
#define PX2_GET_ALL_OBJECTS_BY_NAME(source, name, objects) \
if (source) \
{ \
    source->GetAllObjectsByName(name, objects); \
}
//----------------------------------------------------------------------------

#endif