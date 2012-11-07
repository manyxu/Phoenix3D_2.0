/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2OpenGLVertexShader.hpp
*
* 版本		:	1.0 (2011/05/14)
*
* 作者		：	TimeX
*
*/

#ifndef PX2OPENGLVERTEXSHADER_HPP
#define PX2OPENGLVERTEXSHADER_HPP

#include "PX2OpenGLPrerequisites.hpp"
#include "PX2OpenGLShader.hpp"
#include "PX2VertexShader.hpp"

namespace PX2
{

	class Renderer;

	class PdrVertexShader : public PdrShader
	{
	public:
		PdrVertexShader (Renderer* renderer, const VertexShader* vshader);
		~PdrVertexShader ();

		void Enable (Renderer* renderer, const VertexShader* vshader,
			const ShaderParameters* parameters);
		void Disable (Renderer* renderer, const VertexShader* vshader,
			const ShaderParameters* parameters);

	private:
		GLuint mShader;
	};

}

#endif
