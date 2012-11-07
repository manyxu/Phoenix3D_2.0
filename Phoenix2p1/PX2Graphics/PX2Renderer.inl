/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Renderer.inl
*
*/

//----------------------------------------------------------------------------
inline int Renderer::GetWidth () const
{
	return mWidth;
}
//----------------------------------------------------------------------------
inline int Renderer::GetHeight () const
{
	return mHeight;
}
//----------------------------------------------------------------------------
inline Texture::Format Renderer::GetColorFormat () const
{
	return mColorFormat;
}
//----------------------------------------------------------------------------
inline Texture::Format Renderer::GetDepthStencilFormat () const
{
	return mDepthStencilFormat;
}
//----------------------------------------------------------------------------
inline int Renderer::GetNumMultisamples () const
{
	return mNumMultisamples;
}
//----------------------------------------------------------------------------
inline const AlphaProperty* Renderer::GetAlphaProperty () const
{
	return mAlphaProperty;
}
//----------------------------------------------------------------------------
inline const CullProperty* Renderer::GetCullProperty () const
{
	return mCullProperty;
}
//----------------------------------------------------------------------------
inline const DepthProperty* Renderer::GetDepthProperty () const
{
	return mDepthProperty;
}
//----------------------------------------------------------------------------
inline const OffsetProperty* Renderer::GetOffsetProperty () const
{
	return mOffsetProperty;
}
//----------------------------------------------------------------------------
inline const StencilProperty* Renderer::GetStencilProperty () const
{
	return mStencilProperty;
}
//----------------------------------------------------------------------------
inline const WireProperty* Renderer::GetWireProperty () const
{
	return mWireProperty;
}
//----------------------------------------------------------------------------
inline void Renderer::SetOverrideAlphaProperty (const AlphaProperty* alphaState)
{
	mOverrideAlphaProperty = alphaState;
	if (alphaState)
	{
		SetAlphaProperty(alphaState);
	}
	else
	{
		SetAlphaProperty(mDefaultAlphaProperty);
	}
}
//----------------------------------------------------------------------------
inline void Renderer::SetOverrideCullProperty (const CullProperty* cullState)
{
	mOverrideCullProperty = cullState;
	if (cullState)
	{
		SetCullProperty(cullState);
	}
	else
	{
		SetCullProperty(mDefaultCullProperty);
	}
}
//----------------------------------------------------------------------------
inline void Renderer::SetOverrideDepthProperty (const DepthProperty* depthState)
{
	mOverrideDepthProperty = depthState;
	if (depthState)
	{
		SetDepthProperty(depthState);
	}
	else
	{
		SetDepthProperty(mDefaultDepthProperty);
	}
}
//----------------------------------------------------------------------------
inline void Renderer::SetOverrideOffsetProperty (const OffsetProperty* offsetState)
{
	mOverrideOffsetProperty = offsetState;
	if (offsetState)
	{
		SetOffsetProperty(offsetState);
	}
	else
	{
		SetOffsetProperty(mDefaultOffsetProperty);
	}
}
//----------------------------------------------------------------------------
inline void Renderer::SetOverrideStencilProperty (const StencilProperty* stencilState)
{
	mOverrideStencilProperty = stencilState;
	if (stencilState)
	{
		SetStencilProperty(stencilState);
	}
	else
	{
		SetStencilProperty(mDefaultStencilProperty);
	}
}
//----------------------------------------------------------------------------
inline void Renderer::SetOverrideWireProperty (const WireProperty* wireState)
{
	mOverrideWireProperty = wireState;
	if (wireState)
	{
		SetWireProperty(wireState);
	}
	else
	{
		SetWireProperty(mDefaultWireProperty);
	}
}
//----------------------------------------------------------------------------
inline const AlphaProperty* Renderer::GetOverrideAlphaProperty () const
{
	return mOverrideAlphaProperty;
}
//----------------------------------------------------------------------------
inline const CullProperty* Renderer::GetOverrideCullProperty () const
{
	return mOverrideCullProperty;
}
//----------------------------------------------------------------------------
inline const DepthProperty* Renderer::GetOverrideDepthProperty () const
{
	return mOverrideDepthProperty;
}
//----------------------------------------------------------------------------
inline const OffsetProperty* Renderer::GetOverrideOffsetProperty () const
{
	return mOverrideOffsetProperty;
}
//----------------------------------------------------------------------------
inline const StencilProperty* Renderer::GetOverrideStencilProperty () const
{
	return mOverrideStencilProperty;
}
//----------------------------------------------------------------------------
inline const WireProperty* Renderer::GetOverrideWireProperty () const
{
	return mOverrideWireProperty;
}
//----------------------------------------------------------------------------
inline void Renderer::SetReverseCullOrder (bool reverseCullOrder)
{
	mReverseCullOrder = reverseCullOrder;
}
//----------------------------------------------------------------------------
inline bool Renderer::GetReverseCullOrder () const
{
	return mReverseCullOrder;
}
//----------------------------------------------------------------------------
inline void Renderer::SetCamera (Camera* camera)
{
	mCamera = camera;
}
//----------------------------------------------------------------------------
inline Camera* Renderer::GetCamera ()
{
	return mCamera;
}
//----------------------------------------------------------------------------
inline const Camera* Renderer::GetCamera () const
{
	return mCamera;
}
//----------------------------------------------------------------------------
inline const HMatrix& Renderer::GetViewMatrix () const
{
	return mCamera->GetViewMatrix();
}
//----------------------------------------------------------------------------
inline const HMatrix& Renderer::GetProjectionMatrix () const
{
	return mCamera->GetProjectionMatrix();
}
//----------------------------------------------------------------------------
inline const HMatrix& Renderer::GetPostProjectionMatrix () const
{
	return mCamera->GetPostProjectionMatrix();
}
//----------------------------------------------------------------------------
inline void Renderer::SetClearColor (const Float4& clearColor)
{
	mClearColor = clearColor;
}
//----------------------------------------------------------------------------
inline const Float4& Renderer::GetClearColor () const
{
	return mClearColor;
}
//----------------------------------------------------------------------------
inline void Renderer::SetClearDepth (float clearDepth)
{
	mClearDepth = clearDepth;
}
//----------------------------------------------------------------------------
inline float Renderer::GetClearDepth () const
{
	return mClearDepth;
}
//----------------------------------------------------------------------------
inline void Renderer::SetClearStencil (unsigned int clearStencil)
{
	mClearStencil = clearStencil;
}
//----------------------------------------------------------------------------
inline unsigned int Renderer::GetClearStencil () const
{
	return mClearStencil;
}
//----------------------------------------------------------------------------
inline void Renderer::GetColorMask (bool& allowRed, bool& allowGreen,
									bool& allowBlue, bool& allowAlpha) const
{
	allowRed = mAllowRed;
	allowGreen = mAllowGreen;
	allowBlue = mAllowBlue;
	allowAlpha = mAllowAlpha;
}
//----------------------------------------------------------------------------
inline bool Renderer::InTexture2DMap (const Texture2D* texture)
{
	return mTexture2Ds.find(texture) != mTexture2Ds.end();
}
//----------------------------------------------------------------------------
inline void Renderer::InsertInTexture2DMap (const Texture2D* texture,
											PdrTexture2D* platformTexture)
{
	mTexture2Ds[texture] = platformTexture;
}
//----------------------------------------------------------------------------