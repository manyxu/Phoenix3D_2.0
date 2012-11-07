/*
*
* ÎÄ¼þÃû³Æ	£º	PX2VWMatrixConstant.cpp
*
*/

#include "PX2VWMatrixConstant.hpp"
#include "PX2Camera.hpp"
#include "PX2Renderable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, ShaderFloat, VWMatrixConstant);
PX2_IMPLEMENT_STREAM(VWMatrixConstant);
PX2_IMPLEMENT_FACTORY(VWMatrixConstant);
PX2_IMPLEMENT_DEFAULT_NAMES(ShaderFloat, VWMatrixConstant);
PX2_IMPLEMENT_DEFAULT_STREAM(ShaderFloat, VWMatrixConstant);

//----------------------------------------------------------------------------
VWMatrixConstant::VWMatrixConstant ()
:
ShaderFloat(4)
{
	mAllowUpdater = true;
}
//----------------------------------------------------------------------------
VWMatrixConstant::~VWMatrixConstant ()
{
}
//----------------------------------------------------------------------------
void VWMatrixConstant::Update (const Renderable* renderable, const Camera* camera)
{
	const HMatrix& viewMatrix = camera->GetViewMatrix();
	const HMatrix& worldMatrix = renderable->WorldTransform.Matrix();
	HMatrix viewWorldMatrix = viewMatrix*worldMatrix;

	const float* source = (const float*)viewWorldMatrix;
	float* target = mData;
	for (int i = 0; i < 16; ++i)
	{
		*target++ = *source++;
	}
}
//----------------------------------------------------------------------------
