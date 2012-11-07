/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2OpenGLRenderTarget.hpp
*
* 版本		:	1.0 (2011/05/14)
*
* 作者		：	TimeX
*
*/

#ifndef PX2OPENGLRENDERTARGET_HPP
#define PX2OPENGLRENDERTARGET_HPP

#include "PX2OpenGLPrerequisites.hpp"
#include "PX2RenderTarget.hpp"

namespace PX2
{

	class Renderer;

	class PdrRenderTarget
	{
	public:
		PdrRenderTarget (Renderer* renderer, const RenderTarget* renderTarget);
		~PdrRenderTarget ();

		void Enable (Renderer* renderer);
		void Disable (Renderer* renderer);
		void ReadColor (int i, Renderer* renderer, Texture2D*& texture);

	private:
		int mNumTargets, mWidth, mHeight;
		Texture::Format mFormat;
		bool mHasMipmaps, mHasDepthStencil;

		GLuint* mColorTextures;
		GLuint mDepthStencilTexture, mFrameBuffer;
		GLenum* mDrawBuffers;
		int mPrevViewport[4];
		double mPrevDepthRange[2];
	};

}

#endif
