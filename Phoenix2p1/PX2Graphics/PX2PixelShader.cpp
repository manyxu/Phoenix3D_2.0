/*
*
* ÎÄ¼þÃû³Æ	£º	PX2PixelShader.cpp
*
*/

#include "PX2PixelShader.hpp"
#include "PX2Renderer.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Shader, PixelShader);
PX2_IMPLEMENT_STREAM(PixelShader);
PX2_IMPLEMENT_FACTORY(PixelShader);
PX2_IMPLEMENT_DEFAULT_NAMES(Shader, PixelShader);
PX2_IMPLEMENT_DEFAULT_STREAM(Shader, PixelShader);

PixelShader::Profile PixelShader::msProfile = PixelShader::PP_NONE;

//----------------------------------------------------------------------------
PixelShader::PixelShader (const std::string& programName, int numInputs,
						  int numOutputs, int numConstants, int numSamplers, bool profileOwner)
						  :
Shader(programName, numInputs, numOutputs, numConstants, numSamplers,
	   profileOwner)
{
}
//----------------------------------------------------------------------------
PixelShader::~PixelShader ()
{
	Renderer::UnbindAll(this);
}
//----------------------------------------------------------------------------
void PixelShader::SetProfile (Profile profile)
{
	msProfile = profile;
}
//----------------------------------------------------------------------------
PixelShader::Profile PixelShader::GetProfile ()
{
	return msProfile;
}
//----------------------------------------------------------------------------
