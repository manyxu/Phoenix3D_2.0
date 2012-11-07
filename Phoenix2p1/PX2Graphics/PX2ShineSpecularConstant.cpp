/*
*
* 文件名称	：	PX2ShineSpecularConstant.cpp
*
*/

#include "PX2ShineSpecularConstant.hpp"
#include "PX2Camera.hpp"
#include "PX2Renderable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, ShaderFloat, ShineSpecularConstant);
PX2_IMPLEMENT_STREAM(ShineSpecularConstant);
PX2_IMPLEMENT_FACTORY(ShineSpecularConstant);

//----------------------------------------------------------------------------
ShineSpecularConstant::ShineSpecularConstant (Shine* shine)
:
ShaderFloat(1),
mShine(shine)
{
	EnableUpdater();
}
//----------------------------------------------------------------------------
ShineSpecularConstant::~ShineSpecularConstant ()
{
}
//----------------------------------------------------------------------------
Shine* ShineSpecularConstant::GetShine ()
{
	return mShine;
}
//----------------------------------------------------------------------------
void ShineSpecularConstant::Update (const Renderable*, const Camera*)
{
	const float* source = (const float*)mShine->Specular;
	float* target = mData;
	for (int i = 0; i < 4; ++i)
	{
		*target++ = *source++;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称
//----------------------------------------------------------------------------
Object* ShineSpecularConstant::GetObjectByName (const std::string& name)
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
void ShineSpecularConstant::GetAllObjectsByName (const std::string& name,
													std::vector<Object*>& objects)
{
	ShaderFloat::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mShine, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
ShineSpecularConstant::ShineSpecularConstant (LoadConstructor value)
:
ShaderFloat(value)
{
}
//----------------------------------------------------------------------------
void ShineSpecularConstant::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	ShaderFloat::Load(source);

	source.ReadPointer(mShine);

	PX2_END_DEBUG_STREAM_LOAD(ShineSpecularConstant, source);
}
//----------------------------------------------------------------------------
void ShineSpecularConstant::Link (InStream& source)
{
	ShaderFloat::Link(source);

	source.ResolveLink(mShine);
}
//----------------------------------------------------------------------------
void ShineSpecularConstant::PostLink ()
{
	ShaderFloat::PostLink();
}
//----------------------------------------------------------------------------
bool ShineSpecularConstant::Register (OutStream& target) const
{
	if (ShaderFloat::Register(target))
	{
		target.Register(mShine);
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void ShineSpecularConstant::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	ShaderFloat::Save(target);

	target.WritePointer(mShine);

	PX2_END_DEBUG_STREAM_SAVE(ShineSpecularConstant, target);
}
//----------------------------------------------------------------------------
int ShineSpecularConstant::GetStreamingSize () const
{
	int size = ShaderFloat::GetStreamingSize();
	size += PX2_POINTERSIZE(mShine);
	return size;
}
//----------------------------------------------------------------------------
