/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectMaterial.cpp
*
*/

#include "PX2EffectMaterial.hpp"
#include "PX2PVWMatrixConstant.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Material, EffectMaterial);
PX2_IMPLEMENT_STREAM(EffectMaterial);
PX2_IMPLEMENT_FACTORY(EffectMaterial);

//----------------------------------------------------------------------------
EffectMaterial::EffectMaterial (const std::string &filename)
:
Material(filename)
{
}
//----------------------------------------------------------------------------
EffectMaterial::~EffectMaterial ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Name support.
//----------------------------------------------------------------------------
Object* EffectMaterial::GetObjectByName (const std::string& name)
{
	Object* found = Material::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void EffectMaterial::GetAllObjectsByName (const std::string& name,
										   std::vector<Object*>& objects)
{
	Material::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Streaming support.
//----------------------------------------------------------------------------
EffectMaterial::EffectMaterial (LoadConstructor value)
:
Material(value)
{
}
//----------------------------------------------------------------------------
void EffectMaterial::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Material::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EffectMaterial, source);
}
//----------------------------------------------------------------------------
void EffectMaterial::Link (InStream& source)
{
	Material::Link(source);
}
//----------------------------------------------------------------------------
void EffectMaterial::PostLink ()
{
	Material::PostLink();
}
//----------------------------------------------------------------------------
bool EffectMaterial::Register (OutStream& target) const
{
	return Material::Register(target);
}
//----------------------------------------------------------------------------
void EffectMaterial::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Material::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EffectMaterial, target);
}
//----------------------------------------------------------------------------
int EffectMaterial::GetStreamingSize () const
{
	int size = Material::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------------
