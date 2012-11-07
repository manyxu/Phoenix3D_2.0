/*
*
* ÎÄ¼þÃû³Æ	£º	TdOpenGLES2MaterialPass.cpp
*
*/

#include "PX2OpenGLES2MaterialPass.hpp"
#include "PX2Renderer.hpp"
#include "PX2OpenGLES2VertexShader.hpp"
#include "PX2OpenGLES2PixelShader.hpp"
using namespace PX2;

PdrMaterialPass::PdrMaterialPass (Renderer *renderer, const MaterialPass *pass)
{
	mProgramObject = glCreateProgram();

	assertion(mProgramObject != 0, "glCreateProgram failed.");

	VertexShader *vshader = pass->GetVertexShader();
	PixelShader *pshader = pass->GetPixelShader();

	renderer->Bind(vshader);
	renderer->Bind(pshader);

	PdrVertexShader *pdrVS = renderer->GetResource(pass->GetVertexShader());
	PdrPixelShader *pdrPS = renderer->GetResource(pass->GetPixelShader());

	glAttachShader (mProgramObject, pdrVS->GetShader());
	glAttachShader (mProgramObject, pdrPS->GetShader());

	// Link the program
	glLinkProgram (mProgramObject);

	// Check the link status
	GLint linked;
	glGetProgramiv(mProgramObject, GL_LINK_STATUS, &linked);

	if (!linked) 
	{
		GLint infoLen = 0;

		glGetProgramiv(mProgramObject, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);

			glGetProgramInfoLog(mProgramObject, infoLen, NULL, infoLog);

			assertion(false, "Error linking program:\n%s\n", infoLog);      

			free(infoLog);
		}

		glDeleteProgram(mProgramObject);
	}
}
//----------------------------------------------------------------------------
PdrMaterialPass::~PdrMaterialPass ()
{
	glDeleteProgram(mProgramObject);
}
//----------------------------------------------------------------------------
void PdrMaterialPass::Enable (Renderer* renderer)
{
	glUseProgram(mProgramObject);
}
//----------------------------------------------------------------------------
void PdrMaterialPass::Disable (Renderer* renderer)
{
}
//----------------------------------------------------------------------------