/*
*
* ÎÄ¼şÃû³Æ	£º	PX2RawTerrain.inl
*
*/

//----------------------------------------------------------------------------
inline TerrainMaterial * RawTerrain::GetTerrainMaterial ()
{
	return mTerrainMaterial;
}
//----------------------------------------------------------------------------
inline Shine *RawTerrain::GetShine ()
{
	return mShine;
}
//----------------------------------------------------------------------------
inline int RawTerrain::GetRowQuantity () const
{
	return mNumRows;
}
//----------------------------------------------------------------------------
inline int RawTerrain::GetColQuantity () const
{
	return mNumCols;
}
//----------------------------------------------------------------------------
inline int RawTerrain::GetSize () const
{
	return mSize;
}
//----------------------------------------------------------------------------
inline float RawTerrain::GetSpacing () const
{
	return mSpacing;
}
//----------------------------------------------------------------------------