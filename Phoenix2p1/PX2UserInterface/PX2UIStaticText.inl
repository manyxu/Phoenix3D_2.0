/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIStaticText.inl
*
*/

//----------------------------------------------------------------------------
inline Font *UIStaticText::GetFont ()
{
	return mFont;
}
//----------------------------------------------------------------------------
inline const std::string &UIStaticText::GetText () const
{
	return mText;
}
//----------------------------------------------------------------------------
inline int UIStaticText::GetFontStyle ()
{
	return mFontStyle;
}
//----------------------------------------------------------------------------
inline int UIStaticText::GetDrawStyle ()
{
	return mDrawStyle;
}
//----------------------------------------------------------------------------
inline const Float3 &UIStaticText::GetColor () const
{
	return mColor;
}
//----------------------------------------------------------------------------
inline float UIStaticText::GetAlpha ()
{
	return mAlpha;
}
//----------------------------------------------------------------------------
inline int UIStaticText::GetFontWidth ()
{
	return mFontWidth;
}
//----------------------------------------------------------------------------
inline int UIStaticText::GetFontHeight ()
{
	return mFontHeight;
}
//----------------------------------------------------------------------------
inline bool UIStaticText::IsDoubleSide ()
{
	return mIsDoubleSide;
}
//----------------------------------------------------------------------------