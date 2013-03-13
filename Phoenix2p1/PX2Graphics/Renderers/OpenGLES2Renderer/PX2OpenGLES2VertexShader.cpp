/*
*
* ÎÄ¼þÃû³Æ	£º	TdOpenGLES2VertexShader.cpp
*
*/

#include "PX2OpenGLES2VertexShader.hpp"
#include "PX2Renderer.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
PdrVertexShader::PdrVertexShader (Renderer*, const VertexShader* vshader)
{
	const char* programText =
		vshader->GetProgram(VertexShader::GetProfile())->c_str();
	int programLength = (int)strlen(programText);

	GLint compiled;

	// Create the mShader object
	mShader = glCreateShader(GL_VERTEX_SHADER);

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
PdrVertexShader::~PdrVertexShader ()
{
}
//----------------------------------------------------------------------------
void PdrVertexShader::Enable (Renderer* renderer, const VertexShader* vshader, 
	const ShaderParameters* parameters)
{
	int profile = VertexShader::GetProfile();
	const int numConstants = vshader->GetNumConstants();
	for (int i=0; i<numConstants; ++i)
	{
		const int numRegisters = vshader->GetNumRegistersUsed(i);
		float *data = parameters->GetConstant(i)->GetData();
		int baseRegister = vshader->GetBaseRegister(profile, i);

		if (4 == numRegisters)
		{
			glUniformMatrix4fv((GLuint)baseRegister, 1, false, (const GLfloat*)data);
		}
		else
		{
			glUniform4fv((GLuint)baseRegister, 1, data);
		}
	}

	SetSamplerState(renderer, vshader, profile, parameters,
		renderer->mData->mMaxVShaderImages, renderer->mData->mCurrentSS);
}
//----------------------------------------------------------------------------
void PdrVertexShader::Disable (Renderer* renderer, const VertexShader* vshader,
	const ShaderParameters* parameters)
{
	int profile = VertexShader::GetProfile();
	DisableTextures(renderer, vshader, profile, parameters,
		renderer->mData->mMaxVShaderImages);
}
//----------------------------------------------------------------------------
