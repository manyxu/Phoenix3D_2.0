/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Max8ClassDesc.cpp
*
*/

#include "resource.h"
#include "PX2Max9ClassDesc.hpp"
#include "PX2SceneExport.hpp"

Class_ID PX2Max8ClassDesc::ID(0x554dbc9c,0x8f17519);
PX2Max8ClassDesc PX2Max8ClassDesc::TheClassDesc;

HINSTANCE PX2Max8ClassDesc::msInstance = 0;
//----------------------------------------------------------------------------
PX2Max8ClassDesc::PX2Max8ClassDesc ()
{
}
//----------------------------------------------------------------------------
int PX2Max8ClassDesc::IsPublic () 
{ 
	return 1; 
}
//----------------------------------------------------------------------------
void* PX2Max8ClassDesc::Create (BOOL) 
{ 
	return new PX2SceneExport; 
}
//----------------------------------------------------------------------------
const TCHAR* PX2Max8ClassDesc::ClassName () 
{ 
	return _T("PX2SceneExport"); 
}
//----------------------------------------------------------------------------
SClass_ID PX2Max8ClassDesc::SuperClassID () 
{ 
	return SCENE_EXPORT_CLASS_ID; 
}
//----------------------------------------------------------------------------
Class_ID PX2Max8ClassDesc:: ClassID () 
{ 
	return ID;
}
//----------------------------------------------------------------------------
const TCHAR* PX2Max8ClassDesc::Category ()
{ 
	return _T("Exporter"); 
}
//----------------------------------------------------------------------------
const TCHAR* PX2Max8ClassDesc::InternalName () 
{ 
	return _T("Phoenix2");
}
//----------------------------------------------------------------------------
HINSTANCE PX2Max8ClassDesc::HInstance () 
{ 
	return msInstance; 
}
//----------------------------------------------------------------------------