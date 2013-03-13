/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIPicBox.inl
*
*/

//----------------------------------------------------------------------------
inline bool UIPicBox::IsDynamic ()
{
	return mIsDynamic;
}
//----------------------------------------------------------------------------
inline UIPicBox::PicBoxType UIPicBox::GetPicBoxType ()
{
	return mPicBoxType;
}
//----------------------------------------------------------------------------
inline const Sizef &UIPicBox::GetSize () const
{
	return mSize;
}
//----------------------------------------------------------------------------
inline float UIPicBox::GetWidth ()
{
	return mSize.Width;
}
//----------------------------------------------------------------------------
inline float UIPicBox::GetHeight ()
{
	return mSize.Height;
}
//----------------------------------------------------------------------------
inline Float3 UIPicBox::GetColor () const
{
	return Float3(mColor[0], mColor[1], mColor[2]);
}
//----------------------------------------------------------------------------
inline float UIPicBox::GetAlpha () const
{
	return mColor[3];
}
//----------------------------------------------------------------------------
inline Texture2D *UIPicBox::GetTexture ()
{
	return mTexture;
}
//----------------------------------------------------------------------------
inline const Sizef &UIPicBox::GetTexCornorSize ()
{
	return mCorSize;
}
//----------------------------------------------------------------------------
inline float UIPicBox::GetTexCornerWidth ()
{
	return mCorSize.Width;
}
//----------------------------------------------------------------------------
inline float UIPicBox::GetTexCornerHeight ()
{
	return mCorSize.Height;
}
//----------------------------------------------------------------------------