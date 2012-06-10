/*
*
* 文件名称	：	PX2WglRenderer.cpp
*
*/

#include "PX2Renderer.hpp"
#include "PX2WGLRendererData.hpp"
#include "PX2WGLRendererInput.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Renderer::Renderer (RendererInput& input, int width, int height,
					Texture::Format colorFormat, Texture::Format depthStencilFormat,
					int numMultisamples)
{
	Initialize(width, height, colorFormat, depthStencilFormat,
		numMultisamples);

	WglRendererData* data = new0 WglRendererData();
	mData = data;
	data->mWindowHandle = input.mWindowHandle;
	data->mWindowDC = ::GetDC(input.mWindowHandle);

	// 获取窗口dc
	input.mRendererDC = data->mWindowDC;

	// 选择像素格式
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags =
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_GENERIC_ACCELERATED;
	pfd.dwFlags |= PFD_DOUBLEBUFFER;

	// 创建32-bit RGBA
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;

	// 创建24-8 depthstencil
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;

	// 设置rendering context的像素格式
	bool firstTime = (input.mPixelFormat == 0 ? true : false);
	if (firstTime)
	{
		// 第一次创建,选择一个像素格式
		input.mPixelFormat = ChoosePixelFormat(data->mWindowDC, &pfd);
		if (input.mPixelFormat == 0)
		{
			assertion(false, "ChoosePixelFormat failed\n");
			return;
		}
	}

	BOOL success = SetPixelFormat(data->mWindowDC, input.mPixelFormat, &pfd);
	if (!success)
	{
		assertion(false, "SetPixelFormat failed\n");
		return;
	}

	// 创建OpenGL context
	data->mWindowRC = wglCreateContext(data->mWindowDC);
	if (!data->mWindowRC)
	{
		assertion(false, "wglCreateContext failed\n");
		return;
	}

	// Activate the context.
	success = wglMakeCurrent(data->mWindowDC, data->mWindowRC);
	if (!success)
	{
		assertion(false, "wglMakeCurrent failed\n");
		return;
	}

	if (firstTime)
	{
		// Load the function pointers for the OpenGL extensions.  This only
		// needs to occur once.  If you want a file to be created that stores
		// the OpenGL driver information, change the input filename to a
		// valid string; for example, "OpenGLDriverInfo.txt".
		//const char* infoFile = "OpenGLDriverInfo.txt";
		const char* infoFile = 0;
		GTInitWGL(infoFile);
	}

	if (input.mDisableVerticalSync)
	{
		// 关闭垂直同步
		wglSwapIntervalEXT(0);
	}

#ifdef PX2_USE_TEXT_DISPLAY_LIST
	// Use the system font as default.
	int firstChar = int(' ');
	data->mFont.mQuantity = 127 - firstChar;
	data->mFont.mStart = glGenLists(data->mFont.mQuantity);
	data->mFont.mBase = data->mFont.mStart - firstChar;
	SelectObject(data->mWindowDC, GetStockObject(SYSTEM_FONT)); 
	wglUseFontBitmaps(data->mWindowDC, firstChar, data->mFont.mQuantity,
		data->mFont.mStart);
#endif

	// 设置shader版本
	VertexShader::SetProfile(VertexShader::VP_ARBVP1);
	PixelShader::SetProfile(PixelShader::PP_ARBFP1);

	// 性能
	data->mMaxVShaderImages = 0;
	data->mMaxPShaderImages = 0;
	data->mMaxCombinedImages = 0;
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
		&data->mMaxVShaderImages);
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,
		&data->mMaxPShaderImages);
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
		&data->mMaxCombinedImages);

	// 设置缺省状态
	data->mCurrentRS.Initialize(mDefaultAlphaProperty, mDefaultCullProperty,
		mDefaultDepthProperty, mDefaultOffsetProperty, mDefaultStencilProperty,
		mDefaultWireProperty);
}
//----------------------------------------------------------------------------
Renderer::~Renderer ()
{
	WglRendererData* data = (WglRendererData*)mData;

#ifdef PX2_USE_TEXT_DISPLAY_LIST
	glDeleteLists(data->mFont.mStart, data->mFont.mQuantity);
#endif

	if (data->mWindowRC)
	{
		wglDeleteContext(data->mWindowRC);
	}

	if (data->mWindowDC)
	{
		::ReleaseDC(data->mWindowHandle, data->mWindowDC);
	}

	delete0(data);
	Terminate();
}
//----------------------------------------------------------------------------
void Renderer::DisplayColorBuffer ()
{
	WglRendererData* data = (WglRendererData*)mData;
	SwapBuffers(data->mWindowDC);
}
//----------------------------------------------------------------------------
