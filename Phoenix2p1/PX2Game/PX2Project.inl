/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Project.cpp
*
*/

//----------------------------------------------------------------------------
inline void Project::SetName (const std::string &name)
{
	mName = name;
}
//----------------------------------------------------------------------------
inline void Project::SetWidth (int width)
{
	mWidth = width;
}
//----------------------------------------------------------------------------
inline void Project::SetHeight (int height)
{
	mHeight = height;
}
//----------------------------------------------------------------------------
inline void Project::SetInGamePlay (bool inGamePlay)
{
	mIsInGamePlay = inGamePlay;
}
//----------------------------------------------------------------------------
inline bool Project::IsInGamePlay()
{
	return mIsInGamePlay;
}
//----------------------------------------------------------------------------
inline const std::string &Project::GetName () const
{
	return mName;
}
//----------------------------------------------------------------------------
inline const std::string &Project::GetSceneFilename () const
{
	return mSceneFilename;
}
//----------------------------------------------------------------------------
inline const std::string &Project::GetUIFilename () const
{
	return mUIFilename;
}
//----------------------------------------------------------------------------
inline int Project::GetWidth () const
{
	return mWidth;
}
//----------------------------------------------------------------------------
inline int Project::GetHeight () const
{
	return mHeight;
}
//----------------------------------------------------------------------------
inline Scene *Project::GetScene () const
{
	return mScene;
}
//----------------------------------------------------------------------------
inline UIFrame *Project::GetUI () const
{
	return mUI;
}
//----------------------------------------------------------------------------
inline void Project::SetColor (Float4 color)
{
	mColor = color;
}
//----------------------------------------------------------------------------
inline Float4 Project::GetColor ()
{
	return mColor;
}
//----------------------------------------------------------------------------
inline bool Project::IsShowProjectInfo ()
{
	return mIsShowProjectInfo;
}
//----------------------------------------------------------------------------
inline bool Project::IsSceneWired ()
{
	return mIsSceneWired;
}
//----------------------------------------------------------------------------
inline bool Project::IsShowSceneBound ()
{
	return mIsShowSceneBound;
}
//----------------------------------------------------------------------------
inline bool Project::IsShowGrid ()
{
	return mIsShowGrid;
}
//----------------------------------------------------------------------------
inline bool Project::IsUIWired ()
{
	return mIsUIWired;
}
//----------------------------------------------------------------------------
inline float Project::GetUICameraPercent ()
{
	return mUICameraPercent;
}
//----------------------------------------------------------------------------
inline bool Project::IsShowUI ()
{
	return mIsShowUI;
}
//----------------------------------------------------------------------------
inline bool Project::IsShowUIRange ()
{
	return mIsShowUIRange;
}
//----------------------------------------------------------------------------