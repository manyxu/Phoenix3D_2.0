/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditSystem.inl
*
*/

//----------------------------------------------------------------------------
inline PX2::Node *EditSystem::GetHelpScene ()
{
	return mHelpScene; 
}
//----------------------------------------------------------------------------
inline EditCommandManager *EditSystem::GetCM ()
{
	return mCM;
}
//----------------------------------------------------------------------------
inline TerrainEdit *EditSystem::GetTerrainEdit ()
{
	return mTerrainEdit;
}
//----------------------------------------------------------------------------
inline EditMap *EditSystem::GetEditMap ()
{
	return mEditMap;
}
//----------------------------------------------------------------------------
inline ActorSelection *EditSystem::GetSelection ()
{
	return mSelection;
}
//----------------------------------------------------------------------------
inline bool EditSystem::IsSelectEditEnable ()
{
	return mSelectEditEnable;
}
//----------------------------------------------------------------------------
inline EditSystem::EditMode EditSystem::GetEditMode ()
{
	return mEditMode;
}
//----------------------------------------------------------------------------
inline void EditSystem::SetSelectedResource (PX2::Object *obj)
{
	mSelectedResource = obj;
}
//----------------------------------------------------------------------------
inline void EditSystem::SetSelectedResourceName (std::string name)
{
	mSelectedResourceName = name;
}
//----------------------------------------------------------------------------
inline PX2::Object *EditSystem::GetSelectedResource ()
{
	return mSelectedResource;
}
//----------------------------------------------------------------------------
inline std::string EditSystem::GetSelectedResourceName ()
{
	return mSelectedResourceName;
}
//----------------------------------------------------------------------------
inline PX2::Object *EditSystem::GetPreViewObject ()
{
	return mPreViewObject;
}
//----------------------------------------------------------------------------
inline PX2::TriMesh *EditSystem::GetXYPlane ()
{
	return mXYPlane;
}
//----------------------------------------------------------------------------
inline PX2::TriMesh *EditSystem::GetXZPlane ()
{
	return mXZPlane;
}
//----------------------------------------------------------------------------
inline PX2::TriMesh *EditSystem::GetYZPlane ()
{
	return mYZPlane;
}
//----------------------------------------------------------------------------