/*
*
* 文件名称	：	PX2ShineDiffuseConstant.cpp
*
*/

#include "PX2ShineDiffuseConstant.hpp"
#include "PX2Camera.hpp"
#include "PX2Renderable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, ShaderFloat, ShineDiffuseConstant);
PX2_IMPLEMENT_STREAM(ShineDiffuseConstant);
PX2_IMPLEMENT_FACTORY(ShineDiffuseConstant);

//----------------------------------------------------------------------------
ShineDiffuseConstant::ShineDiffuseConstant (Shine* shine)
    :
    ShaderFloat(1),
    mShine(shine)
{
    EnableUpdater();
}
//----------------------------------------------------------------------------
ShineDiffuseConstant::~ShineDiffuseConstant ()
{
}
//----------------------------------------------------------------------------
Shine* ShineDiffuseConstant::GetShine ()
{
    return mShine;
}
//----------------------------------------------------------------------------
void ShineDiffuseConstant::Update (const Renderable*, const Camera*)
{
    const float* source = (const float*)mShine->Diffuse;
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
Object* ShineDiffuseConstant::GetObjectByName (const std::string& name)
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
void ShineDiffuseConstant::GetAllObjectsByName (const std::string& name,
    std::vector<Object*>& objects)
{
    ShaderFloat::GetAllObjectsByName(name, objects);

    PX2_GET_ALL_OBJECTS_BY_NAME(mShine, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
ShineDiffuseConstant::ShineDiffuseConstant (LoadConstructor value)
    :
    ShaderFloat(value)
{
}
//----------------------------------------------------------------------------
void ShineDiffuseConstant::Load (InStream& source)
{
    PX2_BEGIN_DEBUG_STREAM_LOAD(source);

    ShaderFloat::Load(source);

    source.ReadPointer(mShine);

    PX2_END_DEBUG_STREAM_LOAD(ShineDiffuseConstant, source);
}
//----------------------------------------------------------------------------
void ShineDiffuseConstant::Link (InStream& source)
{
    ShaderFloat::Link(source);

    source.ResolveLink(mShine);
}
//----------------------------------------------------------------------------
void ShineDiffuseConstant::PostLink ()
{
    ShaderFloat::PostLink();
}
//----------------------------------------------------------------------------
bool ShineDiffuseConstant::Register (OutStream& target) const
{
    if (ShaderFloat::Register(target))
    {
        target.Register(mShine);
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
void ShineDiffuseConstant::Save (OutStream& target) const
{
    PX2_BEGIN_DEBUG_STREAM_SAVE(target);

    ShaderFloat::Save(target);

    target.WritePointer(mShine);

    PX2_END_DEBUG_STREAM_SAVE(ShineDiffuseConstant, target);
}
//----------------------------------------------------------------------------
int ShineDiffuseConstant::GetStreamingSize () const
{
    int size = ShaderFloat::GetStreamingSize();
    size += PX2_POINTERSIZE(mShine);
    return size;
}
//----------------------------------------------------------------------------
