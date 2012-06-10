/*
*
* 文件名称	：	PX2WireProperty.cpp
*
*/

#include "PX2WireProperty.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, WireProperty);
PX2_IMPLEMENT_STREAM(WireProperty);
PX2_IMPLEMENT_FACTORY(WireProperty);
PX2_IMPLEMENT_DEFAULT_NAMES(Object, WireProperty);

//----------------------------------------------------------------------------
WireProperty::WireProperty ()
    :
    Enabled(false)
{
}
//----------------------------------------------------------------------------
WireProperty::~WireProperty ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
WireProperty::WireProperty (LoadConstructor value)
    :
    Object(value),
    Enabled(false)
{
}
//----------------------------------------------------------------------------
void WireProperty::Load (InStream& source)
{
    PX2_BEGIN_DEBUG_STREAM_LOAD(source);

    Object::Load(source);

    source.ReadBool(Enabled);

    PX2_END_DEBUG_STREAM_LOAD(WireProperty, source);
}
//----------------------------------------------------------------------------
void WireProperty::Link (InStream& source)
{
    Object::Link(source);
}
//----------------------------------------------------------------------------
void WireProperty::PostLink ()
{
    Object::PostLink();
}
//----------------------------------------------------------------------------
bool WireProperty::Register (OutStream& target) const
{
    return Object::Register(target);
}
//----------------------------------------------------------------------------
void WireProperty::Save (OutStream& target) const
{
    PX2_BEGIN_DEBUG_STREAM_SAVE(target);

    Object::Save(target);

    target.WriteBool(Enabled);

    PX2_END_DEBUG_STREAM_SAVE(WireProperty, target);
}
//----------------------------------------------------------------------------
int WireProperty::GetStreamingSize () const
{
    int size = Object::GetStreamingSize();
    size += PX2_BOOLSIZE(Enabled);
    return size;
}
//----------------------------------------------------------------------------