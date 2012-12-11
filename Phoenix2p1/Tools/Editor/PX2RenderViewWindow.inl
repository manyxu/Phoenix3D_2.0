/*
*
* ÎÄ¼þÃû³Æ	£º	PX2RenderViewWindow.inl
*
*/

//----------------------------------------------------------------------------
inline void RenderViewWindow::SetScene (PX2::Movable *scene)
{
	mScene = scene;
}
//----------------------------------------------------------------------------
inline PX2::Movable *RenderViewWindow::GetScene ()
{
	return mScene;
}
//----------------------------------------------------------------------------
inline void RenderViewWindow::SetHelpScene(PX2::Movable *scene)
{
	mHelpScene = scene;
}
//----------------------------------------------------------------------------
inline PX2::Movable *RenderViewWindow::GetHelpScene ()
{
	return mHelpScene;
}
//----------------------------------------------------------------------------
inline PX2::Renderer *RenderViewWindow::GetRenderer ()
{
	return mRenderer;
}
//----------------------------------------------------------------------------
inline PX2::Camera *RenderViewWindow::GetCamera ()
{
	return mCamera;
}
//----------------------------------------------------------------------------
inline SceneNodeCtrl *RenderViewWindow::GetSceneNodeCtrl ()
{
	return mSceneNodeCtrl;
}
//----------------------------------------------------------------------------
inline RenderViewWindow::ViewType RenderViewWindow::GetViewType ()
{
	return mViewType;
}
//----------------------------------------------------------------------------
inline void RenderViewWindow::SetViewDetail (ViewDetail viewDetail)
{
	mViewDetail = viewDetail;
}
//----------------------------------------------------------------------------
inline RenderViewWindow::ViewDetail RenderViewWindow::GetViewDetail () const
{
	return mViewDetail;
}
//----------------------------------------------------------------------------
inline void RenderViewWindow::SetRenderMilliseconds (int ms)
{
	mRenderMilliseconds = ms;
}
//----------------------------------------------------------------------------
inline int RenderViewWindow::GetRenderMilliseconds ()
{
	return mRenderMilliseconds;
}
//----------------------------------------------------------------------------
inline void RenderViewWindow::SetCameraSpeed (float moveSpeed)
{
	mCameraMoveSpeed = moveSpeed;
}
//----------------------------------------------------------------------------
inline void RenderViewWindow::GetCameraSpeed (float &moveSpeed)
{
	moveSpeed = mCameraMoveSpeed;
}
//----------------------------------------------------------------------------