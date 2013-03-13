/*
*
* ÎÄ¼şÃû³Æ	£º	PX2RawTerrainPage.inl
*
*/

//----------------------------------------------------------------------------
inline Texture2D *RawTerrainPage::GetTexture(int index)
{
	if (0 == index)
		return mTexture0;
	else if (1 == index)
		return mTexture1;
	else if (2 == index)
		return mTexture2;
	else if (3 == index)
		return mTexture3;
	else if (4 == index)
		return mTexture4;

	return 0;
}
//----------------------------------------------------------------------------
inline Texture2D *RawTerrainPage::GetTexture0 ()
{
	return mTexture0;
}
//----------------------------------------------------------------------------
inline Texture2D *RawTerrainPage::GetTextureAlpha ()
{
	return mTextureAlpha;
}
//----------------------------------------------------------------------------
inline Texture2D *RawTerrainPage::GetTexture1 ()
{
	return mTexture1;
}
//----------------------------------------------------------------------------
inline Texture2D *RawTerrainPage::GetTexture2 ()
{
	return mTexture2;
}
//----------------------------------------------------------------------------
inline Texture2D *RawTerrainPage::GetTexture3 ()
{
	return mTexture3;
}
//----------------------------------------------------------------------------
inline Texture2D *RawTerrainPage::GetTexture4 ()
{
	return mTexture4;
}
//----------------------------------------------------------------------------
inline Float2 RawTerrainPage::GetUV0 ()
{
	return Float2(mUV01[0], mUV01[1]);
}
//----------------------------------------------------------------------------
inline Float2 RawTerrainPage::GetUV1 ()
{
	return Float2(mUV01[2], mUV01[3]);
}
//----------------------------------------------------------------------------
inline Float2 RawTerrainPage::GetUV2 ()
{
	return Float2(mUV23[0], mUV23[1]);
}
//----------------------------------------------------------------------------
inline Float2 RawTerrainPage::GetUV3 ()
{
	return Float2(mUV23[2], mUV23[3]);
}
//----------------------------------------------------------------------------
inline Float2 RawTerrainPage::GetUV4 ()
{
	return Float2(mUV4[0], mUV4[1]);
}
//----------------------------------------------------------------------------