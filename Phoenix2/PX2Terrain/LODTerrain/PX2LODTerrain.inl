/*
*
* ÎÄ¼þÃû³Æ	£º	PX2LODTerrain.inl
*
*/

inline void LODTerrain::SetRenderer (Renderer* renderer)
{
	mRenderer = renderer;
}
//----------------------------------------------------------------------------
inline int LODTerrain::GetRowQuantity () const
{
	return mRowQuantity;
}
//----------------------------------------------------------------------------
inline int LODTerrain::GetColQuantity () const
{
	return mColQuantity;
}
//----------------------------------------------------------------------------
inline int LODTerrain::GetSize () const
{
	return mSize;
}
//----------------------------------------------------------------------------
inline float LODTerrain::GetMinElevation () const
{
	return mMinElevation;
}
//----------------------------------------------------------------------------
inline float LODTerrain::GetMaxElevation () const
{
	return mMaxElevation;
}
//----------------------------------------------------------------------------
inline float LODTerrain::GetSpacing () const
{
	return mSpacing;
}
//----------------------------------------------------------------------------
inline float LODTerrain::GetPixelTolerance () const
{
	return mPixelTolerance;
}
//----------------------------------------------------------------------------
inline bool &LODTerrain::CloseAssumption ()
{
	return mCloseAssumption;
}
//----------------------------------------------------------------------------
inline float &LODTerrain::GetUVBias ()
{
	return mUVBias;
}
//----------------------------------------------------------------------------
inline Float4 &LODTerrain::GetBorderColor ()
{
	return mBorderColor;
}
//----------------------------------------------------------------------------
inline bool LODTerrain::UsingLOD ()
{
	return mUseLOD;
}
//----------------------------------------------------------------------------