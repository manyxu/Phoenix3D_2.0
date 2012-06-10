/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2OpenGLRendererData.hpp
*
* 版本		:	1.0 (2011/05/14)
*
* 作者		：	TimeX
*
*/

#ifndef PX2OPENGLRENDERERDATA_HPP
#define PX2OPENGLRENDERERDATA_HPP

#include "PX2Float4.hpp"
#include "PX2OpenGLBitmapFont.hpp"
#include "PX2OpenGLPrerequisites.hpp"

namespace PX2
{

	class AlphaProperty;
	class CullProperty;
	class DepthProperty;
	class OffsetProperty;
	class StencilProperty;
	class WireProperty;

	class RendererData
	{
	public:
#ifdef PX2_USE_TEXT_DISPLAY_LIST
		class DisplayListInfo
		{
		public:
			int mQuantity;  // number of display lists, input to glGenLists
			int mStart;     // start index, output from glGenLists
			int mBase;      // base index for glListBase
		};

		DisplayListInfo mFont;
#else
		void DrawCharacter (const BitmapFont& font, char c);
#endif

		// 保存当前的渲染状态，减少渲染状态的转换.
		class RenderState
		{
		public:
			RenderState ();
			void Initialize (const AlphaProperty* aProperty,
				const CullProperty* cProperty, const DepthProperty* dProperty,
				const OffsetProperty* oProperty, const StencilProperty* sProperty,
				const WireProperty* wProperty);

			// AlphaProperty
			bool mAlphaBlendEnabled;
			GLenum mAlphaSrcBlend;
			GLenum mAlphaDstBlend;
			bool mAlphaCompareEnabled;
			GLenum mCompareFunction;
			float mAlphaReference;
			Float4 mBlendColor;

			// CullProperty
			bool mCullEnabled;
			bool mCCWOrder;

			// DepthProperty
			bool mDepthEnabled;
			bool mDepthWriteEnabled;
			GLenum mDepthCompareFunction;

			// OffsetProperty
			bool mFillEnabled;
			bool mLineEnabled;
			bool mPointEnabled;
			float mOffsetScale;
			float mOffsetBias;

			// StencilProperty
			bool mStencilEnabled;
			GLenum mStencilCompareFunction;
			GLuint mStencilReference;
			GLuint mStencilMask;
			GLuint mStencilWriteMask;
			GLenum mStencilOnFail;
			GLenum mStencilOnZFail;
			GLenum mStencilOnZPass;

			// WireProperty
			bool mWireEnabled;
		};

		RenderState mCurrentRS;

		// Maintain current sampler states to avoid redundant state changes.
		enum
		{
			MAX_NUM_VSAMPLERS = 4,  // VSModel 3 has 4, VSModel 2 has 0.
			MAX_NUM_PSAMPLERS = 16  // PSModel 2 and PSModel 3 have 16.
		};

		class SamplerState
		{
		public:
			SamplerState ();

			// Get the state of the currently enabled texture.  This state appears
			// to be associated with the OpenGL texture object.  How does this
			// relate to the sampler state?  In my opinion, OpenGL needs to have
			// the sampler state separate from the texture object state.
			void GetCurrent (GLenum target);

			float mAnisotropy;
			float mLodBias;
			GLint mMagFilter;
			GLint mMinFilter;
			Float4 mBorderColor;
			GLint mWrap[3];
		};

		SamplerState mCurrentSS[MAX_NUM_PSAMPLERS];

		// Capabilities (queried at run time).
		int mMaxVShaderImages;
		int mMaxPShaderImages;
		int mMaxCombinedImages;
	};

}

#endif
