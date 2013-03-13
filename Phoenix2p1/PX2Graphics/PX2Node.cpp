/*
*
* 文件名称	：	PX2Node.cpp
*
*/

#include "PX2Node.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Movable, Node);
PX2_IMPLEMENT_STREAM(Node);
PX2_IMPLEMENT_FACTORY(Node);

//----------------------------------------------------------------------------
Node::Node ()
{
}
//----------------------------------------------------------------------------
Node::~Node ()
{
    std::vector<MovablePtr>::iterator iter = mChild.begin();
    std::vector<MovablePtr>::iterator end = mChild.end();
    for (/**/; iter != end; ++iter)
    {
        if (*iter)
        {
            (*iter)->SetParent(0);
            *iter = 0;
        }
    }
}
//----------------------------------------------------------------------------
int Node::AttachChild (Movable* child)
{
    if (!child)
    {
        assertion(false, "You cannot attach null children to a node.\n");
        return -1;
    }

    if (child->GetParent())
    {
        assertion(false, "The child already has a parent.\n");
        return -1;
    }

    child->SetParent(this);
	child->OnAttach();

	// 将孩子插入到第一个可用位置
    std::vector<MovablePtr>::iterator iter = mChild.begin();
    std::vector<MovablePtr>::iterator end = mChild.end();
    for (int i = 0; iter != end; ++iter, ++i)
    {
        if (*iter == 0)
        {
            *iter = child;
            return i;
        }
    }

	// 所有空位都用完了，将孩子插入队列末尾
    const int numChildren = (int)mChild.size();
    mChild.push_back(child);
    return numChildren;
}
//----------------------------------------------------------------------------
int Node::DetachChild (Movable* child)
{
    if (child)
    {
        std::vector<MovablePtr>::iterator iter = mChild.begin();
        std::vector<MovablePtr>::iterator end = mChild.end();
        for (int i = 0; iter != end; ++iter, ++i)
        {
            if (*iter == child)
            {
                (*iter)->SetParent(0);
				(*iter)->OnDetach();
                *iter = 0;
                return i;
            }
        }
    }
    return -1;
}
//----------------------------------------------------------------------------
MovablePtr Node::DetachChildAt (int i)
{
    if (0 <= i && i < (int)mChild.size())
    {
        MovablePtr child = mChild[i];
        if (child)
        {
            child->SetParent(0);
            mChild[i] = 0;
        }
        return child;
    }
    return 0;
}
//----------------------------------------------------------------------------
void Node::DetachAllChildren ()
{
	for (int i=0; i<(int)mChild.size(); i++)
	{
		 MovablePtr child = mChild[i];

		 if (child)
		 {
			 child->SetParent(0);
			 mChild[i] = 0;
		 }
	}
}
//----------------------------------------------------------------------------
MovablePtr Node::SetChild (int i, Movable* child)
{
    if (child)
    {
        assertion(!child->GetParent(), "The child already has a parent.\n");
    }

    const int numChildren = (int)mChild.size();
    if (0 <= i && i < numChildren)
    {
		// 将旧的孩子移除
        MovablePtr previousChild = mChild[i];
        if (previousChild)
        {
            previousChild->SetParent(0);
        }

		// 插入新的孩子到空位
        if (child)
        {
            child->SetParent(this);
        }

        mChild[i] = child;
        return previousChild;
    }

	// 孩子超出范围，将其插入到孩子队列末尾
    if (child)
    {
        child->SetParent(this);
    }
    mChild.push_back(child);
    return 0;
}
//----------------------------------------------------------------------------
MovablePtr Node::GetChild (int i)
{
    if (0 <= i && i < (int)mChild.size())
    {
        return mChild[i];
    }
    return 0;
}
//----------------------------------------------------------------------------
void Node::OnNotPicked (int pickInfo)
{
	for (int i=0; i<(int)mChild.size(); i++)
	{
		if (mChild[i])
		{
			mChild[i]->OnNotPicked(pickInfo);
		}
	}
}
//----------------------------------------------------------------------------
void Node::UpdateWorldData (double applicationTime)
{
    Movable::UpdateWorldData(applicationTime);

    std::vector<MovablePtr>::iterator iter = mChild.begin();
    std::vector<MovablePtr>::iterator end = mChild.end();
    for (/**/; iter != end; ++iter)
    {
        Movable* child = *iter;
        if (child)
        {
            child->Update(applicationTime, false);
        }
    }
}
//----------------------------------------------------------------------------
void Node::UpdateWorldBound ()
{
    if (!WorldBoundIsCurrent)
    {
        bool foundFirstBound = false;
        std::vector<MovablePtr>::iterator iter = mChild.begin();
        std::vector<MovablePtr>::iterator end = mChild.end();
        for (/**/; iter != end; ++iter)
        {
            Movable* child = *iter;
            if (child)
            {
                if (foundFirstBound)
                {
					// 将所有孩子的节点包围体融合到一起，作为当前节点的包围体
                    WorldBound.GrowToContain(child->WorldBound);
                }
                else
                {
					// 首先将第一个孩子的包围盒作为节点的包围盒
                    foundFirstBound = true;
                    WorldBound = child->WorldBound;
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
void Node::GetVisibleSet (Culler& culler, bool noCull)
{
    std::vector<MovablePtr>::iterator iter = mChild.begin();
    std::vector<MovablePtr>::iterator end = mChild.end();
    for (/**/; iter != end; ++iter)
    {
        Movable* child = *iter;
        if (child)
        {
            child->OnGetVisibleSet(culler, noCull);
        }
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Name support.
//----------------------------------------------------------------------------
Object* Node::GetObjectByName (const std::string& name)
{
    Object* found = Movable::GetObjectByName(name);
    if (found)
    {
        return found;
    }

    const int numChildren = (int)mChild.size();
    for (int i = 0; i < numChildren; ++i)
    {
        PX2_GET_OBJECT_BY_NAME(mChild[i], name, found);
    }

    return 0;
}
//----------------------------------------------------------------------------
void Node::GetAllObjectsByName (const std::string& name,
    std::vector<Object*>& objects)
{
    Movable::GetAllObjectsByName(name, objects);

    const int numChildren = (int)mChild.size();
    for (int i = 0; i < numChildren; ++i)
    {
        PX2_GET_ALL_OBJECTS_BY_NAME(mChild[i], name, objects);
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Node::Node (LoadConstructor value)
    :
    Movable(value)
{
}
//----------------------------------------------------------------------------
void Node::Load (InStream& source)
{
    PX2_BEGIN_DEBUG_STREAM_LOAD(source);

    Movable::Load(source);

    int numChildren;
    source.Read(numChildren);
    if (numChildren > 0)
    {
        mChild.resize(numChildren);
        source.ReadPointerVV(numChildren, &mChild[0]);
    }

    PX2_END_DEBUG_STREAM_LOAD(Node, source);
}
//----------------------------------------------------------------------------
void Node::Link (InStream& source)
{
    Movable::Link(source);

    const int numChildren = (int)mChild.size();
    for (int i = 0; i < numChildren; ++i)
    {
        if (mChild[i])
        {
            source.ResolveLink(mChild[i]);
            SetChild(i, mChild[i]);
        }
    }
}
//----------------------------------------------------------------------------
void Node::PostLink ()
{
    Movable::PostLink();
}
//----------------------------------------------------------------------------
bool Node::Register (OutStream& target) const
{
    if (Movable::Register(target))
    {
        const int numChildren = (int)mChild.size();
        for (int i = 0; i < numChildren; ++i)
        {
            if (mChild[i])
            {
                target.Register(mChild[i]);
            }
        }
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
void Node::Save (OutStream& target) const
{
    PX2_BEGIN_DEBUG_STREAM_SAVE(target);

    Movable::Save(target);

    const int numChildren = (int)mChild.size();
    target.Write(numChildren);
    for (int i = 0; i < numChildren; ++i)
    {
        if (mChild[i])
        {
            target.WritePointer(mChild[i]);
        }
        else
        {
            target.WritePointer((Movable*)0);
        }
    }


    PX2_END_DEBUG_STREAM_SAVE(Node, target);
}
//----------------------------------------------------------------------------
int Node::GetStreamingSize () const
{
    int size = Movable::GetStreamingSize();
    int numChildren = (int)mChild.size();
    size += sizeof(numChildren);
    size += numChildren*PX2_POINTERSIZE(mChild[0]);
    return size;
}
//----------------------------------------------------------------------------
