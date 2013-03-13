/*
*
* 文件名称	：	PX2UserConstant.cpp
*
*/

#include "PX2UserConstant.hpp"
#include "PX2Camera.hpp"
#include "PX2Renderable.hpp"
#include "PX2Time.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, ShaderFloat, UserConstant);
PX2_IMPLEMENT_STREAM(UserConstant);
PX2_IMPLEMENT_FACTORY(UserConstant);
PX2_IMPLEMENT_DEFAULT_NAMES(ShaderFloat, UserConstant);

//----------------------------------------------------------------------------
UserConstant::UserConstant ()
	:
ShaderFloat(1),
mValue(Float4::ZERO)
{
	EnableUpdater();
}
//----------------------------------------------------------------------------
UserConstant::~UserConstant ()
{
}
//----------------------------------------------------------------------------
void UserConstant::Update (const Renderable*, const Camera*)
{
	mValue[0] = (float)GetTimeInSeconds();

	const float* source = (const float*)mValue;
	float* target = mData;
	for (int i = 0; i < 4; ++i)
	{
		*target++ = *source++;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
UserConstant::UserConstant (LoadConstructor value)
	:
ShaderFloat(value)
{
}
//----------------------------------------------------------------------------
void UserConstant::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	ShaderFloat::Load(source);

	source.ReadAggregate<Float4>(mValue);

	PX2_END_DEBUG_STREAM_LOAD(UserConstant, source);
}
//----------------------------------------------------------------------------
void UserConstant::Link (InStream& source)
{
	ShaderFloat::Link(source);
}
//----------------------------------------------------------------------------
void UserConstant::PostLink ()
{
	ShaderFloat::PostLink();
}
//----------------------------------------------------------------------------
bool UserConstant::Register (OutStream& target) const
{
	if (ShaderFloat::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void UserConstant::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	ShaderFloat::Save(target);

	target.WriteAggregate<Float4>(mValue);

	PX2_END_DEBUG_STREAM_SAVE(UserConstant, target);
}
//----------------------------------------------------------------------------
int UserConstant::GetStreamingSize () const
{
	int size = ShaderFloat::GetStreamingSize();
	size += sizeof(mValue);
	return size;
}
//----------------------------------------------------------------------------
