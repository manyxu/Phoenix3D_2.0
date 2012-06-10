/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2CollapseRecord.hpp
*
* 版本		:	1.0 (2011/03/17)
*
* 作者		：	more
*
*/

#ifndef PX2COLLAPSERECORD_HPP
#define PX2COLLAPSERECORD_HPP

#include "PX2GraphicsPrerequisites.hpp"

namespace PX2
{

	class PX2_GRAPHICS_ENTRY CollapseRecord
	{
	public:
		CollapseRecord (int vKeep = -1, int vThrow = -1, int numVertices = 0,
			int numTriangles = 0);

		~CollapseRecord ();

		// Edge <VKeep,VThrow>，点的VThrow会被VKeep替换掉
		int VKeep, VThrow;

		// 顶点塌陷掉后，顶点的数量
		int NumVertices;

		// 顶点塌陷掉后，三角形数量
		int NumTriangles;

		// 保存[0..NumTriangles-1]之内被扔掉的顶点的索引
		int NumIndices;
		int* Indices;
	};

}

#endif