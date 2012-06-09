/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtDynamicableState.cpp
*
*/

#include "PX2BtDynamicableState.hpp"
#include "PX2BtConverter.hpp"
#include "PX2BtDynamicableRigidBody.hpp"
using namespace TdBt;
using namespace PX2;

DynamicableState::DynamicableState (RigidBody *body)
:
mBody(body)
{
}
//----------------------------------------------------------------------------
DynamicableState::~DynamicableState ()
{
}
//----------------------------------------------------------------------------
void DynamicableState::getWorldTransform (btTransform& worldTrans ) const
{
	assertion(mBody!=0, "mBody must not be 0.");

	worldTrans.setOrigin(Converter::ConvertFrom(
		mBody->GetPosition()));
	worldTrans.setRotation(Converter::ConvertFrom(HQuaternion(
		mBody->GetRotation())));
}
//----------------------------------------------------------------------------
void DynamicableState::setWorldTransform (const btTransform& worldTrans)
{
	assertion(mBody!=0, "mBody must not be 0.");

	mBody->SetPosition(Converter::APointConvertFrom(worldTrans.getOrigin()));
	mBody->SetRotation(Converter::ConvertFrom(worldTrans.getRotation()));
}
//----------------------------------------------------------------------------