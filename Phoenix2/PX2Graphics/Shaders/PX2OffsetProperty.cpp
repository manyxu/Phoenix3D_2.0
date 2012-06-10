/*
*
* 文件名称	：	PX2OffsetProperty.cpp
*
*/

#include "PX2OffsetProperty.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, OffsetProperty);
PX2_IMPLEMENT_STREAM(OffsetProperty);
PX2_IMPLEMENT_FACTORY(OffsetProperty);
PX2_IMPLEMENT_DEFAULT_NAMES(Object, OffsetProperty);

//----------------------------------------------------------------------------
OffsetProperty::OffsetProperty ()
    :
    FillEnabled(false),
    LineEnabled(false),
    PointEnabled(false),
    Scale(0.0f),
    Bias(0.0f)
{
}
//----------------------------------------------------------------------------
OffsetProperty::~OffsetProperty ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
OffsetProperty::OffsetProperty (LoadConstructor value)
    :
    Object(value),
    FillEnabled(false),
    LineEnabled(false),
    PointEnabled(false),
    Scale(0.0f),
    Bias(0.0f)
{
}
//----------------------------------------------------------------------------
void OffsetProperty::Load (InStream& source)
{
    PX2_BEGIN_DEBUG_STREAM_LOAD(source);

    Object::Load(source);

    source.ReadBool(FillEnabled);
    source.ReadBool(LineEnabled);
    source.ReadBool(PointEnabled);
    source.Read(Scale);
    source.Read(Bias);

    PX2_END_DEBUG_STREAM_LOAD(OffsetProperty, source);
}
//----------------------------------------------------------------------------
void OffsetProperty::Link (InStream& source)
{
    Object::Link(source);
}
//----------------------------------------------------------------------------
void OffsetProperty::PostLink ()
{
    Object::PostLink();
}
//----------------------------------------------------------------------------
bool OffsetProperty::Register (OutStream& target) const
{
    return Object::Register(target);
}
//----------------------------------------------------------------------------
void OffsetProperty::Save (OutStream& target) const
{
    PX2_BEGIN_DEBUG_STREAM_SAVE(target);

    Object::Save(target);

    target.WriteBool(FillEnabled);
    target.WriteBool(LineEnabled);
    target.WriteBool(PointEnabled);
    target.Write(Scale);
    target.Write(Bias);

    PX2_END_DEBUG_STREAM_SAVE(OffsetProperty, target);
}
//----------------------------------------------------------------------------
int OffsetProperty::GetStreamingSize () const
{
    int size = Object::GetStreamingSize();
    size += PX2_BOOLSIZE(FillEnabled);
    size += PX2_BOOLSIZE(LineEnabled);
    size += PX2_BOOLSIZE(PointEnabled);
    size += sizeof(Scale);
    size += sizeof(Bias);
    return size;
}
//----------------------------------------------------------------------------