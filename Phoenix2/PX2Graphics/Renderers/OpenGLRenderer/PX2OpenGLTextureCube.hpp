/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2OpenGLTextureCube.hpp
*
* 版本		:	1.0 (2011/05/14)
*
* 作者		：	TimeX
*
*/

#ifndef PX2OPENGLTEXTURECUBE_HPP
#define PX2OPENGLTEXTURECUBE_HPP

#include "PX2OpenGLPrerequisites.hpp"
#include "PX2TextureCube.hpp"

namespace PX2
{

	class Renderer;

	class PdrTextureCube
	{
	public:
		PdrTextureCube (Renderer* renderer, const TextureCube* texture);
		~PdrTextureCube ();

		void Enable (Renderer* renderer, int textureUnit);
		void Disable (Renderer* renderer, int textureUnit);
		void* Lock (int face, int level, Buffer::Locking mode);
		void Unlock (int face, int level);

	private:
		GLuint mTexture, mInternalFormat, mFormat, mType, mPreviousTexture;
		GLint mNumLevels;
		GLint mNumLevelBytes[Texture::MM_MAX_MIPMAP_LEVELS];
		GLint mDimension[2][Texture::MM_MAX_MIPMAP_LEVELS];
		GLuint mBuffer[6][Texture::MM_MAX_MIPMAP_LEVELS];
		void* mLockedMemory[6][Texture::MM_MAX_MIPMAP_LEVELS];
		bool mWriteLock[6][Texture::MM_MAX_MIPMAP_LEVELS];
		bool mIsCompressed;
	};

}

#endif