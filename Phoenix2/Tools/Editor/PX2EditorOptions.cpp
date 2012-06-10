/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditorOptions.cpp
*
*/

#include "PX2EditorOptions.hpp"
using namespace PX2Editor;
using namespace PX2;

EditorOptions::EditorOptions ()
{
	mGridSize = 40.0f;
	mOrthoAdjust = 8.0f;
	mOrthoFrustumMin = 1.0f;
	mViewFullIndex = -1;
	mShowEffectEditorBar = false;
}
//-----------------------------------------------------------------------------
EditorOptions::~EditorOptions ()
{

}
//-----------------------------------------------------------------------------
bool EditorOptions::Save (std::string filename)
{
	FileIO output(filename.c_str(), FileIO::FM_DEFAULT_WRITE);

	output.Write(sizeof(float), 1, &mViewFullIndex);
	output.Write(sizeof(bool), 1, &mShowEffectEditorBar);

	output.Close();

	return true;
}
//-----------------------------------------------------------------------------
bool EditorOptions::Load (std::string filename)
{
	FileIO input;
	
	if (input.Open(filename.c_str(), FileIO::FM_DEFAULT_READ))
	{
		input.Read(sizeof(float), 1, &mViewFullIndex);
		input.Read(sizeof(bool), 1, &mShowEffectEditorBar);
		input.Close();

		return true;
	}

	return false;
}
//-----------------------------------------------------------------------------