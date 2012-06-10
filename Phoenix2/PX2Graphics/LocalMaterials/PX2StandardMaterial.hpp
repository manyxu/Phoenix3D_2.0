/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2StandardMaterial.hpp
*
* 版本		:	1.0 (2011/04/05)
*
* 作者		：	more
*
*/

#ifndef PX2STANDARDMATERIAL_HPP
#define PX2STANDARDMATERIAL_HPP

#include "PX2GraphicsPrerequisites.hpp"
#include "PX2MaterialInstance.hpp"
#include "PX2Texture2D.hpp"
#include "PX2TextureCube.hpp"
#include "PX2Light.hpp"
#include "PX2Shine.hpp"

namespace PX2
{

	class PX2_GRAPHICS_ENTRY StandardMaterial : public Material
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(StandardMaterial);

	public:
		StandardMaterial (const std::string &filename);
		virtual ~StandardMaterial ();

		MaterialInstance* CreateInstance (PX2::Texture2D *diffTex,
			bool alphaVertex,
			bool normalEnable,
			PX2::Texture2D *normalTex,
			float normalScale,
			bool specularEnable,
			PX2::Texture2D *specularTex,
			float specularPower,
			PX2::Light *dirLight, 
			PX2::Shine* shine) const;
	};

	PX2_REGISTER_STREAM(StandardMaterial);
	typedef Pointer0<StandardMaterial> StandardMaterialPtr;

}

#endif