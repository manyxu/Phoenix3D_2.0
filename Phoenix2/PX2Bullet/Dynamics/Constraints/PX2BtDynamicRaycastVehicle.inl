/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtDynamicRaycastVehicle.inl
*
*/

//----------------------------------------------------------------------------
inline btVehicleRaycaster *VehicleRayCaster::GetBulletVehicleRayCaster()
{
	return (btVehicleRaycaster*)mBulletVehicleRayCaster;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// btVehicleTuning
//----------------------------------------------------------------------------
inline btRaycastVehicle::btVehicleTuning *VehicleTuning::GetBulletVehicleTuning()
{
	return mBulletVehicleTuning;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// WheelInfo
//----------------------------------------------------------------------------
inline btWheelInfo *WheelInfo::GetBulletWheelInfo ()
{
	return mWheel;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
inline btRaycastVehicle *RaycastVehicle::GetBulletVehicle ()
{
	return (btRaycastVehicle *)mActionInterface;
}
//----------------------------------------------------------------------------