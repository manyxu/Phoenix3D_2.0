/*
*
* 文件名称	：	TdOpenGLES2Texture2D.cpp
*
*/

#include "PX2OpenGLES2Texture2D.hpp"
#include "PX2OpenGLES2Mapping.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
PdrTexture2D::PdrTexture2D (Renderer*, const Texture2D* texture)
	:
mTexture(0)
{
	mInternalFormat = gOGLTextureInternalFormat[texture->GetFormat()];
	mFormat = gOGLTextureFormat[texture->GetFormat()];
	mType = gOGLTextureType[texture->GetFormat()];

	mNumLevels = texture->GetNumLevels();
	int level;
	for (level = 0; level < mNumLevels; ++level)
	{
		mNumLevelBytes[level] = texture->GetNumLevelBytes(level);
		mDimension[0][level] = texture->GetDimension(0, level);
		mDimension[1][level] = texture->GetDimension(1, level);
	}
	for (/**/; level < Texture::MM_MAX_MIPMAP_LEVELS; ++level)
	{
		mNumLevelBytes[level] = 0;
		mDimension[0][level] = 0;
		mDimension[1][level] = 0;
	}

	// 创建和绑定
	PX2_GL_CHECK(glGenTextures(1, &mTexture));
	PX2_GL_CHECK(glBindTexture(GL_TEXTURE_2D, mTexture));

	mIsCompressed = texture->IsCompressed();
	if (mIsCompressed)
	{
		for (level = 0; level < mNumLevels; ++level)
		{
			PX2_GL_CHECK(glCompressedTexImage2D(GL_TEXTURE_2D, level, mInternalFormat,
				mDimension[0][level], mDimension[1][level], 0,
				mNumLevelBytes[level], texture->GetData(level)));
		}
	}
	else
	{
		for (level = 0; level < mNumLevels; ++level)
		{
			PX2_GL_CHECK(glTexImage2D(GL_TEXTURE_2D, level, mInternalFormat,
				mDimension[0][level], mDimension[1][level], 0, mFormat,
				mType, texture->GetData(level)));
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}
//----------------------------------------------------------------------------
PdrTexture2D::~PdrTexture2D ()
{
	PX2_GL_CHECK(glDeleteTextures(1, &mTexture));
}
//----------------------------------------------------------------------------
void PdrTexture2D::Enable (Renderer*,int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, mTexture);
}
//----------------------------------------------------------------------------
void PdrTexture2D::Disable (Renderer*,int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}
//----------------------------------------------------------------------------
void* PdrTexture2D::Lock (int level, Buffer::Locking mode)
{
	PX2_UNUSED(level);
	PX2_UNUSED(mode);
	assertion (false, "OpenglES does't support Lock.");
	return 0;
}
//----------------------------------------------------------------------------
void PdrTexture2D::Unlock (int level)
{
	PX2_UNUSED(level);
	assertion (false, "OpenglES does't support Unlock.");
}
//----------------------------------------------------------------------------
