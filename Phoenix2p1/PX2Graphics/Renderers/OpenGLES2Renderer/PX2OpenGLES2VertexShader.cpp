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
PdrVertexShader::~PdrVertexShader ()
{
	glDeleteShader(mShader);
}
//----------------------------------------------------------------------------
void PdrVertexShader::Enable (Renderer* renderer,
							  const VertexShader* vshader, const ShaderParameters* parameters)
{
}
//----------------------------------------------------------------------------
void PdrVertexShader::Disable (Renderer* renderer,
							   const VertexShader* vshader, const ShaderParameters* parameters)
{
}
//----------------------------------------------------------------------------
