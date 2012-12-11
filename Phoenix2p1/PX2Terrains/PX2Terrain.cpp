/*
*
* 文件名称	：	PX2Terrain.cpp
*
*/

#include "PX2Terrain.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Node, Terrain);
PX2_IMPLEMENT_STREAM(Terrain);
PX2_IMPLEMENT_FACTORY(Terrain);

//----------------------------------------------------------------------------
Terrain::~Terrain ()
{
}
//----------------------------------------------------------------------------
Terrain::Terrain ()
{
}
//----------------------------------------------------------------------------
float Terrain::GetHeight (float x, float y) const
{
	PX2_UNUSED(x);
	PX2_UNUSED(y);

	return 0.0f;
}
//----------------------------------------------------------------------------
AVector Terrain::GetNormal (float x, float y) const
{
	PX2_UNUSED(x);
	PX2_UNUSED(y);

	return AVector::ZERO;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* Terrain::GetObjectByName (const std::string& name)
{
	Object* found = Node::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	PX2_GET_OBJECT_BY_NAME(mCamera, name, found);

	return 0;
}
//----------------------------------------------------------------------------
void Terrain::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	Node::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mCamera, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Terrain::Terrain (LoadConstructor value)
	:
Node(value),
	mNumRows(0),
	mNumCols(0),
	mSize(0),
	mMinElevation(0.0f),
	mMaxElevation(0.0f),
	mSpacing(0.0f),
	mCameraRow(0),
	mCameraCol(0)
{
}
//----------------------------------------------------------------------------
void Terrain::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Node::Load(source);

	source.Read(mNumRows);
	source.Read(mNumCols);
	source.Read(mSize);
	source.Read(mMinElevation);
	source.Read(mMaxElevation);
	source.Read(mSpacing);
	source.Read(mCameraRow);
	source.Read(mCameraCol);
	source.ReadPointer(mCamera);

	PX2_END_DEBUG_STREAM_LOAD(Terrain, source);
}
//----------------------------------------------------------------------------
void Terrain::Link (InStream& source)
{
	Node::Link(source);

	source.ResolveLink(mCamera);
}
//----------------------------------------------------------------------------
void Terrain::PostLink ()
{
	Node::PostLink();
}
//----------------------------------------------------------------------------
bool Terrain::Register (OutStream& target) const
{
	if (Node::Register(target))
	{
		target.Register(mCamera);

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void Terrain::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Node::Save(target);

	target.Write(mNumRows);
	target.Write(mNumCols);
	target.Write(mSize);
	target.Write(mMinElevation);
	target.Write(mMaxElevation);
	target.Write(mSpacing);
	target.Write(mCameraRow);
	target.Write(mCameraCol);
	target.WritePointer(mCamera);

	PX2_END_DEBUG_STREAM_SAVE(Terrain, target);
}
//----------------------------------------------------------------------------
int Terrain::GetStreamingSize () const
{
	int size = Node::GetStreamingSize();
	size += sizeof(mNumRows);
	size += sizeof(mNumCols);
	size += sizeof(mSize);
	size += sizeof(mMinElevation);
	size += sizeof(mMaxElevation);
	size += sizeof(mSpacing);
	size += sizeof(mCameraRow);
	size += sizeof(mCameraCol);
	size += PX2_POINTERSIZE(mCamera);

	return size;
}
//----------------------------------------------------------------------------
