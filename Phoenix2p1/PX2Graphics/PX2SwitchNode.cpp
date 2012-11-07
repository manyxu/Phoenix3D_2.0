/*
*
* 文件名称	：	PX2SwitchNode.cpp
*
*/

#include "PX2SwitchNode.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Node, SwitchNode);
PX2_IMPLEMENT_STREAM(SwitchNode);
PX2_IMPLEMENT_FACTORY(SwitchNode);
PX2_IMPLEMENT_DEFAULT_NAMES(Node, SwitchNode);

//----------------------------------------------------------------------------
SwitchNode::SwitchNode ()
:
mActiveChild(SN_INVALID_CHILD)
{
}
//----------------------------------------------------------------------------
SwitchNode::~SwitchNode ()
{
}
//----------------------------------------------------------------------------
void SwitchNode::GetVisibleSet (Culler& culler, bool noCull)
{
	if (mActiveChild == SN_INVALID_CHILD)
	{
		return;
	}

	Movable* child = mChild[mActiveChild];
	if (child)
	{
		child->OnGetVisibleSet(culler, noCull);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
SwitchNode::SwitchNode (LoadConstructor value)
:
Node(value),
mActiveChild(SN_INVALID_CHILD)
{
}
//----------------------------------------------------------------------------
void SwitchNode::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Node::Load(source);

	source.Read(mActiveChild);

	PX2_END_DEBUG_STREAM_LOAD(SwitchNode, source);
}
//----------------------------------------------------------------------------
void SwitchNode::Link (InStream& source)
{
	Node::Link(source);
}
//----------------------------------------------------------------------------
void SwitchNode::PostLink ()
{
	Node::PostLink();
}
//----------------------------------------------------------------------------
bool SwitchNode::Register (OutStream& target) const
{
	return Node::Register(target);
}
//----------------------------------------------------------------------------
void SwitchNode::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Node::Save(target);

	target.Write(mActiveChild);

	PX2_END_DEBUG_STREAM_SAVE(SwitchNode, target);
}
//----------------------------------------------------------------------------
int SwitchNode::GetStreamingSize () const
{
	int size = Node::GetStreamingSize();
	size += sizeof(mActiveChild);
	return size;
}
//----------------------------------------------------------------------------
