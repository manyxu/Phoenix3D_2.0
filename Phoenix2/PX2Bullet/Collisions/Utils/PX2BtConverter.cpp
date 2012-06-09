/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtConverter.cpp
*
*/

#include "PX2BtConverter.hpp"
using namespace TdBt;

Converter::Converter ()
{
}
//----------------------------------------------------------------------------
Converter::~Converter ()
{
}
//----------------------------------------------------------------------------
btVector3 Converter::ConvertFrom (const PX2::APoint &point)
{
	return btVector3(point.X(), point.Y(), point.Z());
}
//----------------------------------------------------------------------------
btVector3 Converter::ConvertFrom (const PX2::AVector &vec)
{
	return btVector3(vec.X(), vec.Y(), vec.Z());
}
//----------------------------------------------------------------------------
btVector3 Converter::ConvertFrom (const PX2::Vector3f &vec)
{
	 return btVector3(vec.X(), vec.Y(), vec.Z());
}
//----------------------------------------------------------------------------
btQuaternion Converter::ConvertFrom (const PX2::HQuaternion &quat)
{
	return btQuaternion(quat.X(), quat.Y(), quat.Z(), quat.W());
}
//----------------------------------------------------------------------------
PX2::APoint Converter::APointConvertFrom (const btVector3 &point)
{
	return PX2::APoint(point.x(), point.y(), point.z());
}
//----------------------------------------------------------------------------
PX2::AVector Converter::AVectorConvertFrom (const btVector3 &vec)
{
	return PX2::AVector(vec.x(), vec.y(), vec.z());
}
//----------------------------------------------------------------------------
PX2::Vector3f Converter::Vector3fConvertFrom (const btVector3 &vec)
{
	return PX2::Vector3f(vec.x(), vec.y(), vec.z());
}
//----------------------------------------------------------------------------
PX2::HQuaternion Converter::ConvertFrom (const btQuaternion &quat)
{
	return PX2::HQuaternion(quat.w(), quat.x(), quat.y(), quat.z());
}
//----------------------------------------------------------------------------