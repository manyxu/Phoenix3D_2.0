/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2BtCollisionTrimeshShape.hpp
*
* 版本		:	1.0 (2011/03/07)
*
* 作者		：	more
*
*/

#ifndef PX2BTCOLLISIONTRIMESHSHAPE_HPP
#define PX2BTCOLLISIONTRIMESHSHAPE_HPP

#include "PX2BtCollisionShape.hpp"
#include "PX2TriMesh.hpp"

namespace TdBt
{

	class TriangleMeshCollisionShape : public CollisionShape
	{
	public:
		TriangleMeshCollisionShape(PX2::Vector3f *vertices, 
			unsigned int vertexCount, unsigned int *indices, 
			unsigned int indexCount, bool use32bitsIndices=true);
		TriangleMeshCollisionShape(PX2::TriMesh *mesh, 
			bool use32bitsIndices=true);

		virtual ~TriangleMeshCollisionShape();

	protected:
		btTriangleMesh *mTriMesh;
	};

	typedef PX2::Pointer0<TriangleMeshCollisionShape>
		TriangleMeshCollisionShapePtr;

}

#endif