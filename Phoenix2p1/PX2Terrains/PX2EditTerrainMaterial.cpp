/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainMaterial.cpp
*
*/

#include "PX2EditTerrainMaterial.hpp"
#include "PX2PVWMatrixConstant.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Material, EditTerrainMaterial);
PX2_IMPLEMENT_STREAM(EditTerrainMaterial);
PX2_IMPLEMENT_FACTORY(EditTerrainMaterial);

//----------------------------------------------------------------------------
EditTerrainMaterial::EditTerrainMaterial (const std::string &filename)
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
EditTerrainMaterial::~EditTerrainMaterial ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Name support.
//----------------------------------------------------------------------------
Object* EditTerrainMaterial::GetObjectByName (const std::string& name)
{
	Object* found = Material::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void EditTerrainMaterial::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	Material::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Streaming support.
//----------------------------------------------------------------------------
EditTerrainMaterial::EditTerrainMaterial (LoadConstructor value)
	:
Material(value)
{
}
//----------------------------------------------------------------------------
void EditTerrainMaterial::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Material::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EditTerrainMaterial, source);
}
//----------------------------------------------------------------------------
void EditTerrainMaterial::Link (InStream& source)
{
	Material::Link(source);
}
//----------------------------------------------------------------------------
void EditTerrainMaterial::PostLink ()
{
	Material::PostLink();
}
//----------------------------------------------------------------------------
bool EditTerrainMaterial::Register (OutStream& target) const
{
	if (Material::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EditTerrainMaterial::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Material::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EditTerrainMaterial, target);
}
//----------------------------------------------------------------------------
int EditTerrainMaterial::GetStreamingSize () const
{
	int size = Material::GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------
