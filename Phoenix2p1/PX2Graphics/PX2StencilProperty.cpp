/*
*
* 文件名称	：	PX2StencilProperty.cpp
*
*/

#include "PX2StencilProperty.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, StencilProperty);
PX2_IMPLEMENT_STREAM(StencilProperty);
PX2_IMPLEMENT_FACTORY(StencilProperty);
PX2_IMPLEMENT_DEFAULT_NAMES(Object, StencilProperty);

//----------------------------------------------------------------------------
StencilProperty::StencilProperty ()
:
Enabled(false),
Compare(CM_NEVER),
Reference(0),
Mask(UINT_MAX),
WriteMask(UINT_MAX),
OnFail(OT_KEEP),
OnZFail(OT_KEEP),
OnZPass(OT_KEEP)
{
}
//----------------------------------------------------------------------------
StencilProperty::~StencilProperty ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
StencilProperty::StencilProperty (LoadConstructor value)
:
Object(value),
Enabled(false),
Compare(CM_NEVER),
Reference(0),
Mask(0),
WriteMask(0),
OnFail(OT_KEEP),
OnZFail(OT_KEEP),
OnZPass(OT_KEEP)
{
}
//----------------------------------------------------------------------------
void StencilProperty::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Object::Load(source);

	source.ReadBool(Enabled);
	source.ReadEnum(Compare);
	source.Read(Reference);
	source.Read(Mask);
	source.Read(WriteMask);
	source.ReadEnum(OnFail);
	source.ReadEnum(OnZFail);
	source.ReadEnum(OnZPass);

	PX2_END_DEBUG_STREAM_LOAD(StencilProperty, source);
}
//----------------------------------------------------------------------------
void StencilProperty::Link (InStream& source)
{
	Object::Link(source);
}
//----------------------------------------------------------------------------
void StencilProperty::PostLink ()
{
	Object::PostLink();
}
//----------------------------------------------------------------------------
bool StencilProperty::Register (OutStream& target) const
{
	return Object::Register(target);
}
//----------------------------------------------------------------------------
void StencilProperty::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);

	target.WriteBool(Enabled);
	target.WriteEnum(Compare);
	target.Write(Reference);
	target.Write(Mask);
	target.Write(WriteMask);
	target.WriteEnum(OnFail);
	target.WriteEnum(OnZFail);
	target.WriteEnum(OnZPass);

	PX2_END_DEBUG_STREAM_SAVE(StencilProperty, target);
}
//----------------------------------------------------------------------------
int StencilProperty::GetStreamingSize () const
{
	int size = Object::GetStreamingSize();
	size += PX2_BOOLSIZE(Enabled);
	size += PX2_ENUMSIZE(Compare);
	size += sizeof(Reference);
	size += sizeof(Mask);
	size += sizeof(WriteMask);
	size += PX2_ENUMSIZE(OnFail);
	size += PX2_ENUMSIZE(OnZFail);
	size += PX2_ENUMSIZE(OnZPass);
	return size;
}
//----------------------------------------------------------------------------