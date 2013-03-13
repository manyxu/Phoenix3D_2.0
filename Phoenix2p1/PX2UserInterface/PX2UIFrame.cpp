/*
*
* 文件名称	：	PX2UIFrame.cpp
*
*/

#include "PX2UIFrame.hpp"
using namespace PX2;
using namespace std;

PX2_IMPLEMENT_RTTI(PX2, Node, UIFrame);
PX2_IMPLEMENT_STREAM(UIFrame);
PX2_IMPLEMENT_FACTORY(UIFrame);
PX2_IMPLEMENT_DEFAULT_NAMES(Node, UIFrame);

//----------------------------------------------------------------------------
UIFrame::UIFrame ()
{
	SetName("UIFrame");
}
//----------------------------------------------------------------------------
UIFrame::~UIFrame()
{
}
//----------------------------------------------------------------------------
void UIFrame::RegistScriptHandler (std::string handler)
{
	mScriptHandler = handler;
}
//----------------------------------------------------------------------------
void UIFrame::UnRegistScriptHandler ()
{
	mScriptHandler = "";
}
//----------------------------------------------------------------------------
void UIFrame::OnEvent (Event *event)
{
	for (int i=0; i<GetNumChildren(); i++)
	{
		Movable *mov = GetChild(i);
		UIFrame *frame = DynamicCast<UIFrame>(mov);
		if (frame)
		{
			frame->OnEvent(event);
		}
	}
}
//----------------------------------------------------------------------------
void UIFrame::OnChildPicked (int info, Movable *child)
{
	UIFrame *frame = DynamicCast<UIFrame>(GetParent());
	if (frame)
	{
		frame->OnChildPicked(info, child);
	}
}
//----------------------------------------------------------------------------
void UIFrame::OnChildUIAfterPicked (int info, Movable *child)
{
	UIFrame *frame = DynamicCast<UIFrame>(GetParent());
	if (frame)
	{
		frame->OnChildUIAfterPicked(info, child);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
UIFrame::UIFrame (LoadConstructor value)
	:
Node(value)
{
}
//----------------------------------------------------------------------------
void UIFrame::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Node::Load(source);
	source.ReadString(mScriptHandler);

	PX2_END_DEBUG_STREAM_LOAD(UIFrame, source);
}
//----------------------------------------------------------------------------
void UIFrame::Link (InStream& source)
{
	Node::Link(source);
}
//----------------------------------------------------------------------------
void UIFrame::PostLink ()
{
	Node::PostLink();
}
//----------------------------------------------------------------------------
bool UIFrame::Register (OutStream& target) const
{
	return Node::Register(target);
}
//----------------------------------------------------------------------------
void UIFrame::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Node::Save(target);
	target.WriteString(mScriptHandler);

	PX2_END_DEBUG_STREAM_SAVE(UIFrame, target);
}
//----------------------------------------------------------------------------
int UIFrame::GetStreamingSize () const
{
	int size = Node::GetStreamingSize();
	size += PX2_STRINGSIZE(mScriptHandler);

	return size;
}
//----------------------------------------------------------------------------