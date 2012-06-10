/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainMaterial.cpp
*
*/

#include "PX2TerrainMaterial.hpp"
#include "PX2PVWMatrixConstant.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Material, TerrainMaterial);
PX2_IMPLEMENT_STREAM(TerrainMaterial);
PX2_IMPLEMENT_FACTORY(TerrainMaterial);

//----------------------------------------------------------------------------
TerrainMaterial::TerrainMaterial (const std::string &filename)
:
Material(filename)
{
	PixelShader* pshader = GetPixelShader(0, 0);

	pshader->SetFilter(0, Shader::SF_LINEAR_LINEAR);
	pshader->SetCoordinate(0, 0, Shader::SC_REPEAT);
	pshader->SetCoordinate(0, 1, Shader::SC_REPEAT);

	pshader->SetFilter(1, Shader::SF_LINEAR_LINEAR);
	pshader->SetCoordinate(1, 0, Shader::SC_CLAMP);
	pshader->SetCoordinate(1, 1, Shader::SC_CLAMP);

	pshader->SetFilter(2, Shader::SF_LINEAR_LINEAR);
	pshader->SetCoordinate(2, 0, Shader::SC_REPEAT);
	pshader->SetCoordinate(2, 1, Shader::SC_REPEAT);

	pshader->SetFilter(3, Shader::SF_LINEAR_LINEAR);
	pshader->SetCoordinate(3, 0, Shader::SC_REPEAT);
	pshader->SetCoordinate(3, 1, Shader::SC_REPEAT);

	pshader->SetFilter(4, Shader::SF_LINEAR_LINEAR);
	pshader->SetCoordinate(4, 0, Shader::SC_REPEAT);
	pshader->SetCoordinate(4, 1, Shader::SC_REPEAT);

	pshader->SetFilter(5, Shader::SF_LINEAR_LINEAR);
	pshader->SetCoordinate(5, 0, Shader::SC_REPEAT);
	pshader->SetCoordinate(5, 1, Shader::SC_REPEAT);
}
//----------------------------------------------------------------------------
TerrainMaterial::~TerrainMaterial ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Name support.
//----------------------------------------------------------------------------
Object* TerrainMaterial::GetObjectByName (const std::string& name)
{
	Object* found = Material::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void TerrainMaterial::GetAllObjectsByName (const std::string& name,
												std::vector<Object*>& objects)
{
	Material::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Streaming support.
//----------------------------------------------------------------------------
TerrainMaterial::TerrainMaterial (LoadConstructor value)
:
Material(value)
{
}
//----------------------------------------------------------------------------
void TerrainMaterial::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Material::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(TerrainMaterial, source);
}
//----------------------------------------------------------------------------
void TerrainMaterial::Link (InStream& source)
{
	Material::Link(source);
}
//----------------------------------------------------------------------------
void TerrainMaterial::PostLink ()
{
	Material::PostLink();
}
//----------------------------------------------------------------------------
bool TerrainMaterial::Register (OutStream& target) const
{
	if (Material::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void TerrainMaterial::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Material::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(TerrainMaterial, target);
}
//----------------------------------------------------------------------------
int TerrainMaterial::GetStreamingSize () const
{
	int size = Material::GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------
