/*
*
* 文件名称	：	PX2Renderer.cpp
*
*/

#include "PX2Renderer.hpp"
#include "PX2GlobalMaterial.hpp"

#ifdef PX2_USE_DX9
#include "PX2Dx9IndexBuffer.hpp"
#include "PX2Dx9PixelShader.hpp"
#include "PX2Dx9RenderTarget.hpp"
#include "PX2Dx9Shader.hpp"
#include "PX2Dx9Texture1D.hpp"
#include "PX2Dx9Texture2D.hpp"
#include "PX2Dx9Texture3D.hpp"
#include "PX2Dx9TextureCube.hpp"
#include "PX2Dx9VertexBuffer.hpp"
#include "PX2Dx9VertexFormat.hpp"
#include "PX2Dx9VertexShader.hpp"
#endif

#ifdef PX2_USE_OPENGLES2
#include "PX2OpenGLES2IndexBuffer.hpp"
#include "PX2OpenGLES2PixelShader.hpp"
#include "PX2OpenGLES2RendererData.hpp"
#include "PX2OpenGLES2Shader.hpp"
#include "PX2OpenGLES2Texture1D.hpp"
#include "PX2OpenGLES2Texture2D.hpp"
#include "PX2OpenGLES2Texture3D.hpp"
#include "PX2OpenGLES2TextureCube.hpp"
#include "PX2OpenGLES2RenderTarget.hpp"
#include "PX2OpenGLES2VertexBuffer.hpp"
#include "PX2OpenGLES2VertexFormat.hpp"
#include "PX2OpenGLES2VertexShader.hpp"
#endif

using namespace PX2;

Mutex Renderer::msMutex;
std::set<Renderer*> Renderer::msRenderers;

//----------------------------------------------------------------------------
void Renderer::Initialize (int width, int height, Texture::Format colorFormat,
						   Texture::Format depthStencilFormat, 
						   int numMultisamples)
{
	assertion(width > 0, "Width must be positive\n");

	assertion(height > 0, "Height must be positive\n");

	assertion(depthStencilFormat == Texture::TF_D24S8,
		"Only 24-bit depth and 8-bit stencil are currently supported\n");

	assertion(
		numMultisamples == 0 || numMultisamples == 2 || numMultisamples == 4,
		"The number of multisamples can be only 0, 2, or 4\n");

	mWidth = width;
	mHeight = height;
	mColorFormat = colorFormat;
	mDepthStencilFormat = depthStencilFormat;
	mNumMultisamples = numMultisamples;
	mDefaultAlphaProperty = new0 AlphaProperty();
	mDefaultCullProperty = new0 CullProperty();
	mDefaultDepthProperty = new0 DepthProperty();
	mDefaultOffsetProperty = new0 OffsetProperty();
	mDefaultStencilProperty = new0 StencilProperty();
	mDefaultWireProperty = new0 WireProperty();
	mAlphaProperty = mDefaultAlphaProperty;
	mCullProperty = mDefaultCullProperty;
	mDepthProperty = mDefaultDepthProperty;
	mOffsetProperty = mDefaultOffsetProperty;
	mStencilProperty = mDefaultStencilProperty;
	mWireProperty = mDefaultWireProperty;
	mReverseCullOrder = false;
	mOverrideAlphaProperty = 0;
	mOverrideCullProperty = 0;
	mOverrideDepthProperty = 0;
	mOverrideOffsetProperty = 0;
	mOverrideStencilProperty = 0;
	mOverrideWireProperty = 0;
	mCamera = 0;
	mClearColor = Float4(1.0f, 1.0f, 1.0f, 1.0f);
	mClearDepth = 1.0f;
	mClearStencil = 0;
	mAllowRed = true;
	mAllowGreen = true;
	mAllowBlue = true;
	mAllowAlpha = true;

	msMutex.Enter();
	msRenderers.insert(this);
	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Terminate ()
{
	delete0(mDefaultAlphaProperty);
	delete0(mDefaultCullProperty);
	delete0(mDefaultDepthProperty);
	delete0(mDefaultOffsetProperty);
	delete0(mDefaultStencilProperty);
	delete0(mDefaultWireProperty);

	// 释放所有资源
	DestroyAllVertexFormats();
	DestroyAllVertexBuffers();
	DestroyAllIndexBuffers();
	DestroyAllTexture1Ds();
	DestroyAllTexture2Ds();
	DestroyAllTexture3Ds();
	DestroyAllTextureCubes();
	DestroyAllRenderTargets();
	DestroyAllVertexShaders();
	DestroyAllPixelShaders();

	msMutex.Enter();
	msRenderers.erase(this);
	msMutex.Leave();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 顶点格式管理
//----------------------------------------------------------------------------
void Renderer::Bind (const VertexFormat* vformat)
{
	if (mVertexFormats.find(vformat) == mVertexFormats.end())
	{
		mVertexFormats[vformat] = new0 PdrVertexFormat(this, vformat);
	}
}
//----------------------------------------------------------------------------
void Renderer::BindAll (const VertexFormat* vformat)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Bind(vformat);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Unbind (const VertexFormat* vformat)
{
	VertexFormatMap::iterator iter = mVertexFormats.find(vformat);
	if (iter != mVertexFormats.end())
	{
		PdrVertexFormat* dxVFormat = iter->second;
		delete0(dxVFormat);
		mVertexFormats.erase(iter);
	}
}
//----------------------------------------------------------------------------
void Renderer::UnbindAll (const VertexFormat* vformat)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Unbind(vformat);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Enable (const VertexFormat* vformat)
{
	VertexFormatMap::iterator iter = mVertexFormats.find(vformat);
	PdrVertexFormat* pdrVFormat;
	if (iter != mVertexFormats.end())
	{
		pdrVFormat = iter->second;
	}
	else
	{
		pdrVFormat = new0 PdrVertexFormat(this, vformat);
		mVertexFormats[vformat] = pdrVFormat;
	}

	pdrVFormat->Enable(this);
}
//----------------------------------------------------------------------------
void Renderer::Disable (const VertexFormat* vformat)
{
	VertexFormatMap::iterator iter = mVertexFormats.find(vformat);
	if (iter != mVertexFormats.end())
	{
		PdrVertexFormat* pdrVFormat = iter->second;
		pdrVFormat->Disable(this);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Vertex buffer管理
//----------------------------------------------------------------------------
void Renderer::Bind (const VertexBuffer* vbuffer)
{
	if (mVertexBuffers.find(vbuffer) == mVertexBuffers.end())
	{
		mVertexBuffers[vbuffer] = new0 PdrVertexBuffer(this, vbuffer);
	}
}
//----------------------------------------------------------------------------
void Renderer::BindAll (const VertexBuffer* vbuffer)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Bind(vbuffer);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Unbind (const VertexBuffer* vbuffer)
{
	VertexBufferMap::iterator iter = mVertexBuffers.find(vbuffer);
	if (iter != mVertexBuffers.end())
	{
		PdrVertexBuffer* pdrVBuffer = iter->second;
		delete0(pdrVBuffer);
		mVertexBuffers.erase(iter);
	}
}
//----------------------------------------------------------------------------
void Renderer::UnbindAll (const VertexBuffer* vbuffer)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Unbind(vbuffer);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Enable (const VertexBuffer* vbuffer,
					   unsigned int streamIndex, unsigned int offset)
{
	VertexBufferMap::iterator iter = mVertexBuffers.find(vbuffer);
	PdrVertexBuffer* pdrVBuffer;
	if (iter != mVertexBuffers.end())
	{
		pdrVBuffer = iter->second;
	}
	else
	{
		pdrVBuffer = new0 PdrVertexBuffer(this, vbuffer);
		mVertexBuffers[vbuffer] = pdrVBuffer;
	}

	pdrVBuffer->Enable(this, vbuffer->GetElementSize(), streamIndex, offset);
}
//----------------------------------------------------------------------------
void Renderer::Disable (const VertexBuffer* vbuffer, unsigned int streamIndex)
{
	VertexBufferMap::iterator iter = mVertexBuffers.find(vbuffer);
	if (iter != mVertexBuffers.end())
	{
		PdrVertexBuffer* pdrVBuffer = iter->second;
		pdrVBuffer->Disable(this, streamIndex);
	}
}
//----------------------------------------------------------------------------
void* Renderer::Lock (const VertexBuffer* vbuffer, Buffer::Locking mode)
{
	VertexBufferMap::iterator iter = mVertexBuffers.find(vbuffer);
	PdrVertexBuffer* pdrVBuffer;
	if (iter != mVertexBuffers.end())
	{
		pdrVBuffer = iter->second;
	}
	else
	{
		pdrVBuffer = new0 PdrVertexBuffer(this, vbuffer);
		mVertexBuffers[vbuffer] = pdrVBuffer;
	}

	return pdrVBuffer->Lock(mode);
}
//----------------------------------------------------------------------------
void Renderer::Unlock (const VertexBuffer* vbuffer)
{
	VertexBufferMap::iterator iter = mVertexBuffers.find(vbuffer);
	if (iter != mVertexBuffers.end())
	{
		PdrVertexBuffer* pdrVBuffer = iter->second;
		pdrVBuffer->Unlock();
	}
}
//----------------------------------------------------------------------------
void Renderer::Update (const VertexBuffer* vbuffer)
{
	int numBytes = vbuffer->GetNumBytes();
	char* srcData = vbuffer->GetData();
	void* trgData = Lock(vbuffer, Buffer::BL_WRITE_ONLY);
	memcpy(trgData, srcData, numBytes);
	Unlock(vbuffer);
}
//----------------------------------------------------------------------------
void Renderer::UpdateAll (const VertexBuffer* vbuffer)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Update(vbuffer);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Index buffer管理
//----------------------------------------------------------------------------
void Renderer::Bind (const IndexBuffer* ibuffer)
{
	if (mIndexBuffers.find(ibuffer) == mIndexBuffers.end())
	{
		mIndexBuffers[ibuffer] = new0 PdrIndexBuffer(this, ibuffer);
	}
}
//----------------------------------------------------------------------------
void Renderer::BindAll (const IndexBuffer* ibuffer)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Bind(ibuffer);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Unbind (const IndexBuffer* ibuffer)
{
	IndexBufferMap::iterator iter = mIndexBuffers.find(ibuffer);
	if (iter != mIndexBuffers.end())
	{
		PdrIndexBuffer* pdrIBuffer = iter->second;
		delete0(pdrIBuffer);
		mIndexBuffers.erase(iter);
	}
}
//----------------------------------------------------------------------------
void Renderer::UnbindAll (const IndexBuffer* ibuffer)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Unbind(ibuffer);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Enable (const IndexBuffer* ibuffer)
{
	IndexBufferMap::iterator iter = mIndexBuffers.find(ibuffer);
	PdrIndexBuffer* pdrIBuffer;
	if (iter != mIndexBuffers.end())
	{
		pdrIBuffer = iter->second;
	}
	else
	{
		pdrIBuffer = new0 PdrIndexBuffer(this, ibuffer);
		mIndexBuffers[ibuffer] = pdrIBuffer;
	}

	pdrIBuffer->Enable(this);
}
//----------------------------------------------------------------------------
void Renderer::Disable (const IndexBuffer* ibuffer)
{
	IndexBufferMap::iterator iter = mIndexBuffers.find(ibuffer);
	if (iter != mIndexBuffers.end())
	{
		PdrIndexBuffer* pdrIBuffer = iter->second;
		pdrIBuffer->Disable(this);
	}
}
//----------------------------------------------------------------------------
void* Renderer::Lock (const IndexBuffer* ibuffer, Buffer::Locking mode)
{
	IndexBufferMap::iterator iter = mIndexBuffers.find(ibuffer);
	PdrIndexBuffer* pdrIBuffer;
	if (iter != mIndexBuffers.end())
	{
		pdrIBuffer = iter->second;
	}
	else
	{
		pdrIBuffer = new0 PdrIndexBuffer(this, ibuffer);
		mIndexBuffers[ibuffer] = pdrIBuffer;
	}

	return pdrIBuffer->Lock(mode);
}
//----------------------------------------------------------------------------
void Renderer::Unlock (const IndexBuffer* ibuffer)
{
	IndexBufferMap::iterator iter = mIndexBuffers.find(ibuffer);
	if (iter != mIndexBuffers.end())
	{
		PdrIndexBuffer* pdrIBuffer = iter->second;
		pdrIBuffer->Unlock();
	}
}
//----------------------------------------------------------------------------
void Renderer::Update (const IndexBuffer* ibuffer)
{
	int numBytes = ibuffer->GetNumBytes();
	char* srcData = ibuffer->GetData();
	void* trgData = Lock(ibuffer, Buffer::BL_WRITE_ONLY);
	memcpy(trgData, srcData, numBytes);
	Unlock(ibuffer);
}
//----------------------------------------------------------------------------
void Renderer::UpdateAll (const IndexBuffer* ibuffer)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Update(ibuffer);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Texture1D 管理
//----------------------------------------------------------------------------
void Renderer::Bind (const Texture1D* texture)
{
	if (mTexture1Ds.find(texture) == mTexture1Ds.end())
	{
		mTexture1Ds[texture] = new0 PdrTexture1D(this, texture);
	}
}
//----------------------------------------------------------------------------
void Renderer::BindAll (const Texture1D* texture)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Bind(texture);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Unbind (const Texture1D* texture)
{
	Texture1DMap::iterator iter = mTexture1Ds.find(texture);
	if (iter != mTexture1Ds.end())
	{
		PdrTexture1D* pdrTexture = iter->second;
		delete0(pdrTexture);
		mTexture1Ds.erase(iter);
	}
}
//----------------------------------------------------------------------------
void Renderer::UnbindAll (const Texture1D* texture)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Unbind(texture);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Enable (const Texture1D* texture, int textureUnit)
{
	Texture1DMap::iterator iter = mTexture1Ds.find(texture);
	PdrTexture1D* pdrTexture;
	if (iter != mTexture1Ds.end())
	{
		pdrTexture = iter->second;
	}
	else
	{
		pdrTexture = new0 PdrTexture1D(this, texture);
		mTexture1Ds[texture] = pdrTexture;
	}

	pdrTexture->Enable(this, textureUnit);
}
//----------------------------------------------------------------------------
void Renderer::Disable (const Texture1D* texture, int textureUnit)
{
	Texture1DMap::iterator iter = mTexture1Ds.find(texture);
	if (iter != mTexture1Ds.end())
	{
		PdrTexture1D* pdrTexture = iter->second;
		pdrTexture->Disable(this, textureUnit);
	}
}
//----------------------------------------------------------------------------
void* Renderer::Lock (const Texture1D* texture, int level,
					  Buffer::Locking mode)
{
	Texture1DMap::iterator iter = mTexture1Ds.find(texture);
	PdrTexture1D* pdrTexture;
	if (iter != mTexture1Ds.end())
	{
		pdrTexture = iter->second;
	}
	else
	{
		pdrTexture = new0 PdrTexture1D(this, texture);
		mTexture1Ds[texture] = pdrTexture;
	}

	return pdrTexture->Lock(level, mode);
}
//----------------------------------------------------------------------------
void Renderer::Unlock (const Texture1D* texture, int level)
{
	Texture1DMap::iterator iter = mTexture1Ds.find(texture);
	if (iter != mTexture1Ds.end())
	{
		PdrTexture1D* pdrTexture = iter->second;
		pdrTexture->Unlock(level);
	}
}
//----------------------------------------------------------------------------
void Renderer::Update (const Texture1D* texture, int level)
{
	int numBytes = texture->GetNumLevelBytes(level);
	char* srcData = texture->GetData(level);
	void* trgData = Lock(texture, level, Buffer::BL_WRITE_ONLY);
	memcpy(trgData, srcData, numBytes);
	Unlock(texture, level);
}
//----------------------------------------------------------------------------
void Renderer::UpdateAll (const Texture1D* texture, int level)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Update(texture, level);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Texture2D 管理
//----------------------------------------------------------------------------
void Renderer::Bind (const Texture2D* texture)
{
	if (mTexture2Ds.find(texture) == mTexture2Ds.end())
	{
		mTexture2Ds[texture] = new0 PdrTexture2D(this, texture);
	}
}
//----------------------------------------------------------------------------
void Renderer::BindAll (const Texture2D* texture)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Bind(texture);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Unbind (const Texture2D* texture)
{
	Texture2DMap::iterator iter = mTexture2Ds.find(texture);
	if (iter != mTexture2Ds.end())
	{
		PdrTexture2D* pdrTexture = iter->second;
		delete0(pdrTexture);
		mTexture2Ds.erase(iter);
	}
}
//----------------------------------------------------------------------------
void Renderer::UnbindAll (const Texture2D* texture)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Unbind(texture);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Enable (const Texture2D* texture, int textureUnit)
{
	Texture2DMap::iterator iter = mTexture2Ds.find(texture);
	PdrTexture2D* pdrTexture;
	if (iter != mTexture2Ds.end())
	{
		pdrTexture = iter->second;
	}
	else
	{
		pdrTexture = new0 PdrTexture2D(this, texture);
		mTexture2Ds[texture] = pdrTexture;
	}

	pdrTexture->Enable(this, textureUnit);
}
//----------------------------------------------------------------------------
void Renderer::Disable (const Texture2D* texture, int textureUnit)
{
	Texture2DMap::iterator iter = mTexture2Ds.find(texture);
	if (iter != mTexture2Ds.end())
	{
		PdrTexture2D* pdrTexture = iter->second;
		pdrTexture->Disable(this, textureUnit);
	}
}
//----------------------------------------------------------------------------
void* Renderer::Lock (const Texture2D* texture, int level,
					  Buffer::Locking mode)
{
	Texture2DMap::iterator iter = mTexture2Ds.find(texture);
	PdrTexture2D* pdrTexture;
	if (iter != mTexture2Ds.end())
	{
		pdrTexture = iter->second;
	}
	else
	{
		pdrTexture = new0 PdrTexture2D(this, texture);
		mTexture2Ds[texture] = pdrTexture;
	}

	return pdrTexture->Lock(level, mode);
}
//----------------------------------------------------------------------------
void Renderer::Unlock (const Texture2D* texture, int level)
{
	Texture2DMap::iterator iter = mTexture2Ds.find(texture);
	if (iter != mTexture2Ds.end())
	{
		PdrTexture2D* pdrTexture = iter->second;
		pdrTexture->Unlock(level);
	}
}
//----------------------------------------------------------------------------
void Renderer::Update (const Texture2D* texture, int level)
{
	int numBytes = texture->GetNumLevelBytes(level);
	char* srcData = texture->GetData(level);
	void* trgData = Lock(texture, level, Buffer::BL_WRITE_ONLY);
	memcpy(trgData, srcData, numBytes);
	Unlock(texture, level);
}
//----------------------------------------------------------------------------
void Renderer::UpdateAll (const Texture2D* texture, int level)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Update(texture, level);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Texture3D 管理
//----------------------------------------------------------------------------
void Renderer::Bind (const Texture3D* texture)
{
	if (mTexture3Ds.find(texture) == mTexture3Ds.end())
	{
		mTexture3Ds[texture] = new0 PdrTexture3D(this, texture);
	}
}
//----------------------------------------------------------------------------
void Renderer::BindAll (const Texture3D* texture)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Bind(texture);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Unbind (const Texture3D* texture)
{
	Texture3DMap::iterator iter = mTexture3Ds.find(texture);
	if (iter != mTexture3Ds.end())
	{
		PdrTexture3D* pdrTexture = iter->second;
		delete0(pdrTexture);
		mTexture3Ds.erase(iter);
	}
}
//----------------------------------------------------------------------------
void Renderer::UnbindAll (const Texture3D* texture)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Unbind(texture);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Enable (const Texture3D* texture, int textureUnit)
{
	Texture3DMap::iterator iter = mTexture3Ds.find(texture);
	PdrTexture3D* pdrTexture;
	if (iter != mTexture3Ds.end())
	{
		pdrTexture = iter->second;
	}
	else
	{
		pdrTexture = new0 PdrTexture3D(this, texture);
		mTexture3Ds[texture] = pdrTexture;
	}

	pdrTexture->Enable(this, textureUnit);
}
//----------------------------------------------------------------------------
void Renderer::Disable (const Texture3D* texture, int textureUnit)
{
	Texture3DMap::iterator iter = mTexture3Ds.find(texture);
	if (iter != mTexture3Ds.end())
	{
		PdrTexture3D* pdrTexture = iter->second;
		pdrTexture->Disable(this, textureUnit);
	}
}
//----------------------------------------------------------------------------
void* Renderer::Lock (const Texture3D* texture, int level,
					  Buffer::Locking mode)
{
	Texture3DMap::iterator iter = mTexture3Ds.find(texture);
	PdrTexture3D* pdrTexture;
	if (iter != mTexture3Ds.end())
	{
		pdrTexture = iter->second;
	}
	else
	{
		pdrTexture = new0 PdrTexture3D(this, texture);
		mTexture3Ds[texture] = pdrTexture;
	}

	return pdrTexture->Lock(level, mode);
}
//----------------------------------------------------------------------------
void Renderer::Unlock (const Texture3D* texture, int level)
{
	Texture3DMap::iterator iter = mTexture3Ds.find(texture);
	if (iter != mTexture3Ds.end())
	{
		PdrTexture3D* pdrTexture = iter->second;
		pdrTexture->Unlock(level);
	}
}
//----------------------------------------------------------------------------
void Renderer::Update (const Texture3D* texture, int level)
{
	int numBytes = texture->GetNumLevelBytes(level);
	char* srcData = texture->GetData(level);
	void* trgData = Lock(texture, level, Buffer::BL_WRITE_ONLY);
	memcpy(trgData, srcData, numBytes);
	Unlock(texture, level);
}
//----------------------------------------------------------------------------
void Renderer::UpdateAll (const Texture3D* texture, int level)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Update(texture, level);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// TextureCube 管理
//----------------------------------------------------------------------------
void Renderer::Bind (const TextureCube* texture)
{
	if (mTextureCubes.find(texture) == mTextureCubes.end())
	{
		mTextureCubes[texture] = new0 PdrTextureCube(this, texture);
	}
}
//----------------------------------------------------------------------------
void Renderer::BindAll (const TextureCube* texture)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Bind(texture);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Unbind (const TextureCube* texture)
{
	TextureCubeMap::iterator iter = mTextureCubes.find(texture);
	if (iter != mTextureCubes.end())
	{
		PdrTextureCube* pdrTexture = iter->second;
		delete0(pdrTexture);
		mTextureCubes.erase(iter);
	}
}
//----------------------------------------------------------------------------
void Renderer::UnbindAll (const TextureCube* texture)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Unbind(texture);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Enable (const TextureCube* texture, int textureUnit)
{
	TextureCubeMap::iterator iter = mTextureCubes.find(texture);
	PdrTextureCube* pdrTexture;
	if (iter != mTextureCubes.end())
	{
		pdrTexture = iter->second;
	}
	else
	{
		pdrTexture = new0 PdrTextureCube(this, texture);
		mTextureCubes[texture] = pdrTexture;
	}

	pdrTexture->Enable(this, textureUnit);
}
//----------------------------------------------------------------------------
void Renderer::Disable (const TextureCube* texture, int textureUnit)
{
	TextureCubeMap::iterator iter = mTextureCubes.find(texture);
	if (iter != mTextureCubes.end())
	{
		PdrTextureCube* pdrTexture = iter->second;
		pdrTexture->Disable(this, textureUnit);
	}
}
//----------------------------------------------------------------------------
void* Renderer::Lock (const TextureCube* texture, int face, int level,
					  Buffer::Locking mode)
{
	TextureCubeMap::iterator iter = mTextureCubes.find(texture);
	PdrTextureCube* pdrTexture;
	if (iter != mTextureCubes.end())
	{
		pdrTexture = iter->second;
	}
	else
	{
		pdrTexture = new0 PdrTextureCube(this, texture);
		mTextureCubes[texture] = pdrTexture;
	}

	return pdrTexture->Lock(face, level, mode);
}
//----------------------------------------------------------------------------
void Renderer::Unlock (const TextureCube* texture, int face, int level)
{
	TextureCubeMap::iterator iter = mTextureCubes.find(texture);
	if (iter != mTextureCubes.end())
	{
		PdrTextureCube* pdrTexture = iter->second;
		pdrTexture->Unlock(face, level);
	}
}
//----------------------------------------------------------------------------
void Renderer::Update (const TextureCube* texture, int face, int level)
{
	int numBytes = texture->GetNumLevelBytes(level);
	char* srcData = texture->GetData(face, level);
	void* trgData = Lock(texture, face, level, Buffer::BL_WRITE_ONLY);
	memcpy(trgData, srcData, numBytes);
	Unlock(texture, face, level);
}
//----------------------------------------------------------------------------
void Renderer::UpdateAll (const TextureCube* texture, int face, int level)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Update(texture, face, level);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Render target 管理
//----------------------------------------------------------------------------
void Renderer::Bind (const RenderTarget* renderTarget)
{
	if (mRenderTargets.find(renderTarget) == mRenderTargets.end())
	{
		mRenderTargets[renderTarget] =
			new0 PdrRenderTarget(this, renderTarget);
	}
}
//----------------------------------------------------------------------------
void Renderer::BindAll (const RenderTarget* renderTarget)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Bind(renderTarget);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Unbind (const RenderTarget* renderTarget)
{
	RenderTargetMap::iterator iter = mRenderTargets.find(renderTarget);
	if (iter != mRenderTargets.end())
	{
		PdrRenderTarget* pdrRenderTarget = iter->second;
		delete0(pdrRenderTarget);
		mRenderTargets.erase(iter);
	}
}
//----------------------------------------------------------------------------
void Renderer::UnbindAll (const RenderTarget* renderTarget)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Unbind(renderTarget);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Enable (const RenderTarget* renderTarget)
{
	RenderTargetMap::iterator iter = mRenderTargets.find(renderTarget);
	PdrRenderTarget* pdrRenderTarget;
	if (iter != mRenderTargets.end())
	{
		pdrRenderTarget = iter->second;
	}
	else
	{
		pdrRenderTarget = new0 PdrRenderTarget(this, renderTarget);
		mRenderTargets[renderTarget] = pdrRenderTarget;
	}

	pdrRenderTarget->Enable(this);
}
//----------------------------------------------------------------------------
void Renderer::Disable (const RenderTarget* renderTarget)
{
	RenderTargetMap::iterator iter = mRenderTargets.find(renderTarget);
	if (iter != mRenderTargets.end())
	{
		PdrRenderTarget* pdrRenderTarget = iter->second;
		pdrRenderTarget->Disable(this);
	}
}
//----------------------------------------------------------------------------
void Renderer::ReadColor (int i, const RenderTarget* renderTarget,
						  Texture2D*& texture)
{
	RenderTargetMap::iterator iter = mRenderTargets.find(renderTarget);
	if (iter != mRenderTargets.end())
	{
		PdrRenderTarget* pdrRenderTarget = iter->second;
		pdrRenderTarget->ReadColor(i, this, texture);
	}
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Vertex shader 管理
//----------------------------------------------------------------------------
void Renderer::Bind (const VertexShader* vshader)
{
	if (mVertexShaders.find(vshader) == mVertexShaders.end())
	{
		mVertexShaders[vshader] = new0 PdrVertexShader(this, vshader);
	}
}
//----------------------------------------------------------------------------
void Renderer::BindAll (const VertexShader* vshader)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Bind(vshader);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Unbind (const VertexShader* vshader)
{
	VertexShaderMap::iterator iter = mVertexShaders.find(vshader);
	if (iter != mVertexShaders.end())
	{
		PdrVertexShader* pdrVShader = iter->second;
		delete0(pdrVShader);
		mVertexShaders.erase(iter);
	}
}
//----------------------------------------------------------------------------
void Renderer::UnbindAll (const VertexShader* vshader)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Unbind(vshader);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Enable (const VertexShader* vshader,
					   const ShaderParameters* parameters)
{
	VertexShaderMap::iterator iter = mVertexShaders.find(vshader);
	PdrVertexShader* pdrVShader;
	if (iter != mVertexShaders.end())
	{
		pdrVShader = iter->second;
	}
	else
	{
		pdrVShader = new0 PdrVertexShader(this, vshader);
		mVertexShaders[vshader] = pdrVShader;
	}

	pdrVShader->Enable(this, vshader, parameters);
}
//----------------------------------------------------------------------------
void Renderer::Disable (const VertexShader* vshader,
						const ShaderParameters* parameters)
{
	VertexShaderMap::iterator iter = mVertexShaders.find(vshader);
	if (iter != mVertexShaders.end())
	{
		PdrVertexShader* pdrVShader = iter->second;
		pdrVShader->Disable(this, vshader, parameters);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Pixel shader 管理
//----------------------------------------------------------------------------
void Renderer::Bind (const PixelShader* pshader)
{
	if (mPixelShaders.find(pshader) == mPixelShaders.end())
	{
		mPixelShaders[pshader] = new0 PdrPixelShader(this, pshader);
	}
}
//----------------------------------------------------------------------------
void Renderer::BindAll (const PixelShader* pshader)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Bind(pshader);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Unbind (const PixelShader* pshader)
{
	PixelShaderMap::iterator iter = mPixelShaders.find(pshader);
	if (iter != mPixelShaders.end())
	{
		PdrPixelShader* pdrPShader = iter->second;
		delete0(pdrPShader);
		mPixelShaders.erase(iter);
	}
}
//----------------------------------------------------------------------------
void Renderer::UnbindAll (const PixelShader* pshader)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Unbind(pshader);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Enable (const PixelShader* pshader,
					   const ShaderParameters* parameters)
{
	PixelShaderMap::iterator iter = mPixelShaders.find(pshader);
	PdrPixelShader* pdrPShader;
	if (iter != mPixelShaders.end())
	{
		pdrPShader = iter->second;
	}
	else
	{
		pdrPShader = new0 PdrPixelShader(this, pshader);
		mPixelShaders[pshader] = pdrPShader;
	}

	pdrPShader->Enable(this, pshader, parameters);
}
//----------------------------------------------------------------------------
void Renderer::Disable (const PixelShader* pshader,
						const ShaderParameters* parameters)
{
	PixelShaderMap::iterator iter = mPixelShaders.find(pshader);
	if (iter != mPixelShaders.end())
	{
		PdrPixelShader* pdrPShader = iter->second;
		pdrPShader->Disable(this, pshader, parameters);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 计算选择射线
//----------------------------------------------------------------------------
bool Renderer::GetPickRay (int x, int y, APoint& origin, AVector& direction)
const
{
	if (!mCamera)
	{
		return false;
	}

	// Get the current viewport and test whether (x,y) is in it.
	int viewX, viewY, viewW, viewH;
	GetViewport(viewX, viewY, viewW, viewH);
	if (x < viewX || x > viewX + viewW || y < viewY || y > viewY + viewH)
	{
		return false;
	}

	// Get the [0,1]^2-normalized coordinates of (x,y).
	float r = ((float)(x - viewX))/(float)viewW;
	float u = ((float)(y - viewY))/(float)viewH;

	// Get the relative coordinates in [rmin,rmax]x[umin,umax].
	float rBlend = (1.0f - r)*mCamera->GetRMin() + r*mCamera->GetRMax();
	float uBlend = (1.0f - u)*mCamera->GetUMin() + u*mCamera->GetUMax();

	if (mCamera->IsPerspective())
	{
		origin = mCamera->GetPosition();
		direction = mCamera->GetDMin()*mCamera->GetDVector() +
			rBlend*mCamera->GetRVector() + uBlend*mCamera->GetUVector();
		direction.Normalize();
	}
	else
	{
		origin = mCamera->GetPosition() + rBlend*mCamera->GetRVector() +
			uBlend*mCamera->GetUVector();
		direction = mCamera->GetDVector();
	}

	return true;
}
//----------------------------------------------------------------------------
Vector2f Renderer::PointWorldToViewPort (APoint &point, bool *isInBack)
{
	HMatrix matProjView = GetProjectionMatrix() * GetViewMatrix();
	HPoint hPoint(point.X(), point.Y(), point.Z(), point.W());
	HPoint tempPoint = matProjView * hPoint;

	if (isInBack)
	{
		if (tempPoint.Z() <= 0)
			*isInBack = true;
		else
			*isInBack = false;
	}

	float wInv = 1.0f / tempPoint.W();

	//投影坐标范围为[-1,1]要变成[0,1]
	Vector2f screenPoint;
	screenPoint.X() = (1.0f + tempPoint.X()*wInv)/2.0f;
	screenPoint.Y() = (1.0f + tempPoint.Y()*wInv)/2.0f;

	//投影坐标范围为[0,1]要变成视口内坐标
	int viewX, viewY, viewW, viewH;
	GetViewport(viewX, viewY, viewW, viewH);

	screenPoint.X() = viewX + screenPoint.X()*viewW;
	screenPoint.Y() = viewY + screenPoint.Y()*viewH;

	return screenPoint;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 绘制入口点
//----------------------------------------------------------------------------
void Renderer::Draw (const VisibleSet& visibleSet, GlobalMaterial* globalMaterial)
{
	if (!globalMaterial)
	{
		const int numVisible = visibleSet.GetNumVisible();
		for (int i = 0; i < numVisible; ++i)
		{
			const Renderable* renderable = (const Renderable*)visibleSet.GetVisible(i);
			const MaterialInstance* instance =
				renderable->GetMaterialInstance();
			Draw(renderable, instance);
		}
	}
	else
	{
		globalMaterial->Draw(this, visibleSet);
	}
}
//----------------------------------------------------------------------------
void Renderer::Draw (const Renderable* renderable)
{
	const MaterialInstance* instance = renderable->GetMaterialInstance();
	Draw(renderable, instance);
}
//----------------------------------------------------------------------------
void Renderer::Draw (const Renderable* renderable,
					 const MaterialInstance* instance)
{
	if (!renderable)
	{
		assertion(false, "The renderable must exist.\n");
		return;
	}

	if (!instance)
	{
		assertion(false, "The renderable must have an material instance.\n");
		return;
	}

	const VertexFormat* vformat = renderable->GetVertexFormat();
	const VertexBuffer* vbuffer = renderable->GetVertexBuffer();
	const IndexBuffer* ibuffer = renderable->GetIndexBuffer();

	// OpenGL渲染器需要vertex buffer在顶点格式之前先设置。Directx9没有这
	// 样的需要。
	Enable(vbuffer);
	Enable(vformat);
	if (ibuffer)
	{
		Enable(ibuffer);
	}

	const int numPasses = instance->GetNumPasses();
	for (int i = 0; i < numPasses; ++i)
	{
		// 激活Pass
		Enable(renderable, instance, i);

		// 绘制几何图形
		DrawPrimitive(renderable);

		// 取消激活Pass
		Disable(renderable, instance, i);

#ifdef PX2_RESET_STATE_AFTER_DRAW
		// 恢复到缺省渲染状态
		SetAlphaProperty(mDefaultAlphaProperty);
		SetCullProperty(mDefaultCullProperty);
		SetDepthProperty(mDefaultDepthProperty);
		SetOffsetProperty(mDefaultOffsetProperty);
		SetStencilProperty(mDefaultStencilProperty);
		SetWireProperty(mDefaultWireProperty);
#endif
	}

	if (ibuffer)
	{
		Disable(ibuffer);
	}

	Disable(vformat);
	Disable(vbuffer);
}
//----------------------------------------------------------------------------
void Renderer::DestroyAllVertexFormats ()
{
	VertexFormatMap::iterator iter = mVertexFormats.begin();
	VertexFormatMap::iterator end = mVertexFormats.end();
	for (/**/; iter != end; ++iter)
	{
		PdrVertexFormat* pdrVFormat = iter->second;
		delete0(pdrVFormat);
	}
}
//----------------------------------------------------------------------------
void Renderer::DestroyAllVertexBuffers ()
{
	VertexBufferMap::iterator iter = mVertexBuffers.begin();
	VertexBufferMap::iterator end = mVertexBuffers.end();
	for (/**/; iter != end; ++iter)
	{
		PdrVertexBuffer* pdrVBuffer = iter->second;
		delete0(pdrVBuffer);
	}
}
//----------------------------------------------------------------------------
void Renderer::DestroyAllIndexBuffers ()
{
	IndexBufferMap::iterator iter = mIndexBuffers.begin();
	IndexBufferMap::iterator end = mIndexBuffers.end();
	for (/**/; iter != end; ++iter)
	{
		PdrIndexBuffer* pdrIBuffer = iter->second;
		delete0(pdrIBuffer);
	}
}
//----------------------------------------------------------------------------
void Renderer::DestroyAllTexture1Ds ()
{
	Texture1DMap::iterator iter = mTexture1Ds.begin();
	Texture1DMap::iterator end = mTexture1Ds.end();
	for (/**/; iter != end; ++iter)
	{
		PdrTexture1D* pdrTexture = iter->second;
		delete0(pdrTexture);
	}
}
//----------------------------------------------------------------------------
void Renderer::DestroyAllTexture2Ds ()
{
	Texture2DMap::iterator iter = mTexture2Ds.begin();
	Texture2DMap::iterator end = mTexture2Ds.end();
	for (/**/; iter != end; ++iter)
	{
		PdrTexture2D* pdrTexture = iter->second;
		delete0(pdrTexture);
	}
}
//----------------------------------------------------------------------------
void Renderer::DestroyAllTexture3Ds ()
{
	Texture3DMap::iterator iter = mTexture3Ds.begin();
	Texture3DMap::iterator end = mTexture3Ds.end();
	for (/**/; iter != end; ++iter)
	{
		PdrTexture3D* pdrTexture = iter->second;
		delete0(pdrTexture);
	}
}
//----------------------------------------------------------------------------
void Renderer::DestroyAllTextureCubes ()
{
	TextureCubeMap::iterator iter = mTextureCubes.begin();
	TextureCubeMap::iterator end = mTextureCubes.end();
	for (/**/; iter != end; ++iter)
	{
		PdrTextureCube* pdrTexture = iter->second;
		delete0(pdrTexture);
	}
}
//----------------------------------------------------------------------------
void Renderer::DestroyAllRenderTargets ()
{
	RenderTargetMap::iterator iter = mRenderTargets.begin();
	RenderTargetMap::iterator end = mRenderTargets.end();
	for (/**/; iter != end; ++iter)
	{
		PdrRenderTarget* pdrRenderTarget = iter->second;
		delete0(pdrRenderTarget);
	}
}
//----------------------------------------------------------------------------
void Renderer::DestroyAllVertexShaders ()
{
	VertexShaderMap::iterator iter = mVertexShaders.begin();
	VertexShaderMap::iterator end = mVertexShaders.end();
	for (/**/; iter != end; ++iter)
	{
		PdrVertexShader* pdrVShader = iter->second;
		delete0(pdrVShader);
	}
}
//----------------------------------------------------------------------------
void Renderer::DestroyAllPixelShaders ()
{
	PixelShaderMap::iterator iter = mPixelShaders.begin();
	PixelShaderMap::iterator end = mPixelShaders.end();
	for (/**/; iter != end; ++iter)
	{
		PdrPixelShader* pdrPShader = iter->second;
		delete0(pdrPShader);
	}
}
//----------------------------------------------------------------------------
PdrVertexFormat* Renderer::GetResource (const VertexFormat* vformat)
{
	VertexFormatMap::iterator iter = mVertexFormats.find(vformat);
	if (iter != mVertexFormats.end())
	{
		return iter->second;
	}
	return 0;
}
//----------------------------------------------------------------------------
PdrVertexBuffer* Renderer::GetResource (const VertexBuffer* vbuffer)
{
	VertexBufferMap::iterator iter = mVertexBuffers.find(vbuffer);
	if (iter != mVertexBuffers.end())
	{
		return iter->second;
	}
	return 0;
}
//----------------------------------------------------------------------------
PdrIndexBuffer* Renderer::GetResource (const IndexBuffer* ibuffer)
{
	IndexBufferMap::iterator iter = mIndexBuffers.find(ibuffer);
	if (iter != mIndexBuffers.end())
	{
		return iter->second;
	}
	return 0;
}
//----------------------------------------------------------------------------
PdrTexture1D* Renderer::GetResource (const Texture1D* texture)
{
	Texture1DMap::iterator iter = mTexture1Ds.find(texture);
	if (iter != mTexture1Ds.end())
	{
		return iter->second;
	}
	return 0;
}
//----------------------------------------------------------------------------
PdrTexture2D* Renderer::GetResource (const Texture2D* texture)
{
	Texture2DMap::iterator iter = mTexture2Ds.find(texture);
	if (iter != mTexture2Ds.end())
	{
		return iter->second;
	}
	return 0;
}
//----------------------------------------------------------------------------
PdrTexture3D* Renderer::GetResource (const Texture3D* texture)
{
	Texture3DMap::iterator iter = mTexture3Ds.find(texture);
	if (iter != mTexture3Ds.end())
	{
		return iter->second;
	}
	return 0;
}
//----------------------------------------------------------------------------
PdrTextureCube* Renderer::GetResource (const TextureCube* texture)
{
	TextureCubeMap::iterator iter = mTextureCubes.find(texture);
	if (iter != mTextureCubes.end())
	{
		return iter->second;
	}
	return 0;
}
//----------------------------------------------------------------------------
PdrRenderTarget* Renderer::GetResource (const RenderTarget* renderTarget)
{
	RenderTargetMap::iterator iter = mRenderTargets.find(renderTarget);
	if (iter != mRenderTargets.end())
	{
		return iter->second;
	}
	return 0;
}
//----------------------------------------------------------------------------
PdrVertexShader* Renderer::GetResource (const VertexShader* vshader)
{
	VertexShaderMap::iterator iter = mVertexShaders.find(vshader);
	if (iter != mVertexShaders.end())
	{
		return iter->second;
	}
	return 0;
}
//----------------------------------------------------------------------------
PdrPixelShader* Renderer::GetResource (const PixelShader* pshader)
{
	PixelShaderMap::iterator iter = mPixelShaders.find(pshader);
	if (iter != mPixelShaders.end())
	{
		return iter->second;
	}
	return 0;
}
//----------------------------------------------------------------------------
PdrMaterialPass* Renderer::GetResource (const MaterialPass* pass)
{
	MaterialPassMap::iterator iter = mMaterialPasses.find(pass);
	if (iter != mMaterialPasses.end())
	{
		return iter->second;
	}
	return 0;
}
//----------------------------------------------------------------------------
