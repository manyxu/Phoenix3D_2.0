/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIView.inl
*
*/

//----------------------------------------------------------------------------
inline int UIView::GetID ()
{
	return mID;
}
//----------------------------------------------------------------------------
inline const Sizef &UIView::GetSize () const
{
	return mSize;
}
//----------------------------------------------------------------------------
inline float UIView::GetWidth ()
{
	return mSize.Width;
}
//----------------------------------------------------------------------------
inline float UIView::GetHeight ()
{
	return mSize.Height;
}
//----------------------------------------------------------------------------
inline void UIView::SetRenderer(Renderer *renderer)
{
	mRenderer = renderer;
}
//----------------------------------------------------------------------------
inline void UIView::SetMainFrame (UIFrame *frame)
{
	mUIMainFrame = frame;
}
//----------------------------------------------------------------------------
inline Renderer *UIView::GetRenderer ()
{
	return mRenderer;
}
//----------------------------------------------------------------------------
inline Camera *UIView::GetCamera ()
{
	return mCamera;
}
//----------------------------------------------------------------------------
inline UIFrame *UIView::GetMainFrame ()
{
	return mUIMainFrame;
}
//----------------------------------------------------------------------------
inline Culler &UIView::GetCuller ()
{
	return mCuller;
}
//----------------------------------------------------------------------------
inline std::vector<UIPicBoxPtr> &UIView::GetPickedPicBoxs ()
{
	return mPickedPicBoxes;
}
//----------------------------------------------------------------------------