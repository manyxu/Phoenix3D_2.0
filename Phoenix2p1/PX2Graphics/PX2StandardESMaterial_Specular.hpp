/*
*
* ÎÄ¼þÃû³Æ	£º	PX2StandardESMaterial_Specular.h
*
*/


#ifndef PX2STANDARDESMATERIAL_SPECULAR_HPP
#define PX2STANDARDESMATERIAL_SPECULAR_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2MaterialInstance.hpp"
#include "PX2Texture2D.hpp"
#include "PX2Light.hpp"
#include "PX2Shine.hpp"

namespace PX2
{

	class StandardESMaterial_Specular : public Material
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(StandardESMaterial_Specular);

	public:
		StandardESMaterial_Specular (const std::string &filename);
		virtual ~StandardESMaterial_Specular ();

		MaterialInstance* CreateInstance (
			PX2::Texture2D *diffTex,
			PX2::Texture2D *specTex,
			float specularPower,
			PX2::Light *dirLight,
			PX2::Shine* shine) const;
	};

	PX2_REGISTER_STREAM(StandardESMaterial_Specular);
	typedef Pointer0<StandardESMaterial_Specular> StandardESMaterial_SpecularPtr;

}

#endif