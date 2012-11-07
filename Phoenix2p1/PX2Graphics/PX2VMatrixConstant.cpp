/*
*
* ÎÄ¼þÃû³Æ	£º	PX2VMatrixConstant.cpp
*
*/

#include "PX2VMatrixConstant.hpp"
#include "PX2Camera.hpp"
#include "PX2Renderable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, ShaderFloat, VMatrixConstant);
PX2_IMPLEMENT_STREAM(VMatrixConstant);
PX2_IMPLEMENT_FACTORY(VMatrixConstant);
PX2_IMPLEMENT_DEFAULT_NAMES(ShaderFloat, VMatrixConstant);
PX2_IMPLEMENT_DEFAULT_STREAM(ShaderFloat, VMatrixConstant);

//----------------------------------------------------------------------------
VMatrixConstant::VMatrixConstant ()
:
ShaderFloat(4)
{
	mAllowUpdater = true;
}
//----------------------------------------------------------------------------
VMatrixConstant::~VMatrixConstant ()
{
}
//----------------------------------------------------------------------------
void VMatrixConstant::Update (const Renderable*, const Camera* camera)
{
	const HMatrix& viewMatrix = camera->GetViewMatrix();

	const float* source = (const float*)viewMatrix;
	float* target = mData;
	for (int i = 0; i < 16; ++i)
	{
		*target++ = *source++;
	}
}
//----------------------------------------------------------------------------
