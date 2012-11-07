/*
*
* 文件名称	：	PX2OpenGLShader.cpp
*
*/

#include "PX2OpenGLShader.hpp"
#include "PX2OpenGLMapping.hpp"
#include "PX2Renderer.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
PdrShader::PdrShader ()
{
}
//----------------------------------------------------------------------------
PdrShader::~PdrShader ()
{
}
//----------------------------------------------------------------------------
void PdrShader::SetSamplerState (Renderer* renderer, const Shader* shader,
								 int profile, 
								 const ShaderParameters* parameters,
								 int maxSamplers,
								 RendererData::SamplerState* currentSS)
{
	int numSamplers = shader->GetNumSamplers();
	if (numSamplers > maxSamplers)
	{
		numSamplers = maxSamplers;
	}

	for (int i = 0; i < numSamplers; ++i)
	{
		Shader::SamplerType type = shader->GetSamplerType(i);
		GLenum target = gOGLTextureTarget[type];
		int textureUnit = shader->GetTextureUnit(profile, i);
		const Texture* texture = parameters->GetTexture(i);
		RendererData::SamplerState& current = currentSS[textureUnit];

		switch (type)
		{
		case Shader::ST_1D:
			{
				renderer->Enable((const Texture1D*)texture, textureUnit);
				current.GetCurrent(target);

				GLint wrap0 = gOGLWrapMode[shader->GetCoordinate(i, 0)];
				if (wrap0 != current.mWrap[0])
				{
					current.mWrap[0] = wrap0;
					glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap0);
				}
				break;
			}
		case Shader::ST_2D:
			{
				renderer->Enable((const Texture2D*)texture, textureUnit);
				current.GetCurrent(target);

				GLint wrap0 = gOGLWrapMode[shader->GetCoordinate(i, 0)];
				if (wrap0 != current.mWrap[0])
				{
					current.mWrap[0] = wrap0;
					glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap0);
				}

				GLint wrap1 = gOGLWrapMode[shader->GetCoordinate(i, 1)];
				if (wrap1 != current.mWrap[1])
				{
					current.mWrap[1] = wrap1;
					glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap1);
				}
				break;
			}
		case Shader::ST_3D:
			{
				renderer->Enable((const Texture3D*)texture, textureUnit);
				current.GetCurrent(target);

				GLint wrap0 = gOGLWrapMode[shader->GetCoordinate(i, 0)];
				if (wrap0 != current.mWrap[0])
				{
					current.mWrap[0] = wrap0;
					glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap0);
				}

				GLint wrap1 = gOGLWrapMode[shader->GetCoordinate(i, 1)];
				if (wrap1 != current.mWrap[1])
				{
					current.mWrap[1] = wrap1;
					glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap1);
				}

				GLint wrap2 = gOGLWrapMode[shader->GetCoordinate(i, 2)];
				if (wrap2 != current.mWrap[2])
				{
					current.mWrap[2] = wrap2;
					glTexParameteri(target, GL_TEXTURE_WRAP_R, wrap2);
				}
				break;
			}
		case Shader::ST_CUBE:
			{
				renderer->Enable((const TextureCube*)texture, textureUnit);
				current.GetCurrent(target);

				GLint wrap0 = gOGLWrapMode[shader->GetCoordinate(i, 0)];
				if (wrap0 != current.mWrap[0])
				{
					current.mWrap[0] = wrap0;
					glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap0);
				}

				GLint wrap1 = gOGLWrapMode[shader->GetCoordinate(i, 1)];
				if (wrap1 != current.mWrap[1])
				{
					current.mWrap[1] = wrap1;
					glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap1);
				}
				break;
			}
		default:
			assertion(false, "Invalid sampler type\n");
			break;
		}

		// 各向异性
		const float maxAnisotropy = (float)Shader::MAX_ANISOTROPY;
		float anisotropy = shader->GetAnisotropy(i);
		if (anisotropy < 1.0f || anisotropy > maxAnisotropy)
		{
			anisotropy = 1.0f;
		}
		if (anisotropy != current.mAnisotropy)
		{
			current.mAnisotropy = anisotropy;
			glTexParameterf(target, GL_TEXTURE_MAX_ANISOTROPY_EXT,
				anisotropy);
		}

		// LOD bias.
		float lodBias = shader->GetLodBias(i);
		if (lodBias != current.mLodBias)
		{
			current.mLodBias = lodBias;
			glTexEnvf(GL_TEXTURE_FILTER_CONTROL, GL_TEXTURE_LOD_BIAS,
				lodBias);
		}

		// magfilter
		Shader::SamplerFilter filter = shader->GetFilter(i);
		if (filter == Shader::SF_NEAREST)
		{
			if (GL_NEAREST != current.mMagFilter)
			{
				current.mMagFilter = GL_NEAREST;
				glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}
		}
		else
		{
			if (GL_LINEAR != current.mMagFilter)
			{
				current.mMagFilter = GL_LINEAR;
				glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
		}

		// minfilter
		GLint minFilter = gOGLMinFilter[filter];
		if (minFilter != current.mMinFilter)
		{
			current.mMinFilter = minFilter;
			glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
		}

		// border color
		Float4 color = shader->GetBorderColor(i);
		if (color != current.mBorderColor)
		{
			current.mBorderColor = color;
			glTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, &color[0]);
		}
	}
}
//----------------------------------------------------------------------------
void PdrShader::DisableTextures (Renderer* renderer, const Shader* shader,
								 int profile, const ShaderParameters* parameters, int maxSamplers)
{
	int numSamplers = shader->GetNumSamplers();
	if (numSamplers > maxSamplers)
	{
		numSamplers = maxSamplers;
	}

	for (int i = 0; i < numSamplers; ++i)
	{
		Shader::SamplerType type = shader->GetSamplerType(i);
		int textureUnit = shader->GetTextureUnit(profile, i);
		const Texture* texture = parameters->GetTexture(i);

		switch (type)
		{
		case Shader::ST_1D:
			{
				renderer->Disable((const Texture1D*)texture, textureUnit);
				break;
			}
		case Shader::ST_2D:
			{
				renderer->Disable((const Texture2D*)texture, textureUnit);
				break;
			}
		case Shader::ST_CUBE:
			{
				renderer->Disable((const TextureCube*)texture, textureUnit);
				break;
			}
		case Shader::ST_3D:
			{
				renderer->Disable((const Texture3D*)texture, textureUnit);
				break;
			}
		default:
			assertion(false, "Invalid sampler type\n");
			break;
		}
	}
}
//----------------------------------------------------------------------------
