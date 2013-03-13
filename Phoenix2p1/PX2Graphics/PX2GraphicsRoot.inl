/*
*
* ÎÄ¼þÃû³Æ	£º	PX2GraphicsRoot.inl
*
*/

//----------------------------------------------------------------------------
inline void GraphicsRoot::SetSize (const Sizef &size)
{
	mSize = size;
}
//----------------------------------------------------------------------------
inline const Sizef &GraphicsRoot::GetSize () const
{
	return mSize;
}
//----------------------------------------------------------------------------
inline void GraphicsRoot::SetCamera (Camera *camera)
{
	mCamera = camera;
}
//----------------------------------------------------------------------------
inline PX2::Camera *GraphicsRoot::GetCamera()
{
	return mCamera;
}
//----------------------------------------------------------------------------