/*
*
* ÎÄ¼þÃû³Æ	£º	PX2LODTerrainPage.inl
*
*/

//----------------------------------------------------------------------------
inline int LODTerrainPage::GetSize () const
{
	return mSize;
}
//----------------------------------------------------------------------------
inline const unsigned short* LODTerrainPage::GetHeights () const
{
	return mHeights;
}
//----------------------------------------------------------------------------
inline const Vector2f& LODTerrainPage::GetOrigin () const
{
	return mOrigin;
}
//----------------------------------------------------------------------------
inline float LODTerrainPage::GetMinElevation () const
{
	return mMinElevation;
}
//----------------------------------------------------------------------------
inline float LODTerrainPage::GetMaxElevation () const
{
	return mMaxElevation;
}
//----------------------------------------------------------------------------
inline float LODTerrainPage::GetSpacing () const
{
	return mSpacing;
}
//----------------------------------------------------------------------------
inline float LODTerrainPage::GetPixelTolerance () const
{
	return mPixelTolerance;
}
//----------------------------------------------------------------------------
inline float LODTerrainPage::GetX (int x) const
{
	return mOrigin.X() + mSpacing*(float)x;
}
//----------------------------------------------------------------------------
inline float LODTerrainPage::GetY (int y) const
{
	return mOrigin.Y() + mSpacing*(float)y;
}
//----------------------------------------------------------------------------
inline float LODTerrainPage::GetHeight (int index) const
{
	return mMinElevation + mMultiplier*(float)mHeights[index];
}
//----------------------------------------------------------------------------
inline float& LODTerrainPage::GetUVBias ()
{
	return mUVBias;
}
//----------------------------------------------------------------------------
inline float LODTerrainPage::GetTextureCoordinate (int index) const
{
	return mUVBias + mTextureSpacing*(1.0f-2.0f*mUVBias)*(float)index;
}
//----------------------------------------------------------------------------
