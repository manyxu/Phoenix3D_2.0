/*
*
* 文件名称	：	PX2CullProperty.cpp
*
*/

#include "PX2CullProperty.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, CullProperty);
PX2_IMPLEMENT_STREAM(CullProperty);
PX2_IMPLEMENT_FACTORY(CullProperty);
PX2_IMPLEMENT_DEFAULT_NAMES(Object, CullProperty);

//----------------------------------------------------------------------------
CullProperty::CullProperty ()
:
Enabled(true),
CCWOrder(true)
{
}
//----------------------------------------------------------------------------
CullProperty::~CullProperty ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
CullProperty::CullProperty (LoadConstructor value)
:
Object(value),
Enabled(false),
CCWOrder(false)
{
}
//----------------------------------------------------------------------------
void CullProperty::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Object::Load(source);

	source.ReadBool(Enabled);
	source.ReadBool(CCWOrder);

	PX2_END_DEBUG_STREAM_LOAD(CullProperty, source);
}
//----------------------------------------------------------------------------
void CullProperty::Link (InStream& source)
{
	Object::Link(source);
}
//----------------------------------------------------------------------------
void CullProperty::PostLink ()
{
	Object::PostLink();
}
//----------------------------------------------------------------------------
bool CullProperty::Register (OutStream& target) const
{
	return Object::Register(target);
}
//----------------------------------------------------------------------------
void CullProperty::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);

	target.WriteBool(Enabled);
	target.WriteBool(CCWOrder);

	PX2_END_DEBUG_STREAM_SAVE(CullProperty, target);
}
//----------------------------------------------------------------------------
int CullProperty::GetStreamingSize () const
{
	int size = Object::GetStreamingSize();
	size += PX2_BOOLSIZE(Enabled);
	size += PX2_BOOLSIZE(CCWOrder);
	return size;
}
//----------------------------------------------------------------------------