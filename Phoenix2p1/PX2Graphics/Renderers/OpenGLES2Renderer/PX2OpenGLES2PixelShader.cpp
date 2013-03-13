/*
*
* ÎÄ¼þÃû³Æ	£º	TdOpenGLES2PixelShader.cpp
*
*/

#include "PX2OpenGLES2PixelShader.hpp"
#include "PX2Renderer.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
PdrPixelShader::PdrPixelShader (Renderer*, const PixelShader* pshader)
{
	const char* programText =
		pshader->GetProgram(VertexShader::GetProfile())->c_str();
	int programLength = (int)strlen(programText);

	GLint compiled;

	// Create the mShader object
	mShader = glCreateShader(GL_FRAGMENT_SHADER);

	assertion(mShader != 0, "mShader create failed.");

	// Load the mShader source
	glShaderSource(mShader, 1, &programText, 0);

	// Compile the mShader
	glCompileShader(mShader);

	// Check the compile status
	glGetShaderiv(mShader, GL_COMPILE_STATUS, &compiled);

	if (!compiled) 
	{
		GLint infoLen = 0;

		glGetShaderiv(mShader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = (char *)malloc(sizeof(char) * infoLen);

			glGetShaderInfoLog(mShader, infoLen, NULL, infoLog);
			assertion(false, "Error compiling mShader:\n%s\n", infoLog);      

			free(infoLog);
		}

		glDeleteShader(mShader);
	}
}
//----------------------------------------------------------------------------
PdrPixelShader::~PdrPixelShader ()
{
}
//----------------------------------------------------------------------------
void PdrPixelShader::Enable (Renderer* renderer, const PixelShader* pshader,
							 const ShaderParameters* parameters)
{
	int profile = PixelShader::GetProfile();
	const int numConstants = pshader->GetNumConstants();
	for (int i = 0; i < numConstants; ++i)
	{
		const int numRegisters = pshader->GetNumRegistersUsed(i);
		const float* data = parameters->GetConstant(i)->GetData();
		int baseRegister = pshader->GetBaseRegister(profile, i);

		for (int j = 0; j < numRegisters; ++j)
		{
			glUniform4fv((GLuint)baseRegister, 1, data);

			baseRegister++;
			data += 4;
		}
	}

	SetSamplerState(renderer, pshader, profile, parameters,
		renderer->mData->mMaxPShaderImages, renderer->mData->mCurrentSS);
}
//----------------------------------------------------------------------------
void PdrPixelShader::Disable (Renderer* renderer, const PixelShader* pshader,
							  const ShaderParameters* parameters)
{
	int profile = VertexShader::GetProfile();
	DisableTextures(renderer, pshader, profile, parameters,
		renderer->mData->mMaxVShaderImages);
}
//----------------------------------------------------------------------------
