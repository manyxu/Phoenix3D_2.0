/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ResourceManager.inl
*
*/

//----------------------------------------------------------------------------
inline void ResourceManager::DDSKeepCompressed (bool keep)
{
	mDDSKeepCompressed = keep;
}
//----------------------------------------------------------------------------
inline bool ResourceManager::IsDDSKeepCompressed ()
{
	return mDDSKeepCompressed;
}
//----------------------------------------------------------------------------
inline void ResourceManager::SetResourcePath (const std::string &resPath)
{
	msResPath = resPath;
}
//----------------------------------------------------------------------------
inline const std::string ResourceManager::GetResourcePath ()
{
	return msResPath;
}
//----------------------------------------------------------------------------