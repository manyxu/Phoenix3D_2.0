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
	glShaderSource(mShader, 1, &programText, NULL);

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
	glDeleteShader(mShader);
}
//----------------------------------------------------------------------------
void PdrPixelShader::Enable (Renderer* renderer, const PixelShader* pshader,
							 const ShaderParameters* parameters)
{
}
//----------------------------------------------------------------------------
void PdrPixelShader::Disable (Renderer* renderer, const PixelShader* pshader,
							  const ShaderParameters* parameters)
{
}
//----------------------------------------------------------------------------
