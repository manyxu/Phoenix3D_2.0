/*
*
* 文件名称	：	PX2AlphaProperty.cpp
*
*/

#include "PX2AlphaProperty.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, AlphaProperty);
PX2_IMPLEMENT_STREAM(AlphaProperty);
PX2_IMPLEMENT_FACTORY(AlphaProperty);
PX2_IMPLEMENT_DEFAULT_NAMES(Object, AlphaProperty);

//----------------------------------------------------------------------------
AlphaProperty::AlphaProperty ()
    :
    BlendEnabled(false),
    SrcBlend(SBM_SRC_ALPHA),
    DstBlend(DBM_ONE_MINUS_SRC_ALPHA),
    CompareEnabled(false),
    Compare(CM_ALWAYS),
    Reference(0.0f),
    ConstantColor(0.0f, 0.0f, 0.0f, 0.0f)
{
}
//----------------------------------------------------------------------------
AlphaProperty::~AlphaProperty ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
AlphaProperty::AlphaProperty (LoadConstructor value)
    :
    Object(value),
    BlendEnabled(false),
    SrcBlend(SBM_ZERO),
    DstBlend(DBM_ZERO),
    CompareEnabled(false),
    Compare(CM_NEVER),
    Reference(0.0f),
    ConstantColor(0.0f, 0.0f, 0.0f, 0.0f)
{
}
//----------------------------------------------------------------------------
void AlphaProperty::Load (InStream& source)
{
    PX2_BEGIN_DEBUG_STREAM_LOAD(source);

    Object::Load(source);

    source.ReadBool(BlendEnabled);
    source.ReadEnum(SrcBlend);
    source.ReadEnum(DstBlend);
    source.ReadBool(CompareEnabled);
    source.ReadEnum(Compare);
    source.Read(Reference);
    source.ReadAggregate(ConstantColor);

    PX2_END_DEBUG_STREAM_LOAD(AlphaProperty, source);
}
//----------------------------------------------------------------------------
void AlphaProperty::Link (InStream& source)
{
    Object::Link(source);
}
//----------------------------------------------------------------------------
void AlphaProperty::PostLink ()
{
    Object::PostLink();
}
//----------------------------------------------------------------------------
bool AlphaProperty::Register (OutStream& target) const
{
    return Object::Register(target);
}
//----------------------------------------------------------------------------
void AlphaProperty::Save (OutStream& target) const
{
    PX2_BEGIN_DEBUG_STREAM_SAVE(target);

    Object::Save(target);

    target.WriteBool(BlendEnabled);
    target.WriteEnum(SrcBlend);
    target.WriteEnum(DstBlend);
    target.WriteBool(CompareEnabled);
    target.WriteEnum(Compare);
    target.Write(Reference);
    target.WriteAggregate(ConstantColor);

    PX2_END_DEBUG_STREAM_SAVE(AlphaProperty, target);
}
//----------------------------------------------------------------------------
int AlphaProperty::GetStreamingSize () const
{
    int size = Object::GetStreamingSize();
    size += PX2_BOOLSIZE(BlendEnabled);
    size += PX2_ENUMSIZE(SrcBlend);
    size += PX2_ENUMSIZE(DstBlend);
    size += PX2_BOOLSIZE(CompareEnabled);
    size += PX2_ENUMSIZE(Compare);
    size += sizeof(Reference);
    size += sizeof(ConstantColor);
    return size;
}
//----------------------------------------------------------------------------