/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2AwesomiumPrerequisites.hpp
*
* 版本		:	1.0 (2011/03/11)
*
* 作者		：	more
*
*/

#ifndef PX2AWESOMIUMPREREQUISITES_HPP
#define PX2AWESOMIUMPREREQUISITES_HPP

#include "PX2Core.hpp"
#include "PX2Graphics.hpp"

// Awesomium
#pragma warning(push) 
#pragma warning(disable : 4100)
#include "Awesomium\WebCore.h"
#pragma warning(pop)

// Begin Microsoft Windows DLL
#if defined(PX2_AWESOMIUM_DLL_EXPORT)
    #define PX2_AWESOMIUM_ENTRY __declspec(dllexport)
#elif defined(PX2_AWESOMIUM_DLL_IMPORT)
    #define PX2_AWESOMIUM_ENTRY __declspec(dllimport)
#else
    #define PX2_AWESOMIUM_ENTRY
#endif
// End Microsoft Windows DLL

#endif