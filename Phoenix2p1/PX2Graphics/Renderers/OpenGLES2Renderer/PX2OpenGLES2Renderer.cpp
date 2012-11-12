/*
*
* 文件名称	：	TdOpenGLES2Renderer.cpp
*
*/

#include "PX2Renderer.hpp"
#include "PX2OpenGLES2Mapping.hpp"
#include "PX2OpenGLES2RendererData.hpp"
#include "PX2Polypoint.hpp"
#include "PX2Polysegment.hpp"
#include "PX2TriFan.hpp"
#include "PX2TriStrip.hpp"
#include "PX2OpenGLES2MaterialPass.hpp"
#include "PX2OpenGLES2RendererInput.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Renderer::Renderer (RendererInput& input, int width, int height,
	Texture::Format colorFormat, Texture::Format depthStencilFormat,
	int numMultisamples)
{
	Initialize(width, height, colorFormat, depthStencilFormat,
		numMultisamples);

	mData = new0 RendererData();

	mData->mWindowHandle = (EGLNativeWindowType)input.mWindowHandle;
	mData->mDisplayType = (EGLNativeDisplayType)input.mRendererDC;

	EGLDisplay display = eglGetDisplay(input.mRendererDC);
	if (display == EGL_NO_DISPLAY)
	{
		assertion(false, "");
	}
	mData->mDisplay = display;

	EGLint majorVersion;
	EGLint minorVersion;
	if (!eglInitialize(display, &majorVersion, &minorVersion))
	{
		assertion(false, "");
	}

	 EGLint numConfigs;
	 if (!eglGetConfigs(display, NULL, 0, &numConfigs) )
	 {
		 assertion(false, "");
	 }

	 const EGLint attribList[] =
	 {
		 EGL_LEVEL,                0,
		 EGL_SURFACE_TYPE,         EGL_WINDOW_BIT,
		 EGL_RENDERABLE_TYPE,      EGL_OPENGL_ES2_BIT,
		 EGL_NATIVE_RENDERABLE,    EGL_FALSE,
		 EGL_DEPTH_SIZE,           16,
		 EGL_NONE,
	 };
	 EGLConfig config;
	 if (!eglChooseConfig(display, attribList, &config, 1, &numConfigs) )
	 {
		 assertion(false, "");
	 }
	 mData->mConfig = config;

	 EGLSurface surface = eglCreateWindowSurface(display, config, mData->mWindowHandle, NULL);
	 if (surface == EGL_NO_SURFACE)
	 {
		 assertion(false, "");
	 }
	 mData->mSurface = surface;

	 EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
	 EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
	 if (context == EGL_NO_CONTEXT)
	 {
		  assertion(false, "");
	 }
	 mData->mContext = context;

	 if (!eglMakeCurrent(display, surface, surface, context))
	 {
		 assertion(false, "");
	 }

	 // 设置缺省渲染状态和采样状态
	 mData->mCurrentRS.Initialize(mDefaultAlphaProperty, mDefaultCullProperty,
		 mDefaultDepthProperty, mDefaultOffsetProperty, mDefaultStencilProperty,
		 mDefaultWireProperty);
}
//----------------------------------------------------------------------------
Renderer::~Renderer ()
{
	if (mData)
	{
		delete0(mData);
		mData = 0;
	}
}
//----------------------------------------------------------------------------
// Pass 管理
//----------------------------------------------------------------------------
void Renderer::Bind (const MaterialPass *pass)
{
	if (mMaterialPasses.find(pass) == mMaterialPasses.end())
	{
		mMaterialPasses[pass] = new0 PdrMaterialPass(this, pass);
	}
}
//----------------------------------------------------------------------------
void Renderer::BindAll (const MaterialPass *pass)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Bind(pass);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Unbind (const MaterialPass *pass)
{
	MaterialPassMap::iterator iter = mMaterialPasses.find(pass);
	if (iter != mMaterialPasses.end())
	{
		PdrMaterialPass* pdrMaterialPass = iter->second;
		delete0(pdrMaterialPass);
		mMaterialPasses.erase(iter);
	}
}
//----------------------------------------------------------------------------
void Renderer::UnbindAll (const MaterialPass *pass)
{
	msMutex.Enter();

	RendererSet::iterator iter = msRenderers.begin();
	RendererSet::iterator end = msRenderers.end();
	for (/**/; iter != end; ++iter)
	{
		Renderer* renderer = *iter;
		renderer->Unbind(pass);
	}

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Renderer::Enable (const Renderable* renderable,
					   const MaterialInstance* instance, int index)
{
	PX2_UNUSED(renderable);
	PX2_UNUSED(instance);
	PX2_UNUSED(index);
}
//----------------------------------------------------------------------------
void Renderer::Disable (const Renderable* renderable,
						const MaterialInstance* instance, int index)
{
	PX2_UNUSED(renderable);
	PX2_UNUSED(instance);
	PX2_UNUSED(index);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// RenderProperty management.
//----------------------------------------------------------------------------
void Renderer::SetAlphaProperty (const AlphaProperty* AlphaProperty)
{
	if (!mOverrideAlphaProperty)
	{
		mAlphaProperty = AlphaProperty;
	}
	else	{
		mAlphaProperty = mOverrideAlphaProperty;
	}

	if (mAlphaProperty->BlendEnabled)
	{
		if (!mData->mCurrentRS.mAlphaBlendEnabled)
		{
			mData->mCurrentRS.mAlphaBlendEnabled = true;
			glEnable(GL_BLEND);
		}

		GLenum srcBlend = gOGLAlphaSrcBlend[mAlphaProperty->SrcBlend];
		GLenum dstBlend = gOGLAlphaDstBlend[mAlphaProperty->DstBlend];
		if (srcBlend != mData->mCurrentRS.mAlphaSrcBlend
			||  dstBlend != mData->mCurrentRS.mAlphaDstBlend)
		{
			mData->mCurrentRS.mAlphaSrcBlend = srcBlend;
			mData->mCurrentRS.mAlphaDstBlend = dstBlend;
			glBlendFunc(srcBlend, dstBlend);
		}

		if (mAlphaProperty->ConstantColor != mData->mCurrentRS.mBlendColor)
		{
			mData->mCurrentRS.mBlendColor = mAlphaProperty->ConstantColor;
			glBlendColor(
				mData->mCurrentRS.mBlendColor[0],
				mData->mCurrentRS.mBlendColor[1],
				mData->mCurrentRS.mBlendColor[1],
				mData->mCurrentRS.mBlendColor[3]);
		}
	}
	else
	{
		if (mData->mCurrentRS.mAlphaBlendEnabled)
		{
			mData->mCurrentRS.mAlphaBlendEnabled = false;
			glDisable(GL_BLEND);
		}
	}

	if (mAlphaProperty->CompareEnabled)
	{
		// 在shader中支持
	}
	else
	{
		// 在shader中支持
	}
}
//----------------------------------------------------------------------------
void Renderer::SetCullProperty (const CullProperty* cullState)
{
	if (!mOverrideCullProperty)
	{
		mCullProperty = cullState;
	}
	else
	{
		mCullProperty = mOverrideCullProperty;
	}

	if (mCullProperty->Enabled)
	{
		if (!mData->mCurrentRS.mCullEnabled)
		{
			mData->mCurrentRS.mCullEnabled = true;
			glEnable(GL_CULL_FACE);
			glFrontFace(GL_CCW);
		}

		bool order = mCullProperty->CCWOrder;
		if (mReverseCullOrder)
		{
			order = !order;
		}

		if (order != mData->mCurrentRS.mCCWOrder)
		{
			mData->mCurrentRS.mCCWOrder = order;
			if (mData->mCurrentRS.mCCWOrder)
			{
				glCullFace(GL_BACK);
			}
			else
			{
				glCullFace(GL_FRONT);
			}
		}
	}
	else
	{
		if (mData->mCurrentRS.mCullEnabled)
		{
			mData->mCurrentRS.mCullEnabled = false;
			glDisable(GL_CULL_FACE);
		}
	}
}
//----------------------------------------------------------------------------
void Renderer::SetDepthProperty (const DepthProperty* depthState)
{
	if (!mOverrideDepthProperty)
	{
		mDepthProperty = depthState;
	}
	else
	{
		mDepthProperty = mOverrideDepthProperty;
	}

	if (mDepthProperty->Enabled)
	{
		if (!mData->mCurrentRS.mDepthEnabled)
		{
			mData->mCurrentRS.mDepthEnabled = true;
			glEnable(GL_DEPTH_TEST);
		}

		GLenum compare = gOGLDepthCompare[mDepthProperty->Compare];
		if (compare != mData->mCurrentRS.mDepthCompareFunction)
		{
			mData->mCurrentRS.mDepthCompareFunction = compare;
			glDepthFunc(compare);
		}
	}
	else
	{
		if (mData->mCurrentRS.mDepthEnabled)
		{
			mData->mCurrentRS.mDepthEnabled = false;
			glDisable(GL_DEPTH_TEST);
		}
	}

	if (mDepthProperty->Writable)
	{
		if (!mData->mCurrentRS.mDepthWriteEnabled)
		{
			mData->mCurrentRS.mDepthWriteEnabled = true;
			glDepthMask(GL_TRUE);
		}
	}
	else
	{
		if (mData->mCurrentRS.mDepthWriteEnabled)
		{
			mData->mCurrentRS.mDepthWriteEnabled = false;
			glDepthMask(GL_FALSE);
		}
	}
}
//----------------------------------------------------------------------------
void Renderer::SetOffsetProperty (const OffsetProperty* offsetState)
{
	if (!mOverrideOffsetProperty)
	{
		mOffsetProperty = offsetState;
	}
	else
	{
		mOffsetProperty = mOverrideOffsetProperty;
	}

	if (mOffsetProperty->FillEnabled)
	{
		if (!mData->mCurrentRS.mFillEnabled)
		{
			mData->mCurrentRS.mFillEnabled = true;
			glEnable(GL_POLYGON_OFFSET_FILL);
		}
	}
	else
	{
		if (mData->mCurrentRS.mFillEnabled)
		{
			mData->mCurrentRS.mFillEnabled = false;
			glDisable(GL_POLYGON_OFFSET_FILL);
		}
	}

	// LineEnabled，PointEnabled不支持

	if (mOffsetProperty->Scale != mData->mCurrentRS.mOffsetScale
		||  mOffsetProperty->Bias != mData->mCurrentRS.mOffsetBias)
	{
		mData->mCurrentRS.mOffsetScale = mOffsetProperty->Scale;
		mData->mCurrentRS.mOffsetBias = mOffsetProperty->Bias;
		glPolygonOffset(mOffsetProperty->Scale, mOffsetProperty->Bias);
	}
}
//----------------------------------------------------------------------------
void Renderer::SetStencilProperty (const StencilProperty* stencilProperty)
{
	if (!mOverrideStencilProperty)
	{
		mStencilProperty = stencilProperty;
	}
	else
	{
		mStencilProperty = mOverrideStencilProperty;
	}

	if (mStencilProperty->Enabled)
	{
		if (!mData->mCurrentRS.mStencilEnabled)
		{
			mData->mCurrentRS.mStencilEnabled = true;
			glEnable(GL_STENCIL_TEST);
		}

		GLenum compare = gOGLStencilCompare[mStencilProperty->Compare];
		if (compare != mData->mCurrentRS.mStencilCompareFunction
			||  mStencilProperty->Reference != mData->mCurrentRS.mStencilReference
			||  mStencilProperty->Mask != mData->mCurrentRS.mStencilMask)
		{
			mData->mCurrentRS.mStencilCompareFunction = compare;
			mData->mCurrentRS.mStencilReference = mStencilProperty->Reference;
			mData->mCurrentRS.mStencilMask = mStencilProperty->Mask;
			glStencilFunc(compare, mStencilProperty->Reference,
				mStencilProperty->Mask);
		}

		if (mStencilProperty->WriteMask != mData->mCurrentRS.mStencilWriteMask)
		{
			mData->mCurrentRS.mStencilWriteMask = mStencilProperty->WriteMask;
			glStencilMask(mStencilProperty->WriteMask);
		}

		GLenum onFail = gOGLStencilOperation[mStencilProperty->OnFail];
		GLenum onZFail = gOGLStencilOperation[mStencilProperty->OnZFail];
		GLenum onZPass = gOGLStencilOperation[mStencilProperty->OnZPass];
		if (onFail != mData->mCurrentRS.mStencilOnFail
			||  onZFail != mData->mCurrentRS.mStencilOnZFail
			||  onZPass != mData->mCurrentRS.mStencilOnZPass)
		{
			mData->mCurrentRS.mStencilOnFail = onFail;
			mData->mCurrentRS.mStencilOnZFail = onZFail;
			mData->mCurrentRS.mStencilOnZPass = onZPass;
			glStencilOp(onFail, onZFail, onZPass);
		}
	}
	else
	{
		if (mData->mCurrentRS.mStencilEnabled)
		{
			mData->mCurrentRS.mStencilEnabled = false;
			glDisable(GL_STENCIL_TEST);
		}
	}
}
//----------------------------------------------------------------------------
void Renderer::SetWireProperty (const WireProperty* wireState)
{
	if (!mOverrideWireProperty)
	{
		mWireProperty = wireState;
	}
	else
	{
		mWireProperty = mOverrideWireProperty;
	}

	if (mWireProperty->Enabled)
	{
		if (!mData->mCurrentRS.mWireEnabled)
		{
			mData->mCurrentRS.mWireEnabled = true;

			// assertion
			assertion(false, "OpenglES2 doesn't support.");
		}
	}
	else
	{
		if (mData->mCurrentRS.mWireEnabled)
		{
			mData->mCurrentRS.mWireEnabled = false;

			// assertion
			assertion(false, "OpenglES2 doesn't support.");
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Viewport management.
//----------------------------------------------------------------------------
void Renderer::SetViewport (int xPosition, int yPosition, int width,
							int height)
{
	glViewport(xPosition, yPosition, width, height);
}
//----------------------------------------------------------------------------
void Renderer::GetViewport (int& xPosition, int& yPosition,
							int& width, int& height) const
{
	int param[4];
	glGetIntegerv(GL_VIEWPORT, param);

	xPosition = param[0];
	yPosition = param[1];
	width = param[2];
	height = param[3];
}
//----------------------------------------------------------------------------
void Renderer::SetDepthRange (float zMin, float zMax)
{
	PX2_UNUSED(zMin);
	PX2_UNUSED(zMax);

	assertion(false, "PowerSDK does't support.");
}
//----------------------------------------------------------------------------
void Renderer::GetDepthRange (float& zMin, float& zMax) const
{
	GLfloat param[2];
	glGetFloatv(GL_DEPTH_RANGE, param);

	zMin = (float)param[0];
	zMax = (float)param[1];
}
//----------------------------------------------------------------------------
void Renderer::Resize (int width, int height)
{
	mWidth = width;
	mHeight = height;

	int param[4];
	glGetIntegerv(GL_VIEWPORT, param);
	glViewport(param[0], param[1], width, height);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Support for clearing the color, depth, and stencil buffers.
//----------------------------------------------------------------------------
void Renderer::ClearColorBuffer ()
{
	glClearColor(mClearColor[0], mClearColor[1], mClearColor[2],
		mClearColor[3]);

	glClear(GL_COLOR_BUFFER_BIT);
}
//----------------------------------------------------------------------------
void Renderer::ClearDepthBuffer ()
{
	glClearDepthf((GLclampf)mClearDepth);

	glClear(GL_DEPTH_BUFFER_BIT);
}
//----------------------------------------------------------------------------
void Renderer::ClearStencilBuffer ()
{
	glClearStencil((GLint)mClearStencil);

	glClear(GL_STENCIL_BUFFER_BIT);
}
//----------------------------------------------------------------------------
void Renderer::ClearBuffers ()
{
	glClearColor(mClearColor[0], mClearColor[1], mClearColor[2],
		mClearColor[3]);

	glClearDepthf((GLclampf)mClearDepth);

	glClearStencil((GLint)mClearStencil);

	glClear(
		GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT |
		GL_STENCIL_BUFFER_BIT);
}
//----------------------------------------------------------------------------
void Renderer::ClearColorBuffer (int x, int y, int w, int h)
{
	glClearColor(mClearColor[0], mClearColor[1], mClearColor[2],
		mClearColor[3]);

	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, w, h);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void Renderer::ClearDepthBuffer (int x, int y, int w, int h)
{
	glClearDepthf((GLclampf)mClearDepth);

	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, w, h);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void Renderer::ClearStencilBuffer (int x, int y, int w, int h)
{
	glClearStencil((GLint)mClearStencil);

	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, w, h);
	glClear(GL_STENCIL_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void Renderer::ClearBuffers (int x, int y, int w, int h)
{
	glClearColor(mClearColor[0], mClearColor[1], mClearColor[2],
		mClearColor[3]);

	glClearDepthf(mClearDepth);

	glClearStencil((GLint)mClearStencil);

	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, w, h);
	glClear(
		GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT |
		GL_STENCIL_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void Renderer::DisplayColorBuffer ()
{
	 eglSwapBuffers(mData->mDisplay, mData->mSurface);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Support for masking color channels.
//----------------------------------------------------------------------------
void Renderer::SetColorMask (bool allowRed, bool allowGreen,
							 bool allowBlue, bool allowAlpha)
{
	mAllowRed = allowRed;
	mAllowGreen = allowGreen;
	mAllowBlue = allowBlue;
	mAllowAlpha = allowAlpha;

	GLboolean rMask = (mAllowRed ? 1 : 0);
	GLboolean gMask = (mAllowGreen ? 1 : 0);
	GLboolean bMask = (mAllowBlue ? 1 : 0);
	GLboolean aMask = (mAllowAlpha ? 1 : 0);
	glColorMask(rMask, gMask, bMask, aMask);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Support for predraw and postdraw semantics.
//----------------------------------------------------------------------------
bool Renderer::PreDraw ()
{
	return true;
}
//----------------------------------------------------------------------------
void Renderer::PostDraw ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Drawing routines.
//----------------------------------------------------------------------------
void Renderer::Draw (const unsigned char* screenBuffer, bool reflectY)
{
	if (!screenBuffer)
	{
		return;
	}

	assertion(false, "OpenglES does't support.");
}
//----------------------------------------------------------------------------
void Renderer::Draw (int x, int y, const Float4& color,
					 const std::string& message)
{
	PX2_UNUSED(x);
	PX2_UNUSED(y);
	PX2_UNUSED(color);
	PX2_UNUSED(message);

	//assertion(false, "OpenglES does't support.");
}
//----------------------------------------------------------------------------
#ifdef TD_QUERY_PIXEL_COUNT

#else
	#define PX2_BEGIN_QUERY(query)
	#define PX2_END_QUERY(query, numPixelsDrawn)
#endif
//----------------------------------------------------------------------------
void Renderer::DrawPrimitive (const Renderable* visual)
{
	Renderable::PrimitiveType type = visual->GetPrimitiveType();
	const VertexBuffer* vbuffer = visual->GetVertexBuffer();
	const IndexBuffer* ibuffer = visual->GetIndexBuffer();

	GLuint numPixelsDrawn;
	PX2_UNUSED(numPixelsDrawn);

	if (type == Renderable::PT_TRIMESH
		||  type == Renderable::PT_TRISTRIP
		||  type == Renderable::PT_TRIFAN)
	{
		int numVertices = vbuffer->GetNumElements();
		int numIndices = ibuffer->GetNumElements();
		if (numVertices > 0 && numIndices > 0)
		{
			GLenum indexType;
			const GLvoid* indexData;
			if (ibuffer->GetElementSize() == 2)
			{
				indexType = GL_UNSIGNED_SHORT;
				indexData = (unsigned short*)0 + ibuffer->GetOffset();
			}
			else  // size is 4
			{
				indexType = GL_UNSIGNED_INT;
				indexData = (unsigned int*)0 + ibuffer->GetOffset();
			}

			PX2_BEGIN_QUERY(query);

			// vertex data

			glDrawElements(gOGLPrimitiveType[type], numIndices, indexType, indexData);

			PX2_END_QUERY(query, numPixelsDrawn);
		}
	}
	else if (type == Renderable::PT_POLYSEGMENTS_CONTIGUOUS)
	{
		int numSegments = StaticCast<Polysegment>(visual)->GetNumSegments();
		if (numSegments > 0)
		{
			PX2_BEGIN_QUERY(query);

			glDrawArrays(GL_LINE_STRIP, 0, numSegments + 1);

			PX2_END_QUERY(query, numPixelsDrawn);
		}
	}
	else if (type == Renderable::PT_POLYSEGMENTS_DISJOINT)
	{
		int numSegments = StaticCast<Polysegment>(visual)->GetNumSegments();
		if (numSegments > 0)
		{
			PX2_BEGIN_QUERY(query);

			glDrawArrays(GL_LINES, 0, 2*numSegments);

			PX2_END_QUERY(query, numPixelsDrawn);
		}
	}
	else if (type == Renderable::PT_POLYPOINT)
	{
		int numPoints = StaticCast<Polypoint>(visual)->GetNumPoints();
		if (numPoints > 0)
		{
			PX2_BEGIN_QUERY(query);

			glDrawArrays(GL_POINTS, 0, numPoints);

			PX2_END_QUERY(query, numPixelsDrawn);
		}
	}
	else
	{
		assertion(false, "Invalid type.\n");
	}
}
//----------------------------------------------------------------------------
