/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2OpenGLTexture2D.hpp
*
* 版本		:	1.0 (2011/05/16)
*
* 作者		：	TimeX
*
*/

#ifndef PX2OPENGLTEXTURE2D_HPP
#define PX2OPENGLTEXTURE2D_HPP

#include "PX2OpenGLPrerequisites.hpp"
#include "PX2Texture2D.hpp"

namespace PX2
{

	class Renderer;

	class PdrTexture2D
	{
	public:
		PdrTexture2D (Renderer* renderer, const Texture2D* texture);
		~PdrTexture2D ();

		inline GLuint GetTexture () { return mTexture; }

		void Enable (Renderer* renderer, int textureUnit);
		void Disable (Renderer* renderer, int textureUnit);
		void* Lock (int level, Buffer::Locking mode);
		void Unlock (int level);

	private:
		GLuint mTexture, mInternalFormat, mFormat, mType, mPreviousTexture;
		GLint mNumLevels;
		GLint mNumLevelBytes[Texture::MM_MAX_MIPMAP_LEVELS];
		GLint mDimension[2][Texture::MM_MAX_MIPMAP_LEVELS];
		GLuint mBuffer[Texture::MM_MAX_MIPMAP_LEVELS];
		void* mLockedMemory[Texture::MM_MAX_MIPMAP_LEVELS];
		bool mWriteLock[Texture::MM_MAX_MIPMAP_LEVELS];
		bool mIsCompressed;
	};

}

#endif
