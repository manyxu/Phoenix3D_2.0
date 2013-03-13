/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIManager.inl
*
*/

//----------------------------------------------------------------------------
inline FontManager *UIManager::GetFontManager ()
{
	return mFontManager;
}
//----------------------------------------------------------------------------
inline VertexFormat *UIManager::GetVertexFormat ()
{
	return mVertexFormat;
}
//----------------------------------------------------------------------------
inline UIMaterial *UIManager::GetUIMaterial ()
{
	return mUIMaterial;
}
//----------------------------------------------------------------------------
inline UIMaterial *UIManager::GetUIMaterialDoubleSide ()
{
	return mUIMaterialDoubleSide;
}
//----------------------------------------------------------------------------
inline UIView *UIManager::GetDefaultView ()
{
	return mDefaultView;
}
//----------------------------------------------------------------------------
inline std::map<std::string, UIViewPtr> &UIManager::GetUIViews ()
{
	return mUiViews;
}
//----------------------------------------------------------------------------
inline UIView *UIManager::GetUIView (std::string name)
{
	return mUiViews[name];
}
//----------------------------------------------------------------------------