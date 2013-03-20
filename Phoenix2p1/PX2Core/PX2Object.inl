/*
*
* 文件名称	：	PX2Object.inl
*
*/

//----------------------------------------------------------------------------
inline void Object::SetCurIOFlag (int flag)
{
	msCurIOFlag = flag;
}
//----------------------------------------------------------------------------
inline int Object::GetCurIOFlag () 
{
	return msCurIOFlag;
}
//----------------------------------------------------------------------------
inline const std::string &Object::GetCurSaveVersion() const
{
	return mCurSaveVersion;
}
//----------------------------------------------------------------------------
inline const std::string &Object::GetVersion() const
{
	return mVersion;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 类型转换
//----------------------------------------------------------------------------
template <class T>
T* StaticCast (Object* object)
{
	return (T*)object;
}
//----------------------------------------------------------------------------
template <class T>
const T* StaticCast (const Object* object)
{
	return (const T*)object;
}
//----------------------------------------------------------------------------
template <class T>
T* DynamicCast (Object* object)
{
	return object && object->IsDerived(T::TYPE) ? (T*)object : 0;
}
//----------------------------------------------------------------------------
template <class T>
const T* DynamicCast (const Object* object)
{
	return object && object->IsDerived(T::TYPE) ? (const T*)object : 0;
}
//----------------------------------------------------------------------------