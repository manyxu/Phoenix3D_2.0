/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2UIMaterial.hpp
*
* 版本		:	1.0 (2011/02/23)
*
* 作者		：	more
*
*/

#ifndef PX2UIMATERIAL_HPP
#define PX2UIMATERIAL_HPP

#include "PX2UIPrerequisites.hpp"
#include "PX2MaterialInstance.hpp"
#include "PX2Texture2D.hpp"

namespace PX2
{

	class UIMaterial : public Material
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(UIMaterial);

	public:
		UIMaterial (
			Shader::SamplerFilter filter = Shader::SF_NEAREST,
			Shader::SamplerCoordinate coordinate0 = Shader::SC_CLAMP_EDGE,
			Shader::SamplerCoordinate coordinate1 = Shader::SC_CLAMP_EDGE);

		virtual ~UIMaterial ();

		PixelShader* GetPixelShader () const;

		MaterialInstance* CreateInstance (Texture2D* texture) const;

		static MaterialInstance* CreateUniqueInstance (Texture2D* texture,
			Shader::SamplerFilter filter, Shader::SamplerCoordinate coordinate0,
			Shader::SamplerCoordinate coordinate1);

	private:
		static int msDx9VRegisters[1];
		static int msOglVRegisters[1];
		static int* msVRegisters[Shader::MAX_PROFILES];
		static std::string msVPrograms[Shader::MAX_PROFILES];
		static int msAllPTextureUnits[1];
		static int* msPTextureUnits[Shader::MAX_PROFILES];
		static std::string msPPrograms[Shader::MAX_PROFILES];
	};

	PX2_REGISTER_STREAM(UIMaterial);
	typedef Pointer0<UIMaterial> UIMaterialPtr;

}

#endif