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
	mPass = pass;

	VertexShader *vshader = pass->GetVertexShader();
	PixelShader *pshader = pass->GetPixelShader();

	renderer->Bind(vshader);
	renderer->Bind(pshader);

	PdrVertexShader *pdrVS = renderer->GetResource(pass->GetVertexShader());
	PdrPixelShader *pdrPS = renderer->GetResource(pass->GetPixelShader());

	mProgramObject = glCreateProgram();
	assertion(mProgramObject != 0, "glCreateProgram failed.");

	GLint vShader = pdrVS->GetShader();
	GLint pShader = pdrPS->GetShader();
	PX2_GL_CHECK(glAttachShader (mProgramObject, vShader));
	PX2_GL_CHECK(glAttachShader (mProgramObject, pShader));

	glBindAttribLocation(mProgramObject, ALP_POSITION, "modelPosition");
	glBindAttribLocation(mProgramObject, ALP_NORMAL, "modelNormal");
	glBindAttribLocation(mProgramObject, ALP_COLOR0, "modelColor0");
	glBindAttribLocation(mProgramObject, ALP_TEXCOORD0, "modelTCoord0");

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
	else
	{
		int vProfile = VertexShader::GetProfile();
		const int vNumConstants = vshader->GetNumConstants();
		for (int i=0; i<vNumConstants; ++i)
		{
			const std::string &name = vshader->GetConstantName(i);
			int location = glGetUniformLocation(mProgramObject, name.c_str());
			vshader->SetBaseRegister(vProfile, i, location);
		}
		const int numVTexs = vshader->GetNumSamplers();
		for (int i=0; i<numVTexs; i++)
		{
			std::string sampleName = vshader->GetSamplerName(i);
			int location = glGetUniformLocation(mProgramObject, sampleName.c_str());
		}

		int pProfile = PixelShader::GetProfile();
		const int pNumConstants = pshader->GetNumConstants();
		for (int i=0; i<pNumConstants; ++i)
		{
			const std::string &name = pshader->GetConstantName(i);
			int location = glGetUniformLocation(mProgramObject, name.c_str());
			pshader->SetBaseRegister(pProfile, i, location);
		}
		const int numPTexs = pshader->GetNumSamplers();
		for (int i=0; i<numPTexs; i++)
		{
			std::string sampleName = pshader->GetSamplerName(i);
			int location = glGetUniformLocation(mProgramObject, sampleName.c_str());
		}
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