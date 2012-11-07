/*
*
* 文件名称	：	PX2Movable.cpp
*
*/

#include "PX2Movable.hpp"
#include "PX2Culler.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Controlledable, Movable);
PX2_IMPLEMENT_STREAM(Movable);
PX2_IMPLEMENT_ABSTRACT_FACTORY(Movable);

//----------------------------------------------------------------------------
Movable::Movable ()
    :
    WorldTransformIsCurrent(false),
    WorldBoundIsCurrent(false),
    Culling(CULL_DYNAMIC),
    mParent(0)
{
}
//----------------------------------------------------------------------------
Movable::~Movable ()
{
	// mParent不需要被释放
}
//----------------------------------------------------------------------------
void Movable::Update (double applicationTime, bool initiator)
{
    UpdateWorldData(applicationTime);
    UpdateWorldBound();
    if (initiator)
    {
        PropagateBoundToRoot();
    }
}
//----------------------------------------------------------------------------
void Movable::OnAttach ()
{
}
//----------------------------------------------------------------------------
void Movable::OnDetach ()
{
}
//----------------------------------------------------------------------------
void Movable::UpdateWorldData (double applicationTime)
{
	// 更新控制器
    UpdateControllers(applicationTime);

    // 更新世界变幻
    if (!WorldTransformIsCurrent)
    {
        if (mParent)
        {
            WorldTransform = mParent->WorldTransform*LocalTransform;
        }
        else
        {
            WorldTransform = LocalTransform;
        }
    }
}
//----------------------------------------------------------------------------
void Movable::PropagateBoundToRoot ()
{
    if (mParent)
    {
        mParent->UpdateWorldBound();
        mParent->PropagateBoundToRoot();
    }
}
//----------------------------------------------------------------------------
void Movable::OnGetVisibleSet (Culler& culler, bool noCull)
{
    if (Culling == CULL_ALWAYS)
    {
        return;
    }

    if (Culling == CULL_NEVER)
    {
        noCull = true;
    }

    unsigned int savePlaneState = culler.GetPlaneState();
    if (noCull || culler.IsVisible(WorldBound))
    {
        GetVisibleSet(culler, noCull);
    }
    culler.SetPlaneState(savePlaneState);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称
//----------------------------------------------------------------------------
Object* Movable::GetObjectByName (const std::string& name)
{
    // mParent不用查找，否则会无限循环
    return Controlledable::GetObjectByName(name);
}
//----------------------------------------------------------------------------
void Movable::GetAllObjectsByName (const std::string& name,
    std::vector<Object*>& objects)
{
    // mParent不用查找，否则会无限循环
    Controlledable::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
Movable::Movable (LoadConstructor value)
    :
    Controlledable(value),
    WorldTransformIsCurrent(false),
    WorldBoundIsCurrent(false),
    Culling(CULL_DYNAMIC),
    mParent(0)
{
}
//----------------------------------------------------------------------------
void Movable::Load (InStream& source)
{
    PX2_BEGIN_DEBUG_STREAM_LOAD(source);

    Controlledable::Load(source);

    source.ReadAggregate(LocalTransform);
    source.ReadAggregate(WorldTransform);
    source.ReadBool(WorldTransformIsCurrent);
    source.ReadAggregate(WorldBound);
    source.ReadBool(WorldBoundIsCurrent);
    source.ReadEnum(Culling);

	// mParent不被保存，它会在Node::Link中调用Node::SetChild被设置。

    PX2_END_DEBUG_STREAM_LOAD(Movable, source);
}
//----------------------------------------------------------------------------
void Movable::Link (InStream& source)
{
	// mParent不被保存，它会在Node::Link中调用Node::SetChild被设置。

    Controlledable::Link(source);
}
//----------------------------------------------------------------------------
void Movable::PostLink ()
{
    Controlledable::PostLink();
}
//----------------------------------------------------------------------------
bool Movable::Register (OutStream& target) const
{
	// mParent不需要被注册

    return Controlledable::Register(target);
}
//----------------------------------------------------------------------------
void Movable::Save (OutStream& target) const
{
    PX2_BEGIN_DEBUG_STREAM_SAVE(target);

    Controlledable::Save(target);

    target.WriteAggregate(LocalTransform);
    target.WriteAggregate(WorldTransform);
    target.WriteBool(WorldTransformIsCurrent);
    target.WriteAggregate(WorldBound);
    target.WriteBool(WorldBoundIsCurrent);
    target.WriteEnum(Culling);

	// mParent不被保存，它会在Node::Link中调用Node::SetChild被设置。

    PX2_END_DEBUG_STREAM_SAVE(Movable, target);
}
//----------------------------------------------------------------------------
int Movable::GetStreamingSize () const
{
    int size = Controlledable::GetStreamingSize();
    size += LocalTransform.GetStreamingSize();;
    size += WorldTransform.GetStreamingSize();
    size += PX2_BOOLSIZE(WorldTransformIsCurrent);
    size += WorldBound.GetStreamingSize();
    size += PX2_BOOLSIZE(WorldBoundIsCurrent);
    size += PX2_ENUMSIZE(Culling);

    // mParent不被持久化

    return size;
}
//----------------------------------------------------------------------------
