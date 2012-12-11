/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainMaterial.hpp
*
*/

#ifndef PX2EDITTERRAINMATERIAL_HPP
#define PX2EDITTERRAINMATERIAL_HPP

#include "PX2TerrainsPre.hpp"

namespace PX2
{

	class EditTerrainMaterial : public Material
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EditTerrainMaterial);

	public:
		EditTerrainMaterial (const std::string &filename);
		virtual ~EditTerrainMaterial ();
	};

	PX2_REGISTER_STREAM(EditTerrainMaterial);
	typedef Pointer0<EditTerrainMaterial> EditTerrainMaterialPtr;

}

#endif