/*
*
* 文件名称	：	PX2OpenGLRendererData.cpp
*
*/

#include "PX2OpenGLRendererData.hpp"
#include "PX2OpenGLMapping.hpp"
using namespace PX2;

#ifndef PX2_USE_TEXT_DISPLAY_LIST
//----------------------------------------------------------------------------
// Support for non-display-list fonts.
//----------------------------------------------------------------------------
void RendererData::DrawCharacter (const BitmapFont& font, char c)
{
	const BitmapFontChar* bfc = font.mCharacters[(unsigned int)c];

	// Save unpack state.
	GLint swapBytes, lsbFirst, rowLength, skipRows, skipPixels, alignment;
	glGetIntegerv(GL_UNPACK_SWAP_BYTES, &swapBytes);
	glGetIntegerv(GL_UNPACK_LSB_FIRST, &lsbFirst);
	glGetIntegerv(GL_UNPACK_ROW_LENGTH, &rowLength);
	glGetIntegerv(GL_UNPACK_SKIP_ROWS, &skipRows);
	glGetIntegerv(GL_UNPACK_SKIP_PIXELS, &skipPixels);
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);

	glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
	glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBitmap(bfc->mXSize, bfc->mYSize, (float)bfc->mXOrigin,
		(float)bfc->mYOrigin, (float)bfc->mXSize, 0.0f,
		(const GLubyte*)bfc->mBitmap);

	// Restore unpack state.
	glPixelStorei(GL_UNPACK_SWAP_BYTES, swapBytes);
	glPixelStorei(GL_UNPACK_LSB_FIRST, lsbFirst);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, rowLength);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, skipRows);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, skipPixels);
	glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
}
//----------------------------------------------------------------------------
#endif

//----------------------------------------------------------------------------
// Render state information to avoid redundant state changes.
//----------------------------------------------------------------------------
RendererData::RenderState::RenderState ()
{
	// Initialization must be deferred until an OpenGL context has been
	// created.
}
//----------------------------------------------------------------------------
void RendererData::RenderState::Initialize (const AlphaProperty* aProperty,
											const CullProperty* cProperty,
											const DepthProperty* dProperty,
											const OffsetProperty* oProperty, 
											const StencilProperty* sProperty,
											const WireProperty* wProperty)
{
	// AlphaProperty
	mAlphaBlendEnabled = aProperty->BlendEnabled;
	mAlphaSrcBlend = gOGLAlphaSrcBlend[aProperty->SrcBlend];
	mAlphaDstBlend = gOGLAlphaDstBlend[aProperty->DstBlend];
	mAlphaCompareEnabled = aProperty->CompareEnabled;
	mCompareFunction = gOGLAlphaCompare[aProperty->Compare];
	mAlphaReference = aProperty->Reference;
	mBlendColor = aProperty->ConstantColor;

	mAlphaBlendEnabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
	glBlendFunc(mAlphaSrcBlend, GL_ONE_MINUS_SRC_ALPHA);
	mAlphaCompareEnabled ? glEnable(GL_ALPHA_TEST) : glDisable(GL_ALPHA_TEST);
	glAlphaFunc(mCompareFunction, mAlphaReference);
	glBlendColor(mBlendColor[0], mBlendColor[1], mBlendColor[2],
		mBlendColor[3]);

	// CullProperty
	mCullEnabled = cProperty->Enabled;
	mCCWOrder = cProperty->CCWOrder;

	mCullEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(mCCWOrder ? GL_BACK : GL_FRONT);

	// DepthProperty
	mDepthEnabled = dProperty->Enabled;
	mDepthWriteEnabled = dProperty->Writable;
	mDepthCompareFunction = gOGLDepthCompare[dProperty->Compare];

	mDepthEnabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	glDepthMask(mDepthWriteEnabled ? GL_TRUE : GL_FALSE);
	glDepthFunc(mDepthCompareFunction);

	// OffsetProperty
	mFillEnabled = oProperty->FillEnabled;
	mLineEnabled = oProperty->LineEnabled;
	mPointEnabled = oProperty->PointEnabled;
	mOffsetScale = oProperty->Scale;
	mOffsetBias = oProperty->Bias;

	mFillEnabled ? glEnable(GL_POLYGON_OFFSET_FILL) :
		glDisable(GL_POLYGON_OFFSET_FILL);
	mLineEnabled ? glEnable(GL_POLYGON_OFFSET_LINE) :
		glDisable(GL_POLYGON_OFFSET_LINE);
	mPointEnabled ? glEnable(GL_POLYGON_OFFSET_POINT) :
		glDisable(GL_POLYGON_OFFSET_POINT);
	glPolygonOffset(mOffsetScale, mOffsetBias);

	// StencilProperty
	mStencilEnabled = sProperty->Enabled;
	mStencilCompareFunction = gOGLStencilCompare[sProperty->Compare];
	mStencilReference = sProperty->Reference;
	mStencilMask = sProperty->Mask;
	mStencilWriteMask = sProperty->WriteMask;
	mStencilOnFail = gOGLStencilOperation[sProperty->OnFail];
	mStencilOnZFail = gOGLStencilOperation[sProperty->OnZFail];
	mStencilOnZPass = gOGLStencilOperation[sProperty->OnZPass];

	mStencilEnabled ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
	glStencilFunc(mStencilCompareFunction, mStencilReference, mStencilMask);
	glStencilMask(mStencilWriteMask);
	glStencilOp(mStencilOnFail, mStencilOnZFail, mStencilOnZPass);

	// WireProperty
	mWireEnabled = wProperty->Enabled;

	glPolygonMode(GL_FRONT_AND_BACK, mWireEnabled ? GL_LINE : GL_FILL);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 保存当前的渲染状态，减少渲染状态的转换
//----------------------------------------------------------------------------
RendererData::SamplerState::SamplerState ()
:
mBorderColor(0.0f, 0.0f, 0.0f, 0.0f)
{
	mAnisotropy = 1.0f;
	mLodBias = 0.0f;
	mMagFilter = GL_LINEAR;
	mMinFilter = GL_NEAREST_MIPMAP_LINEAR;
	mWrap[0] = GL_REPEAT;
	mWrap[1] = GL_REPEAT;
	mWrap[2] = GL_REPEAT;
}
//----------------------------------------------------------------------------
void RendererData::SamplerState::GetCurrent (GLenum target)
{
	glGetTexParameterfv(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, &mAnisotropy);
	glGetTexEnvfv(GL_TEXTURE_FILTER_CONTROL, GL_TEXTURE_LOD_BIAS, &mLodBias);
	glGetTexParameteriv(target, GL_TEXTURE_MAG_FILTER, &mMagFilter);
	glGetTexParameteriv(target, GL_TEXTURE_MIN_FILTER, &mMinFilter);
	glGetTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, mBorderColor);
	glGetTexParameteriv(target, GL_TEXTURE_WRAP_S, &mWrap[0]);
	glGetTexParameteriv(target, GL_TEXTURE_WRAP_T, &mWrap[1]);
	glGetTexParameteriv(target, GL_TEXTURE_WRAP_R, &mWrap[2]);
}
//----------------------------------------------------------------------------
