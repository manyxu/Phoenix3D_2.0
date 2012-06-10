/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SkinController.inl
*
*/

//----------------------------------------------------------------------------
inline int SkinController::GetNumVertices () const
{
	return mNumVertices;
}
//----------------------------------------------------------------------------
inline int SkinController::GetNumBones () const
{
	return mNumBones;
}
//----------------------------------------------------------------------------
inline Node** SkinController::GetBones () const
{
	return mBones;
}
//----------------------------------------------------------------------------
inline float** SkinController::GetWeights () const
{
	return mWeights;
}
//----------------------------------------------------------------------------
inline APoint** SkinController::GetOffsets () const
{
	return mOffsets;
}
//----------------------------------------------------------------------------
