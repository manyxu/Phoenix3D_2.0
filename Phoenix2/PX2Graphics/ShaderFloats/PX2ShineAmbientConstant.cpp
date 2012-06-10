/*
*
* 文件名称	：	PX2ShineAmbientConstant.cpp
*
*/

#include "PX2ShineAmbientConstant.hpp"
#include "PX2Camera.hpp"
#include "PX2Renderable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, ShaderFloat, ShineAmbientConstant);
PX2_IMPLEMENT_STREAM(ShineAmbientConstant);
PX2_IMPLEMENT_FACTORY(ShineAmbientConstant);

//----------------------------------------------------------------------------
ShineAmbientConstant::ShineAmbientConstant (Shine* shine)
:
ShaderFloat(1),
mShine(shine)
{
	EnableUpdater();
}
//----------------------------------------------------------------------------
ShineAmbientConstant::~ShineAmbientConstant ()
{
}
//----------------------------------------------------------------------------
Shine* ShineAmbientConstant::GetShine ()
{
	return mShine;
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::Update (const Renderable*, const Camera*)
{
	const float* source = (const float*)mShine->Ambient;
	float* target = mData;
	for (int i = 0; i < 4; ++i)
	{
		*target++ = *source++;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* ShineAmbientConstant::GetObjectByName (const std::string& name)
{
	Object* found = ShaderFloat::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	PX2_GET_OBJECT_BY_NAME(mShine, name, found);
	return 0;
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::GetAllObjectsByName (const std::string& name,
												   std::vector<Object*>& objects)
{
	ShaderFloat::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mShine, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
ShineAmbientConstant::ShineAmbientConstant (LoadConstructor value)
:
ShaderFloat(value)
{
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	ShaderFloat::Load(source);

	source.ReadPointer(mShine);

	PX2_END_DEBUG_STREAM_LOAD(ShineAmbientConstant, source);
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::Link (InStream& source)
{
	ShaderFloat::Link(source);

	source.ResolveLink(mShine);
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::PostLink ()
{
	ShaderFloat::PostLink();
}
//----------------------------------------------------------------------------
bool ShineAmbientConstant::Register (OutStream& target) const
{
	if (ShaderFloat::Register(target))
	{
		target.Register(mShine);
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	ShaderFloat::Save(target);

	target.WritePointer(mShine);

	PX2_END_DEBUG_STREAM_SAVE(ShineAmbientConstant, target);
}
//----------------------------------------------------------------------------
int ShineAmbientConstant::GetStreamingSize () const
{
	int size = ShaderFloat::GetStreamingSize();
	size += PX2_POINTERSIZE(mShine);
	return size;
}
//----------------------------------------------------------------------------
