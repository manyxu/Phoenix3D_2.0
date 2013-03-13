/*
*
* 文件名称	：	PX2EffectNode.cpp
*
*/

#include "PX2EffectNode.hpp"
#include "PX2ParticleEmitter.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Node, EffectNode);
PX2_IMPLEMENT_STREAM(EffectNode);
PX2_IMPLEMENT_FACTORY(EffectNode);
PX2_IMPLEMENT_DEFAULT_NAMES(Node, EffectNode);

//----------------------------------------------------------------------------
EffectNode::EffectNode ()
{
}
//----------------------------------------------------------------------------
EffectNode::~EffectNode ()
{
}
//----------------------------------------------------------------------------
void EffectNode::Play ()
{
	int numChildren = GetNumChildren();
	for (int i=0; i<numChildren; i++)
	{
		ParticleEmitter *emitt = DynamicCast<ParticleEmitter>(GetChild(i));
		if (emitt)
		{
			emitt->Play();
		}
	}
}
//----------------------------------------------------------------------------
void EffectNode::Stop ()
{
	int numChildren = GetNumChildren();
	for (int i=0; i<numChildren; i++)
	{
		ParticleEmitter *emitt = DynamicCast<ParticleEmitter>(GetChild(i));
		if (emitt)
		{
			emitt->Stop();
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
EffectNode::EffectNode (LoadConstructor value)
	:
Node(value)
{
}
//----------------------------------------------------------------------------
void EffectNode::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Node::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EffectNode, source);
}
//----------------------------------------------------------------------------
void EffectNode::Link (InStream& source)
{
	Node::Link(source);
}
//----------------------------------------------------------------------------
void EffectNode::PostLink ()
{
	Node::PostLink();
}
//----------------------------------------------------------------------------
bool EffectNode::Register (OutStream& target) const
{
	return Node::Register(target);
}
//----------------------------------------------------------------------------
void EffectNode::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Node::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EffectNode, target);
}
//----------------------------------------------------------------------------
int EffectNode::GetStreamingSize () const
{
	int size = Node::GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------
