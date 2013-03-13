/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Renderable.inl
*
*/

//----------------------------------------------------------------------------
inline Renderable::PrimitiveType Renderable::GetPrimitiveType () const
{
    return mType;
}
//----------------------------------------------------------------------------
inline void Renderable::SetVertexFormat (VertexFormat* vformat)
{
    mVFormat = vformat;
}
//----------------------------------------------------------------------------
inline const VertexFormat* Renderable::GetVertexFormat () const
{
    return mVFormat;
}
//----------------------------------------------------------------------------
inline VertexFormat* Renderable::GetVertexFormat ()
{
    return mVFormat;
}
//----------------------------------------------------------------------------
inline void Renderable::SetVertexBuffer (VertexBuffer* vbuffer)
{
    mVBuffer = vbuffer;
}
//----------------------------------------------------------------------------
inline const VertexBuffer* Renderable::GetVertexBuffer () const
{
    return mVBuffer;
}
//----------------------------------------------------------------------------
inline VertexBuffer* Renderable::GetVertexBuffer ()
{
    return mVBuffer;
}
//----------------------------------------------------------------------------
inline void Renderable::SetIndexBuffer (IndexBuffer* ibuffer)
{
    mIBuffer = ibuffer;
}
//----------------------------------------------------------------------------
inline const IndexBuffer* Renderable::GetIndexBuffer () const
{
    return mIBuffer;
}
//----------------------------------------------------------------------------
inline IndexBuffer* Renderable::GetIndexBuffer ()
{
    return mIBuffer;
}
//----------------------------------------------------------------------------
inline const Bound& Renderable::GetModelBound () const
{
    return mModelBound;
}
//----------------------------------------------------------------------------
inline Bound& Renderable::GetModelBound ()
{
    return mModelBound;
}
//----------------------------------------------------------------------------
inline void Renderable::AddRenderUsage (RenderUsage usage)
{
	mRenderUsageBits |= 1<<usage;
}
//----------------------------------------------------------------------------
inline void Renderable::RemoveRenderUsage (RenderUsage usage)
{
	mRenderUsageBits &= ~(1<<usage);
}
//----------------------------------------------------------------------------
inline unsigned int Renderable::GetRenderUsage ()
{
	return mRenderUsageBits;
}
//----------------------------------------------------------------------------
inline void Renderable::SetTransparent (bool transparent)
{
	mSortIndex = (mSortIndex&0xffff0000)|(transparent?1:0);
}
//----------------------------------------------------------------------------
inline bool Renderable::IsTransparent () const
{
	return (mSortIndex&1); 
}
//----------------------------------------------------------------------------
inline unsigned int Renderable::GetSortIndex ()
{
	return mSortIndex;
}
//----------------------------------------------------------------------------
inline void Renderable::SetMaterialInstance (MaterialInstance* material)
{
    mMaterial = material;
}
//----------------------------------------------------------------------------
inline MaterialInstance* Renderable::GetMaterialInstance () const
{
    return mMaterial;
}
//----------------------------------------------------------------------------