/*
*
* 文件名称	：	PX2CameraNode.cpp
*
*/

#include "PX2CameraNode.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Node, CameraNode);
PX2_IMPLEMENT_STREAM(CameraNode);
PX2_IMPLEMENT_FACTORY(CameraNode);

//----------------------------------------------------------------------------
CameraNode::CameraNode (Camera* camera)
:
mCamera(camera)
{
	if (mCamera)
	{
		LocalTransform.SetTranslate(mCamera->GetPosition());

		HMatrix rotate(mCamera->GetDVector(), mCamera->GetUVector(),
			mCamera->GetRVector(), APoint::ORIGIN, true);

		LocalTransform.SetRotate(rotate);
	}
}
//----------------------------------------------------------------------------
CameraNode::~CameraNode ()
{
}
//----------------------------------------------------------------------------
void CameraNode::SetCamera (Camera* camera)
{
	mCamera = camera;

	if (mCamera)
	{
		LocalTransform.SetTranslate(mCamera->GetPosition());

		HMatrix rotate(mCamera->GetDVector(), mCamera->GetUVector(),
			mCamera->GetRVector(), APoint::ORIGIN, true);

		LocalTransform.SetRotate(rotate);

		Update();
	}
}
//----------------------------------------------------------------------------
void CameraNode::UpdateWorldData (double applicationTime)
{
	Node::UpdateWorldData(applicationTime);

	if (mCamera)
	{
		APoint camPosition = WorldTransform.GetTranslate();
		AVector camDVector, camUVector, camRVector;
		WorldTransform.GetRotate().GetColumn(0, camDVector);
		WorldTransform.GetRotate().GetColumn(1, camUVector);
		WorldTransform.GetRotate().GetColumn(2, camRVector);
		mCamera->SetFrame(camPosition, camDVector, camUVector, camRVector);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称
//----------------------------------------------------------------------------
Object* CameraNode::GetObjectByName (const std::string& name)
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
void CameraNode::GetAllObjectsByName (const std::string& name,
									  std::vector<Object*>& objects)
{
	Node::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mCamera, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
CameraNode::CameraNode (LoadConstructor value)
:
Node(value)
{
}
//----------------------------------------------------------------------------
void CameraNode::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Node::Load(source);

	source.ReadPointer(mCamera);

	PX2_END_DEBUG_STREAM_LOAD(CameraNode, source);
}
//----------------------------------------------------------------------------
void CameraNode::Link (InStream& source)
{
	Node::Link(source);

	source.ResolveLink(mCamera);
}
//----------------------------------------------------------------------------
void CameraNode::PostLink ()
{
	Node::PostLink();
}
//----------------------------------------------------------------------------
bool CameraNode::Register (OutStream& target) const
{
	if (Node::Register(target))
	{
		target.Register(mCamera);
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void CameraNode::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Node::Save(target);

	target.WritePointer(mCamera);

	PX2_END_DEBUG_STREAM_SAVE(CameraNode, target);
}
//----------------------------------------------------------------------------
int CameraNode::GetStreamingSize () const
{
	int size = Node::GetStreamingSize();
	size += PX2_POINTERSIZE(mCamera);
	return size;
}
//----------------------------------------------------------------------------