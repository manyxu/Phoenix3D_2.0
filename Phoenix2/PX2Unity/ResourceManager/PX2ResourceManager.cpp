/*
*
* 文件名称	：	PX2ResourceManager.cpp
*
*/

#include "PX2ResourceManager.hpp"
#include "PX2StringHelp.hpp"

// DevIL
#include "IL/il.h"
#include "IL/ilu.h"

#pragma warning(disable : 4312)

using namespace PX2;
using namespace std;

#if defined(WIN32)
//----------------------------------------------------------------------------
#include <windows.h>
//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------
static unsigned int WINAPI ThreadLoadFun (void *data)
{
	ResourceManager *manager = (ResourceManager*)data;

	if (manager)
		return manager->RunLoadingThread();

	return 0;
}
//----------------------------------------------------------------------------
ResourceManager::ResourceManager ()
:
mLoadingThread(0),
mTimeCounter(0),
mQuitLoading(false),
mDDSKeepCompressed(true)
{
	// Init Devil
	ilInit();
	iluInit();
	ilEnable(IL_FILE_OVERWRITE);
	ilEnable(IL_CONV_PAL);

	StartThread();
}
//----------------------------------------------------------------------------
ResourceManager::~ResourceManager ()
{
#if defined(WIN32)
	::ReleaseSemaphore(mLoadingDequeSemaphore, 1, NULL);
#endif

	if (mLoadingThread)
	{
		delete0(mLoadingThread);
		mLoadingThread = NULL;
	}
#if defined(WIN32)
	::CloseHandle(mLoadingDequeSemaphore);
#endif

	// Shutdown Devil
	ilShutDown();
}
//----------------------------------------------------------------------------
Object *ResourceManager::BlockLoad (const std::string &filename)
{
	if (filename == "")
	{
		assertion(false, "filename must not be null");
		return 0;
	}

	LoadRecord &loadRec = InsertRecord(filename);

	LoadTheRecord(loadRec);

	return loadRec.Obj;
}
//----------------------------------------------------------------------------
ResourceManager::ResHandle ResourceManager::BackgroundLoad (
	const std::string &filename)
{
	LoadRecord &rec = InsertRecord(filename);

	{
		ScopedCS scopedCS(&mLoadRecordMutex);

		if (LS_UNLOADED == rec.State)
		{
			ScopedCS scopedCSLoadingDeque(&mLoadingDequeMutex);
			rec.State = LS_LOADQUE;
			mLoadingDeque.push_front(&rec);

#if defined(WIN32)	
			bool b = (::ReleaseSemaphore(mLoadingDequeSemaphore, 1, NULL)==1);
			assertion(b, "ReleaseSemaphore failed.");
			PX2_UNUSED(b);
#endif

		}
	}

	return (ResHandle)&rec;
}
//----------------------------------------------------------------------------
Object *ResourceManager::CheckRes (ResHandle handle)
{
	LoadRecord &rec = *((LoadRecord *)handle);

	if (LS_LOADED == rec.State)
	{
		return rec.Obj;
	}

	return 0;
}
//----------------------------------------------------------------------------
ResourceManager::LoadState ResourceManager::GetResLoadState (ResHandle handle)
{
	LoadRecord &rec = *(LoadRecord *)handle;
	
	return rec.State;
}
//----------------------------------------------------------------------------
void ResourceManager::GarbageCollect ()
{

}
//----------------------------------------------------------------------------
unsigned int ResourceManager::RunLoadingThread ()
{
	LoadRecord *rec = 0;

	while (!mQuitLoading)
	{
#if defined(WIN32)	
		::WaitForSingleObject(mLoadingDequeSemaphore, INFINITE);
#endif

		if (mQuitLoading)
			break;

		{
			ScopedCS scopedCS(&mLoadingDequeMutex);

			if (mLoadingDeque.empty())
				continue;

			rec = mLoadingDeque.front();
			mLoadingDeque.pop_front();
		}

		LoadTheRecord(*rec);
	}

	return 0;
}
//----------------------------------------------------------------------------
ResourceManager::LoadRecord &ResourceManager::InsertRecord (const std::string &filename)
{
	ScopedCS scopeCS(&mResTableMutex);

	ResTable::iterator it = mResTable.find(filename);
	if (it != mResTable.end())
	{
		it->second.LastTouchedTime = mTimeCounter;
		
		return it->second;
	}

	LoadRecord rec;
	mResTable.insert(std::pair<std::string, LoadRecord>(filename, rec));

	LoadRecord &rRec = mResTable[filename];

	rRec.Filename = filename;
	rRec.State = LS_UNLOADED;
	rRec.LastTouchedTime = mTimeCounter;

	return rRec;
}
//----------------------------------------------------------------------------
void ResourceManager::LoadTheRecord (LoadRecord &rec)
{
	bool needLoad = false;
	{
		ScopedCS scopedCS(&mLoadRecordMutex);

		if (LS_UNLOADED == rec.State || LS_LOADQUE == rec.State)
		{
			rec.State = LS_LOADING;
			needLoad = true;
		}
	}

	if (needLoad)
	{
		rec.Obj = LoadObject (rec.Filename);
		rec.LastTouchedTime = mTimeCounter;
		rec.State = LS_LOADED;
	}

	// 可能其他线程正在加载这个资源
	while (rec.State != LS_LOADED)
	{
#if defined(WIN32)
		Sleep(10);
#endif
	}
}
//----------------------------------------------------------------------------
Object *ResourceManager::LoadObject (const std::string &filename)
{
	Object *obj = 0;

	string::size_type pos = filename.find(".");
	if (pos == string::npos)
		return 0;

	std::string outPath;
	std::string outBaseName;
	std::string outExtention;
	StringHelp::SplitFullFilename(filename, outPath, outBaseName, outExtention);

	if ("pxtf" == outExtention || "PXTF" == outExtention)
	{
		obj = Texture2D::LoadPXtf(filename);
		if (obj)
		{
			obj->SetResourcePath(outBaseName+"."+outExtention);
		}

		return obj;
	}
	else if (("dds" == outExtention||"DDS" == outExtention) && mDDSKeepCompressed)
	{
		obj = LoadTextureFromDDS(filename);
		if (obj)
		{
			obj->SetResourcePath(outBaseName+"."+outExtention);
		}

		return obj;
	}
	else if ("jpg"==outExtention  || "JPG"==outExtention 
		|| "png"==outExtention || "PNG"==outExtention 
		|| "tga"==outExtention || "TGA"==outExtention 
		|| "bmp"==outExtention || "BMP"==outExtention 
		|| "dds"==outExtention || "DDS"==outExtention)
	{
		obj = LoadTextureFromOtherImagefile(filename);
		if (obj)
		{
			obj->SetResourcePath(outBaseName+"."+outExtention);
		}

		return obj;
	}

	// 引擎文件
	InStream inStream;

	if (inStream.Load(filename))
	{
		obj = inStream.GetObjectAt(0);
	}

	return obj;
}
//----------------------------------------------------------------------------
Texture2D *ResourceManager::LoadTextureFromOtherImagefile (
	const std::string& filename)
{
	ILuint image;
	ilGenImages(1, &image);
	ilBindImage(image);

	bool revert = false;

	std::string outPath;
	std::string outBaseName;
	std::string outExtention;
	StringHelp::SplitFullFilename(filename, outPath, outBaseName, outExtention);

	ILenum type = IL_TYPE_UNKNOWN;

	if ("jpg" == outExtention || "JPG" == outExtention)
	{
		type = IL_JPG;
		revert = true;
	}
	else if ("png" == outExtention || "PNG" == outExtention)
	{
		type = IL_PNG;
		revert = true;
	}
	else if ("dds" == outExtention || "DDS" == outExtention)
	{
		type = IL_DDS;
		revert = true;
	}
	else if ("tga" == outExtention || "TGA" == outExtention)
	{
		type = IL_TGA;
	}
	else if ("bmp" == outExtention || "BMP" == outExtention)
	{
		type = IL_BMP;
	}
	else
	{
		assertion(false, "format is not supported.");
		return false;
	}

	int bufferSize;
	char* buffer = 0;
	if (!FileIO::Load(filename, true, bufferSize, buffer))
	{
		return 0;
	}

	ILboolean b = ilLoadL(type, buffer, bufferSize);

	if (buffer)
	{
		delete1(buffer);
	}

	if (!b)
	{
		assertion(false, "ilLoadL texture file error: %s", filename.c_str());
		return 0;
	}

	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	ILint fmt = ilGetInteger(IL_IMAGE_FORMAT);
	int bytePerPixel = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	
	ILint destfmt = IL_BGRA;
	Texture::Format format = Texture::TF_A8R8G8B8;

	if (fmt==IL_RGBA || fmt==IL_BGRA)
	{
		format = Texture::TF_A8R8G8B8;
		destfmt = IL_BGRA;
	}
	else if(fmt==IL_RGB || fmt==IL_BGR)
	{
		format = Texture::TF_R8G8B8;
		destfmt = IL_BGR;
	}
	else
	{
		assertion(false, "");
	}

	Texture2D* texture = 0;
	texture = new0 Texture2D(format, width, height, 1);

	for (int y=0; y<height; y++)
	{
		int y1 = revert ? y : height-1-y;
		char *destBuffer = texture->GetData(0) + bytePerPixel*width*y;
		ilCopyPixels(0, y1, 0, width, 1, 1, destfmt, IL_UNSIGNED_BYTE, destBuffer);
	}

	ilDeleteImages(1, &image);

	return texture;
}
//----------------------------------------------------------------------------

#ifndef DWORD
typedef unsigned long DWORD;
#endif

#define FOURCC(c0, c1, c2, c3) (c0 | (c1 << 8) | (c2 << 16) | (c3 << 24))

const DWORD D3DFMT_R16F				= 111;
const DWORD D3DFMT_G16R16F			= 112;
const DWORD D3DFMT_A16B16G16R16F	= 113;
const DWORD D3DFMT_R32F				= 114;
const DWORD D3DFMT_G32R32F			= 115;
const DWORD D3DFMT_A32B32G32R32F	= 116;

#define DDSD_CAPS        0x00000001
#define DDSD_HEIGHT      0x00000002
#define DDSD_WIDTH       0x00000004
#define DDSD_PITCH       0x00000008
#define DDSD_PIXELFORMAT 0x00001000
#define DDSD_MIPMAPCOUNT 0x00020000
#define DDSD_LINEARSIZE  0x00080000
#define DDSD_DEPTH       0x00800000

#define DDPF_ALPHAPIXELS 0x00000001
#define DDPF_FOURCC      0x00000004
#define DDPF_RGB         0x00000040

#define DDSCAPS_COMPLEX  0x00000008 
#define DDSCAPS_TEXTURE  0x00001000 
#define DDSCAPS_MIPMAP   0x00400000 

#define DDSCAPS2_CUBEMAP		   0x00000200 
#define DDSCAPS2_CUBEMAP_POSITIVEX 0x00000400 
#define DDSCAPS2_CUBEMAP_NEGATIVEX 0x00000800 
#define DDSCAPS2_CUBEMAP_POSITIVEY 0x00001000 
#define DDSCAPS2_CUBEMAP_NEGATIVEY 0x00002000 
#define DDSCAPS2_CUBEMAP_POSITIVEZ 0x00004000 
#define DDSCAPS2_CUBEMAP_NEGATIVEZ 0x00008000 
#define DDSCAPS2_VOLUME			   0x00200000 

struct DDPIXELFORMAT
{
	DWORD dwSize; 
	DWORD dwFlags; 
	DWORD dwFourCC; 
	DWORD dwRGBBitCount; 
	DWORD dwRBitMask; 
	DWORD dwGBitMask; 
	DWORD dwBBitMask; 
	DWORD dwRGBAlphaBitMask; 
};

struct DDSCAPS2
{
	DWORD    dwCaps;
	DWORD    dwCaps2;
	DWORD    dwCaps3;
	DWORD    dwCaps4; 
};

struct DDSHeader
{
	char          magic[4];
	DWORD         dwSize;
	DWORD         dwFlags;
	DWORD         dwHeight;
	DWORD         dwWidth;
	DWORD         dwPitchOrLinearSize;
	DWORD         dwDepth;
	DWORD         dwMipMapCount;
	DWORD         dwReserved1[11];
	DDPIXELFORMAT ddpfPixelFormat;
	DDSCAPS2      ddsCaps;
	DWORD         dwReserved2;
};

static Texture::Format ConvertFourCCFormat(uint32_t fourcc)
{
	switch(fourcc)
	{
	case FOURCC('D','X','T','1'):
		return Texture::TF_DXT1;
	case FOURCC('D','X','T','3'):
		return Texture::TF_DXT3;
	case FOURCC('D','X','T','5'):
		return Texture::TF_DXT5;
	default:
		assertion(false, "other format is not supportted.");
		return Texture::TF_NONE;
	};
}

static void GetDescInfo (const DDSHeader &header, int &width, int &height,
						 int &minmap, Texture::Format &format)
{
	if(strncmp(header.magic, "DDS ", 4) != 0)
	{
		assertion(false, "this is not DDS.");
	}

	if (header.dwFlags & DDSD_CAPS)
	{
		const DDSCAPS2 &caps = header.ddsCaps;
		if(caps.dwCaps2&DDSCAPS2_CUBEMAP)
		{
			assertion(false, "current not supported.");
		}
		else if(caps.dwCaps2&DDSCAPS2_VOLUME)
		{
			assertion(false, "current not supported.");
		}
	}

	assertion((header.dwFlags&DDSD_WIDTH) && (header.dwFlags&DDSD_HEIGHT), "");
	width = (int)header.dwWidth;
	height = (int)header.dwHeight;

	if (header.dwFlags&DDSD_MIPMAPCOUNT)
	{
		assertion(((header.ddsCaps.dwCaps&DDSCAPS_MIPMAP)!=0), "must has minmap.");
		minmap = header.dwMipMapCount;
	}
	else
	{
		minmap = 1;
	}

	const DDPIXELFORMAT &fmt = header.ddpfPixelFormat;

	if(fmt.dwFlags & DDPF_RGB)
	{
		assertion(false, "");
	}
	else if(fmt.dwFlags & DDPF_FOURCC)
	{
		format = ConvertFourCCFormat(fmt.dwFourCC);
	}
	else
	{
		assertion(false, "");
	}
}

Texture2D *ResourceManager::LoadTextureFromDDS (const std::string &filename)
{
	FILE* inFile;
	inFile = fopen(filename.c_str(), "rb");

	if (!inFile)
	{
		assertion(false, "Failed to open file %s\n", filename.c_str());
		return 0;
	}

	DDSHeader header;
	int numRead = (int)fread(&header, sizeof(header), 1, inFile);
	PX2_UNUSED(numRead);

	int width = 0;
	int height = 0;
	int minmap = 1;
	Texture::Format format;
	GetDescInfo(header, width, height, minmap, format);

	Texture2D *texture = new Texture2D(format, width, height, minmap);
	fread(texture->GetData(0), texture->GetNumTotalBytes(), 1, inFile);

	if (fclose(inFile) != 0)
	{
		assertion(false, "Failed to read or close file %s\n",
			filename.c_str());
		return 0;
	}

	return texture;
}
//----------------------------------------------------------------------------
void ResourceManager::StartThread ()
{
#if defined(WIN32)
	mLoadingDequeSemaphore = ::CreateSemaphore(NULL, 0, 10000, NULL);
#endif

	mLoadingThread = new0 Thread(ThreadLoadFun, this);
}
//----------------------------------------------------------------------------