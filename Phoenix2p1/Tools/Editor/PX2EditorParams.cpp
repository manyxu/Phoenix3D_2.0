/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditorParams.cpp
*
*/

#include "PX2EditorParams.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
EditorParams::EditorParams ()
{
	mGridSize = 40.0f;
}
//-----------------------------------------------------------------------------
EditorParams::~EditorParams ()
{

}
//-----------------------------------------------------------------------------
EditorParams &EditorParams::GetSingleton ()
{
	static EditorParams param;

	return param;
}
//-----------------------------------------------------------------------------
bool EditorParams::Save (std::string filename)
{
	return true;
}
//-----------------------------------------------------------------------------
bool EditorParams::Load (std::string filename)
{
	return true;
}
//-----------------------------------------------------------------------------