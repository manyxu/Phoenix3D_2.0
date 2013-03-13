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
mTex(texture),
mTexture(0)
{
	mInternalFormat = gOGLTextureInternalFormat[texture->GetFormat()];
	Texture::Format tdFormat = texture->GetFormat();
	mFormat = gOGLTextureFormat[tdFormat];
	mType = gOGLTextureType[tdFormat];
	int numBytes = texture->GetNumTotalBytes();
	int numLevels = texture->GetNumLevels();
	char *srcData = texture->GetData(0);

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

	char* newSrc = 0;
	int numElement = 0;
	int srcBase = 0;
	if (tdFormat == Texture::TF_A8R8G8B8)
	{
		numElement = numBytes/4;
		newSrc = new1<char>(numBytes);
		for (int i = 0; i < numElement; i++)
		{
			newSrc[srcBase + 2] = srcData[srcBase    ]; // B
			newSrc[srcBase + 1] = srcData[srcBase + 1]; // G
			newSrc[srcBase + 0] = srcData[srcBase + 2]; // R
			newSrc[srcBase + 3] = srcData[srcBase + 3]; // A
			srcBase += 4;
		}
	}
	else if (tdFormat == Texture::TF_R8G8B8)
	{
		numElement = numBytes/3;
		newSrc = new1<char>(numBytes);
		for (int i = 0; i < numElement; i++)
		{
			newSrc[srcBase + 2] = srcData[srcBase    ]; // B
			newSrc[srcBase + 1] = srcData[srcBase + 1]; // G
			newSrc[srcBase + 0] = srcData[srcBase + 2]; // R
			srcBase += 3;
		}
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
		int onePixelBytes = 4;
		if (tdFormat == Texture::TF_A8R8G8B8)
		{
			onePixelBytes = 4;
		}
		else if (tdFormat == Texture::TF_R8G8B8)
		{
			onePixelBytes = 3;
		}
		char *src1 = newSrc;
		int levelByte = 0;
		int lastWidth = 0;
		int lastHegiht = 0;

		for (int level = 0; level < numLevels; ++level)
		{
			int curWidth = texture->GetDimension(0, level);
			int curHegiht = texture->GetDimension(1, level);

			levelByte = onePixelBytes*curWidth*curHegiht;

			PX2_GL_CHECK(glTexImage2D(GL_TEXTURE_2D, level, mInternalFormat,
				mDimension[0][level], mDimension[1][level], 0, mFormat,
				mType, src1));

			src1 += levelByte;
		}

		delete1(newSrc);
	}

	PX2_GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}
//----------------------------------------------------------------------------
PdrTexture2D::~PdrTexture2D ()
{
	PX2_GL_CHECK(glDeleteTextures(1, &mTexture));
}
//----------------------------------------------------------------------------
void PdrTexture2D::Enable (Renderer*,int textureUnit)
{
	PX2_GL_CHECK(glActiveTexture(GL_TEXTURE0 + textureUnit));
	PX2_GL_CHECK(glBindTexture(GL_TEXTURE_2D, mTexture));
}
//----------------------------------------------------------------------------
void PdrTexture2D::Disable (Renderer*,int textureUnit)
{
	PX2_GL_CHECK(glActiveTexture(GL_TEXTURE0 + textureUnit));
	PX2_GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}
//----------------------------------------------------------------------------
void* PdrTexture2D::Lock (int level, Buffer::Locking mode)
{
	Texture::Format format = mTex->GetFormat();
	int numBytes = mTex->GetNumTotalBytes();
	int numLevels = mTex->GetNumLevels();
	char *srcData = mTex->GetData(0);
	char* newSrc = 0;
	int numElement = 0;
	int srcBase = 0;

	PX2_GL_CHECK(glBindTexture(GL_TEXTURE_2D, mTexture));

	mIsCompressed = mTex->IsCompressed();
	if (mIsCompressed)
	{
		for (level = 0; level < mNumLevels; ++level)
		{
			PX2_GL_CHECK(glCompressedTexImage2D(GL_TEXTURE_2D, level, mInternalFormat,
				mDimension[0][level], mDimension[1][level], 0,
				mNumLevelBytes[level], mTex->GetData(level)));
		}
	}
	else
	{
		int onePixelBytes = 4;
		if (format == Texture::TF_A8R8G8B8)
		{
			onePixelBytes = 4;
		}
		else if (format == Texture::TF_R8G8B8)
		{
			onePixelBytes = 3;
		}
		char *src1 = newSrc;
		int levelByte = 0;
		int lastWidth = 0;
		int lastHegiht = 0;

		for (int level = 0; level < numLevels; ++level)
		{
			int curWidth = mTex->GetDimension(0, level);
			int curHegiht = mTex->GetDimension(1, level);

			levelByte = onePixelBytes*curWidth*curHegiht;

			PX2_GL_CHECK(glTexImage2D(GL_TEXTURE_2D, level, mInternalFormat,
				mDimension[0][level], mDimension[1][level], 0, mFormat,
				mType, src1));

			src1 += levelByte;
		}

		delete1(newSrc);
	}

	PX2_GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

	return 0;
}
//----------------------------------------------------------------------------
void PdrTexture2D::Unlock (int level)
{
	PX2_UNUSED(level);
	assertion (false, "OpenglES does't support Unlock.");
}
//----------------------------------------------------------------------------
