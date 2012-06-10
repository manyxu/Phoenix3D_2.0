/*
*
* 文件名称	：	PX2OpenGLRenderer.cpp
*
*/

#include "PX2Renderer.hpp"
#include "PX2OpenGLBitmapFont.hpp"
#include "PX2OpenGLMapping.hpp"
#include "PX2OpenGLRendererData.hpp"
#include "PX2Polypoint.hpp"
#include "PX2Polysegment.hpp"
#include "PX2TriFan.hpp"
#include "PX2TriStrip.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
// render property management.
//----------------------------------------------------------------------------
void Renderer::SetAlphaProperty (const AlphaProperty* alphaProperty)
{
	if (!mOverrideAlphaProperty)
	{
		mAlphaProperty = alphaProperty;
	}
	else
	{
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
		if (!mData->mCurrentRS.mAlphaCompareEnabled)
		{
			mData->mCurrentRS.mAlphaCompareEnabled = true;
			glEnable(GL_ALPHA_TEST);
		}

		GLenum compare = gOGLAlphaCompare[mAlphaProperty->Compare];
		float reference = mAlphaProperty->Reference;
		if (compare != mData->mCurrentRS.mCompareFunction
			||  reference != mData->mCurrentRS.mAlphaReference)
		{
			mData->mCurrentRS.mCompareFunction = compare;
			mData->mCurrentRS.mAlphaReference = reference;
			glAlphaFunc(compare, reference);
		}
	}
	else
	{
		if (mData->mCurrentRS.mAlphaCompareEnabled)
		{
			mData->mCurrentRS.mAlphaCompareEnabled = false;
			glDisable(GL_ALPHA_TEST);
		}
	}
}
//----------------------------------------------------------------------------
void Renderer::SetCullProperty (const CullProperty* cullProperty)
{
	if (!mOverrideCullProperty)
	{
		mCullProperty = cullProperty;
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
void Renderer::SetDepthProperty (const DepthProperty* depthProperty)
{
	if (!mOverrideDepthProperty)
	{
		mDepthProperty = depthProperty;
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
void Renderer::SetOffsetProperty (const OffsetProperty* offsetProperty)
{
	if (!mOverrideOffsetProperty)
	{
		mOffsetProperty = offsetProperty;
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

	if (mOffsetProperty->LineEnabled)
	{
		if (!mData->mCurrentRS.mLineEnabled)
		{
			mData->mCurrentRS.mLineEnabled = true;
			glEnable(GL_POLYGON_OFFSET_LINE);
		}
	}
	else
	{
		if (mData->mCurrentRS.mLineEnabled)
		{
			mData->mCurrentRS.mLineEnabled = false;
			glDisable(GL_POLYGON_OFFSET_LINE);
		}
	}

	if (mOffsetProperty->PointEnabled)
	{
		if (!mData->mCurrentRS.mPointEnabled)
		{
			mData->mCurrentRS.mPointEnabled = true;
			glEnable(GL_POLYGON_OFFSET_POINT);
		}
	}
	else
	{
		if (mData->mCurrentRS.mPointEnabled)
		{
			mData->mCurrentRS.mPointEnabled = false;
			glDisable(GL_POLYGON_OFFSET_POINT);
		}
	}

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
void Renderer::SetWireProperty (const WireProperty* wireProperty)
{
	if (!mOverrideWireProperty)
	{
		mWireProperty = wireProperty;
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
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
	}
	else
	{
		if (mData->mCurrentRS.mWireEnabled)
		{
			mData->mCurrentRS.mWireEnabled = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
	glDepthRange((GLclampd)zMin, (GLclampd)zMax);
}
//----------------------------------------------------------------------------
void Renderer::GetDepthRange (float& zMin, float& zMax) const
{
	GLclampd param[2];
	glGetDoublev(GL_DEPTH_RANGE, param);

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
// color, depth, stencil buffers
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
	glClearDepth((GLclampd)mClearDepth);

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

	glClearDepth((GLclampd)mClearDepth);

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
	glClearDepth((GLclampd)mClearDepth);

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

	glClearDepth((GLclampd)mClearDepth);

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
// predraw 和 postdraw 支持
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
// 绘制
//----------------------------------------------------------------------------
void Renderer::Draw (const unsigned char* screenBuffer, bool reflectY)
{
	if (!screenBuffer)
	{
		assertion(false, "Incoming screen buffer is null.\n");
		return;
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, (double)mWidth, 0.0, (double)mHeight, 0.0, 1.0);
	glRasterPos3f(0.0, 0.0, 0.0);
	if (!reflectY)
	{
		GLubyte bitmap[1] = {0};
		glBitmap(0, 0, 0.0f, 0.0f, 0.0f, (float)mHeight, bitmap);
	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	if (!reflectY)
	{
		glPixelZoom(1.0f, -1.0f);
	}

	glDrawPixels(mWidth, mHeight, GL_BGRA, GL_UNSIGNED_BYTE, screenBuffer);

	if (!reflectY)
	{
		glPixelZoom(1.0f, 1.0f);
	}
}
//----------------------------------------------------------------------------
void Renderer::Draw (int x, int y, const Float4& color,
					 const std::string& message)
{
	const char* text = message.c_str();
	assertion(text != 0, "Invalid message\n");
	int length = (int)strlen(text);

#ifdef PX2_USE_TEXT_DISPLAY_LIST
	GLint listBase;
	glGetIntegerv(GL_LIST_BASE, &listBase);
#endif

	// Switch to orthogonal view.
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-0.5f, mWidth - 0.5f, -0.5f, mHeight - 0.5f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// 置回到缺省渲染状态
	SetAlphaProperty(mDefaultAlphaProperty);
	SetCullProperty(mDefaultCullProperty);
	SetOffsetProperty(mDefaultOffsetProperty);
	SetStencilProperty(mDefaultStencilProperty);
	SetWireProperty(mDefaultWireProperty);

	mData->mCurrentRS.mDepthEnabled = false;
	glDisable(GL_DEPTH_TEST);

	// 设置文字颜色
	glColor4fv((const float*)color);

	// 使用右手坐标系绘制文字
	glRasterPos3i(x, mHeight - 1 - y, 0);
#ifdef PX2_USE_TEXT_DISPLAY_LIST
	glListBase(mData->mFont.mBase);
	glCallLists(length, GL_UNSIGNED_BYTE, text);
#else
	for (int i = 0; i < length; ++i)
	{
		mData->DrawCharacter(gVerdanaS16B0I0, text[i]);
	}
#endif

#ifdef PX2_RESET_STATE_AFTER_DRAW
	// 置回到缺省状态
	mData->mCurrentRS.mDepthEnabled = true;
	glEnable(GL_DEPTH_TEST);
#endif

	// Restore matrices.
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

#ifdef PX2_USE_TEXT_DISPLAY_LIST
	glListBase(listBase);
#endif
}
//----------------------------------------------------------------------------
#ifdef PX2_QUERY_PIXEL_COUNT
static GLuint BeginQuery ()
{
	GLuint query = 0;
	glGenQueriesARB(1, &query);
	glBeginQueryARB(GL_SAMPLES_PASSED_ARB, query);
	return query;
}

static GLuint EndQuery (GLuint query)
{
	glEndQueryARB(GL_SAMPLES_PASSED_ARB);
	GLint available = 0;
	while (!available)
	{
		// Wait until query finishes.
		glGetQueryObjectivARB(query, GL_QUERY_RESULT_AVAILABLE_ARB,
			&available);
	}

	GLuint numPixelsDrawn = 0;
	glGetQueryObjectuivARB(query, GL_QUERY_RESULT_ARB, &numPixelsDrawn);
	glDeleteQueriesARB(1, &query);
	return numPixelsDrawn;
}

#define PX2_BEGIN_QUERY(query) \
	GLuint query = BeginQuery()

#define PX2_END_QUERY(query, numPixelsDrawn) \
	numPixelsDrawn = EndQuery(query)
#else
#define PX2_BEGIN_QUERY(query)
#define PX2_END_QUERY(query, numPixelsDrawn)
#endif
//----------------------------------------------------------------------------
void Renderer::DrawPrimitive (const Renderable* renderable)
{
	Renderable::PrimitiveType type = renderable->GetPrimitiveType();
	const VertexBuffer* vbuffer = renderable->GetVertexBuffer();
	const IndexBuffer* ibuffer = renderable->GetIndexBuffer();

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

			glDrawRangeElements(gOGLPrimitiveType[type], 0, numVertices-1,
				numIndices, indexType, indexData);

			PX2_END_QUERY(query, numPixelsDrawn);
		}
	}
	else if (type == Renderable::PT_POLYSEGMENTS_CONTIGUOUS)
	{
		int numSegments = StaticCast<Polysegment>(renderable)
			->GetNumSegments();
		if (numSegments > 0)
		{
			PX2_BEGIN_QUERY(query);

			glDrawArrays(GL_LINE_STRIP, 0, numSegments + 1);

			PX2_END_QUERY(query, numPixelsDrawn);
		}
	}
	else if (type == Renderable::PT_POLYSEGMENTS_DISJOINT)
	{
		int numSegments = StaticCast<Polysegment>(renderable)
			->GetNumSegments();
		if (numSegments > 0)
		{
			PX2_BEGIN_QUERY(query);

			glDrawArrays(GL_LINES, 0, 2*numSegments);

			PX2_END_QUERY(query, numPixelsDrawn);
		}
	}
	else if (type == Renderable::PT_POLYPOINT)
	{
		int numPoints = StaticCast<Polypoint>(renderable)->GetNumPoints();
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
