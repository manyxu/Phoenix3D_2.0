/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionTriMeshShape.cpp
*
*/

#include "PX2BtCollisionTriMeshShape.hpp"
#include "PX2BtConverter.hpp"
#include "PX2BtCollisionDebugLines.hpp"
using namespace TdBt;
using namespace PX2;

TriangleMeshCollisionShape::TriangleMeshCollisionShape(PX2::Vector3f *vertices, 
													   unsigned int vertexCount,
													   unsigned int *indices, 
													   unsigned int indexCount,
													   bool use32bitsIndices)
													   :
mTriMesh(0)
{
	PX2_UNUSED(vertexCount);

	unsigned int numFaces = indexCount/3;

	mTriMesh = new btTriangleMesh(use32bitsIndices);

	btVector3 vertexPos[3];
	for (unsigned int n=0; n<numFaces; ++n)
	{
		const Vector3f &vec0 = vertices[*indices];
		vertexPos[0][0] = vec0.X();
		vertexPos[0][1] = vec0.Y();
		vertexPos[0][2] = vec0.Z();

		const Vector3f &vec1 = vertices[*(indices + 1)];
		vertexPos[1][0] = vec1.X();
		vertexPos[1][1] = vec1.Y();
		vertexPos[1][2] = vec1.Z();

		const Vector3f &vec2 = vertices[*(indices + 2)];
		vertexPos[2][0] = vec2.X();
		vertexPos[2][1] = vec2.Y();
		vertexPos[2][2] = vec2.Z();

		indices += 3;

		mTriMesh->addTriangle(vertexPos[0], vertexPos[1], vertexPos[2]);
	}

	mShape = new btConvexTriangleMeshShape(mTriMesh);
}
//----------------------------------------------------------------------------
TriangleMeshCollisionShape::TriangleMeshCollisionShape(PX2::TriMesh *mesh, 
						   bool use32bitsIndices)
						   :
mTriMesh(0)
{
	mTriMesh = new btTriangleMesh(use32bitsIndices);

	btVector3 vertexPos[3];
	int numTris= mesh->GetNumTriangles();
	for (int i=0; i<numTris; i++)
	{
		APoint triPos[3];
		if (mesh->GetModelTriangle(i, triPos))
		{
			vertexPos[0][0] = triPos[0].X();
			vertexPos[0][1] = triPos[0].Y();
			vertexPos[0][2] = triPos[0].Z();

			vertexPos[1][0] = triPos[1].X();
			vertexPos[1][1] = triPos[1].Y();
			vertexPos[1][2] = triPos[1].Z();

			vertexPos[2][0] = triPos[2].X();
			vertexPos[2][1] = triPos[2].Y();
			vertexPos[2][2] = triPos[2].Z();

			mTriMesh->addTriangle(vertexPos[0], vertexPos[1], vertexPos[2]);
		}
	}

	mShape = new  btConvexTriangleMeshShape(mTriMesh);
}
//----------------------------------------------------------------------------
TriangleMeshCollisionShape::~TriangleMeshCollisionShape ()
{
	if (mTriMesh)
	{
		delete mTriMesh;
	}
	mTriMesh = 0;
}
//----------------------------------------------------------------------------