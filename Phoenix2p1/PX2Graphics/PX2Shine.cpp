/*
*
* 文件名称	：	PX2Shine.cpp
*
*/

#include "PX2Shine.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, Shine);
PX2_IMPLEMENT_STREAM(Shine);
PX2_IMPLEMENT_FACTORY(Shine);
PX2_IMPLEMENT_DEFAULT_NAMES(Object, Shine);

//----------------------------------------------------------------------------
Shine::Shine ()
:
Emissive(0.0f, 0.0f, 0.0f, 1.0f),
Ambient(0.0f, 0.0f, 0.0f, 1.0f),
Diffuse(0.0f, 0.0f, 0.0f, 1.0f),
Specular(0.0f, 0.0f, 0.0f, 0.0f)
{
}
//----------------------------------------------------------------------------
Shine::~Shine ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Shine::Shine (LoadConstructor value)
:
Object(value),
Emissive(0.0f, 0.0f, 0.0f, 0.0f),
Ambient(0.0f, 0.0f, 0.0f, 0.0f),
Diffuse(0.5f, 0.5f, 0.5f, 1.0f),
Specular(0.0f, 0.0f, 0.0f, 0.0f)
{
}
//----------------------------------------------------------------------------
void Shine::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Object::Load(source);

	source.ReadAggregate(Emissive);
	source.ReadAggregate(Ambient);
	source.ReadAggregate(Diffuse);
	source.ReadAggregate(Specular);

	PX2_END_DEBUG_STREAM_LOAD(Shine, source);
}
//----------------------------------------------------------------------------
void Shine::Link (InStream& source)
{
	Object::Link(source);
}
//----------------------------------------------------------------------------
void Shine::PostLink ()
{
	Object::PostLink();
}
//----------------------------------------------------------------------------
bool Shine::Register (OutStream& target) const
{
	return Object::Register(target);
}
//----------------------------------------------------------------------------
void Shine::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);

	target.WriteAggregate(Emissive);
	target.WriteAggregate(Ambient);
	target.WriteAggregate(Diffuse);
	target.WriteAggregate(Specular);

	PX2_END_DEBUG_STREAM_SAVE(Shine, target);
}
//----------------------------------------------------------------------------
int Shine::GetStreamingSize () const
{
	int size = Object::GetStreamingSize();
	size += sizeof(Emissive);
	size += sizeof(Ambient);
	size += sizeof(Diffuse);
	size += sizeof(Specular);
	return size;
}
//----------------------------------------------------------------------------