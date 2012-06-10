/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2OpenGLIndexBuffer.hpp
*
* 版本		:	1.0 (2011/05/14)
*
* 作者		：	TimeX
*
*/

#ifndef PX2OPENGLINDEXBUFFER_HPP
#define PX2OPENGLINDEXBUFFER_HPP

#include "PX2OpenGLPrerequisites.hpp"
#include "PX2IndexBuffer.hpp"

namespace PX2
{

	class Renderer;

	class PdrIndexBuffer
	{
	public:
		PdrIndexBuffer (Renderer* renderer, const IndexBuffer* ibuffer);
		~PdrIndexBuffer ();

		void Enable (Renderer* renderer);
		void Disable (Renderer* renderer);
		void* Lock (Buffer::Locking mode);
		void Unlock ();

	private:
		GLuint mBuffer;
	};

}

#endif
