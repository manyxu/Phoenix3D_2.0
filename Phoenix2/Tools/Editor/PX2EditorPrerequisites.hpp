/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EditorPrerequisites.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2EDITORPREREQUISITES_HPP
#define PX2EDITORPREREQUISITES_HPP

// PX2
#include "PX2Core.hpp"
#include "PX2Mathematics.hpp"
#include "PX2Graphics.hpp"
#include "PX2Renderers.hpp"
#include "PX2Unity.hpp"
#include "PX2Game.hpp"
#include "PX2EditorLib.hpp"

#pragma warning(push) 
#pragma warning(disable : 4267)
#pragma warning(disable : 4482)
#pragma warning(disable : 4244)
#pragma warning(disable : 4189)
#pragma warning(disable : 4312)

// wx
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/xrc/xmlres.h>
#include <wx/filesys.h>
#include <wx/fs_arc.h>
#include <wx/imaglist.h>
#include <wx/aui/aui.h>
#include <wx/treectrl.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/propgrid/propdev.h>
#include <wx/propgrid/manager.h>
#include <wx/numdlg.h>
#include <wx/dirctrl.h>
#include <wx/dir.h>
#include <wx/config.h>
#include <wx/fileconf.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/textctrl.h>
#include <wx/clrpicker.h>
#include "foldpanelbar.h"

#pragma warning(pop)

#endif