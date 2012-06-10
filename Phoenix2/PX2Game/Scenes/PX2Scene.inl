/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Scene.inl
*
*/

//----------------------------------------------------------------------------
inline PX2::Light *Scene::GetDefaultLight ()
{
	return mDefaultLight;
}
//----------------------------------------------------------------------------
inline TdBt::DynamicWorld *Scene::GetDynamicWorld ()
{
	return mBulletDynamicWorld;
}
//----------------------------------------------------------------------------
inline TdBt::DebugDrawer *Scene::GetDebugDrawer ()
{
	return mDebugDrawer;
}
//----------------------------------------------------------------------------
inline void Scene::SetSceneID (int id)
{
	mSceneID = id;
}
//----------------------------------------------------------------------------
inline int Scene::GetSceneID ()
{
	return mSceneID;
}
//----------------------------------------------------------------------------
inline PX2::Node *Scene::GetSceneNode ()
{
	return mSceneNode;
}
//----------------------------------------------------------------------------
inline bool Scene::IsPhysicsSimulateion ()
{
	return mPlayPhysicsSimulation;
}
//----------------------------------------------------------------------------
inline AmbientRegionActor *Scene::GetDefaultARActor ()
{
	return mDefaultARActor;
}
//----------------------------------------------------------------------------