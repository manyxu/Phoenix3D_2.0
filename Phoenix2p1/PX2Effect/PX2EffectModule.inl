/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectModule.inl
*
*/

//----------------------------------------------------------------------------
inline InterpCurveFloat &EffectModule::GetCurveFloatMin()
{
	return mCurveFloatMin;
}
//----------------------------------------------------------------------------
inline InterpCurveFloat &EffectModule::GetCurveFloatMax()
{
	return mCurveFloatMax;
}
//----------------------------------------------------------------------------
inline InterpCurveFloat3 &EffectModule::GetCurveFloat3Min()
{
	return mCurveFloat3Min;
}
//----------------------------------------------------------------------------
inline InterpCurveFloat3 &EffectModule::GetCurveFloat3Max()
{
	return mCurveFloat3Max;
}
//----------------------------------------------------------------------------
inline bool EffectModule::IsForInit ()
{
	return mIsForInit;
}
//----------------------------------------------------------------------------
inline bool EffectModule::IsRange ()
{
	return mIsRange;
}
//----------------------------------------------------------------------------
inline EffectModule::ModuleType EffectModule::GetModuleType ()
{
	return mModuleType;
}
//----------------------------------------------------------------------------