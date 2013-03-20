/*
*
* 文件名称	：	PX2ResourceManager.cpp
*
*/

#include "PX2ResourceManager.hpp"
#include "PX2StringHelp.hpp"
#include "PX2XMLData.hpp"

// DevIL
#include "IL/il.h"
#include "IL/ilu.h"

#include "unzip.h"
#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#elif defined __ANDROID__
#include "PX2JNI.hpp"
#endif

#pragma warning(disable : 4312)

using namespace PX2;
using namespace std;

//----------------------------------------------------------------------------
std::string ResourceManager::msResPath;
//----------------------------------------------------------------------------
ResourceManager::ResourceManager ()
:
mLoadingThread(0),
mTimeCounter(0),
mQuitLoading(false),
mDDSKeepCompressed(true),
mReadFromZip(false),
mLoadRecordMutex(0),
mLoadingDequeMutex(0),
mResTableMutex()
{
	mLoadRecordMutex = new0 Mutex();
	mLoadingDequeMutex = new0 Mutex();
	mResTableMutex = new0 Mutex();

	// Init Devil
	ilInit();
	ilEnable(IL_FILE_OVERWRITE);
	ilEnable(IL_CONV_PAL);

	CreateCondition(mLoadingDequeCondition);
	mLoadingThread = new0 Thread("ResLoadThread");
	mLoadingThread->Start(*this);

#if defined WIN32
	if (msResPath.empty())
	{
		char full_path[_MAX_PATH + 1];
		GetModuleFileName(NULL, full_path, _MAX_PATH + 1);
		std::string ret((char*)full_path);
		ret =  ret.substr(0, ret.rfind("\\") + 1);

		msResPath = StringHelp::StandardisePath(ret);
	}

	FILE* inFile = 0;
	inFile = fopen("Data", "rb");
	if (inFile)
	{
		mReadFromZip = true;
		fclose(inFile);
		inFile = 0;
	}
	else
	{
		mReadFromZip = false;
	}
#endif
}
//----------------------------------------------------------------------------
ResourceManager::~ResourceManager ()
{
	PostCondition(mLoadingDequeCondition);

	if (mLoadingThread)
	{
		mQuitLoading = true;
		mLoadingThread->Join();
		delete0(mLoadingThread);
		mLoadingThread = 0;
	}

	CloseCondition(mLoadingDequeCondition);

	// Shutdown Devil
	ilShutDown();

	if (mLoadRecordMutex)
	{
		delete0(mLoadRecordMutex);
	}

	if (mLoadingDequeMutex)
	{
		delete0(mLoadingDequeMutex);
	}

	if (mResTableMutex)
	{
		delete0(mResTableMutex);
	}
}
//----------------------------------------------------------------------------
void ResourceManager::Clear ()
{
	ScopedCS scopeCS(mResTableMutex);
	mResTable.clear();
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

	_LoadTheRecord(loadRec);

	return loadRec.Obj;
}
//----------------------------------------------------------------------------
bool ResourceManager::GetBuffer (const std::string &filename, int &bufferSize, 
	char* &buffer)
{
	if (filename == "")
	{
		assertion(false, "filename must not be null");
	}

	return _LoadBuffer(filename, bufferSize, buffer);
}
//----------------------------------------------------------------------------
bool ResourceManager::AddTexPack (const std::string &texPackPath)
{
	if (mTexPacks.find(texPackPath) != mTexPacks.end())
		return false;

	int bufferSize = 0;
	char *buffer = 0;
	if (GetBuffer(texPackPath, bufferSize, buffer))
	{
		std::string outPath;
		std::string outBaseName;
		std::string outExt;
		StringHelp::SplitFullFilename(texPackPath, outPath, outBaseName, outExt);

		XMLData data;
		if (data.LoadBuffer(buffer, bufferSize))
		{
			XMLNode rootNode = data.GetRootNode();
			std::string imagePath = rootNode.AttributeToString("imagePath");
			int width = rootNode.AttributeToInt("width");
			int height = rootNode.AttributeToInt("height");
			TexPack pack;
			pack.ImagePath = imagePath;
			pack.Width = width;
			pack.Height = height;

			XMLNode childNode = rootNode.IterateChild();
			while (!childNode.IsNull())
			{
				std::string eleName;
				int x = 0;
				int y = 0;
				int w = 0;
				int h = 0;
				int oX = 0;
				int oY = 0;
				int oW = 0;
				int oH = 0;
				bool rolated = false;

				if (childNode.HasAttribute("n"))
					eleName = childNode.AttributeToString("n");
				if (childNode.HasAttribute("x"))
					x = childNode.AttributeToInt("x");
				if (childNode.HasAttribute("y"))
					y = childNode.AttributeToInt("y");
				if (childNode.HasAttribute("w"))
					w = childNode.AttributeToInt("w");
				if (childNode.HasAttribute("h"))
					h = childNode.AttributeToInt("h");
				if (childNode.HasAttribute("oX"))
					oX = childNode.AttributeToInt("oX");
				if (childNode.HasAttribute("oY"))
					oY = childNode.AttributeToInt("oY");
				if (childNode.HasAttribute("oW"))
					oW = childNode.AttributeToInt("oW");
				if (childNode.HasAttribute("oH"))
					oH = childNode.AttributeToInt("oH");
				if (childNode.HasAttribute("r"))
					rolated = (std::string(childNode.AttributeToString("r"))=="y");
				
				TexPackElement ele;
				ele.X = x;
				ele.Y = y;
				ele.W = w;
				ele.H = h;
				ele.OX = oX;
				ele.OY = oY;
				ele.OW = oW;
				ele.OH = oH;
				ele.Rolated = rolated;
				ele.TexWidth = width;
				ele.TexHeight = height;
				ele.ElementName = eleName;
				ele.ImagePathFull = outPath+imagePath;

				pack.Elements.push_back(ele);

				std::string allStr = texPackPath+eleName;
				mPackElements[allStr] = ele;

				childNode = rootNode.IterateChild(childNode);
			}

			mTexPacks[texPackPath] = pack;
		}

		delete1(buffer);

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
const TexPack &ResourceManager::GetTexPack (const std::string &texPackPath)
{
	return mTexPacks[texPackPath];
}
//----------------------------------------------------------------------------
const TexPackElement &ResourceManager::GetTexPackElement (
	const std::string &texPackPath, const std::string &eleName)
{
	std::string allStr = texPackPath+eleName;
	return mPackElements[allStr];
}
//----------------------------------------------------------------------------
ResHandle ResourceManager::BackgroundLoad (
	const std::string &filename)
{
	LoadRecord &rec = InsertRecord(filename);

	{
		ScopedCS scopedCS(mLoadRecordMutex);

		if (LS_UNLOADED == rec.State)
		{
			ScopedCS scopedCSLoadingDeque(mLoadingDequeMutex);
			rec.State = LS_LOADQUE;
			mLoadingDeque.push_front(&rec);

			PostCondition(mLoadingDequeCondition);
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
bool ResourceManager::SaveCachedResource (const std::string &filename)
{
	ScopedCS scopeCS(mResTableMutex);

	OutStream outPut;

	ResTable::iterator it = mResTable.begin();
	for (; it!=mResTable.end(); it++)
	{
		Object *obj = it->second.Obj;
		if (obj)
		{
			outPut.Insert(obj);
		}
	}

	return outPut.Save(filename);
}
//----------------------------------------------------------------------------
bool ResourceManager::LoadCachedResource (const std::string &filename)
{
	ScopedCS scopeCS(mResTableMutex);

	InStream inPut;

	if (inPut.Load(filename))
	{
		int numObjects = inPut.GetNumObjects();
		for (int i=0; i<numObjects; i++)
		{
			Object *obj = inPut.GetObjectAt(i);
			if (obj)
			{
				std::string filename = obj->GetResourcePath();
				LoadRecord rec;
				rec.Filename = filename;
				rec.Obj = obj;
				mResTable.insert(std::pair<std::string, LoadRecord>(filename, rec));
			}
		}

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
std::string ResourceManager::GetWriteablePath ()
{
#if defined(_WIN32) || defined(WIN32)

	char full_path[_MAX_PATH + 1];
	GetModuleFileName(NULL, full_path, _MAX_PATH + 1);
	std::string ret((char*)full_path);
	ret =  ret.substr(0, ret.rfind("\\") + 1);

	return ret;

#elif defined __ANDROID__
	// the path is: /data/data/ + package name
	std::string dir("/data/data/");
	std::string temp = GetPackageNameJNI();

	if (!temp.empty())
	{
		dir.append(temp).append("/");

		return dir;
	}
	else
	{
		return "";
	}

	return temp;
#endif
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
		WaitCondition(mLoadingDequeCondition);

		if (mQuitLoading)
			break;

		{
			ScopedCS scopedCS(mLoadingDequeMutex);

			if (mLoadingDeque.empty())
				continue;

			rec = mLoadingDeque.front();
			mLoadingDeque.pop_front();
		}

		_LoadTheRecord(*rec);
	}

	return 0;
}
//----------------------------------------------------------------------------
ResourceManager::LoadRecord &ResourceManager::InsertRecord (const std::string &filename)
{
	ScopedCS scopeCS(mResTableMutex);

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
void ResourceManager::_LoadTheRecord (LoadRecord &rec)
{
	bool needLoad = false;
	{
		ScopedCS scopedCS(mLoadRecordMutex);

		if (LS_UNLOADED == rec.State || LS_LOADQUE == rec.State)
		{
			rec.State = LS_LOADING;
			needLoad = true;
		}
	}

	if (needLoad)
	{
		rec.Obj = _LoadObject(rec.Filename);
		rec.LastTouchedTime = mTimeCounter;
		rec.State = LS_LOADED;
	}

	// 可能其他线程正在加载这个资源
	while (rec.State != LS_LOADED)
	{
		SleepInSeconds(0.01f);
	}
}
//----------------------------------------------------------------------------
Object *ResourceManager::_LoadObject (const std::string &filename)
{
	Object *obj = 0;

	string::size_type pos = filename.find(".");
	if (pos == string::npos)
		return 0;

	std::string outPath;
	std::string outBaseName;
	std::string outExtention;
	StringHelp::SplitFullFilename(filename, outPath, outBaseName, outExtention);

	char *buffer = 0;
	int bufferSize = 0;

	if (GetBuffer(filename, bufferSize, buffer))
	{
		if ("png"==outExtention || "PNG"==outExtention)
		{
			obj = LoadTexFormOtherImagefile(outExtention, bufferSize, buffer);
		}
		else
		{
			InStream inStream;
			inStream.Load1(bufferSize, buffer);
			obj = inStream.GetObjectAt(0);
		}

		delete1(buffer);
		bufferSize = 0;
	}

	if (obj)
	{
		obj->SetResourcePath(filename);
	}

	return obj;
}
//----------------------------------------------------------------------------
bool ResourceManager::_LoadBuffer (const std::string &filename,
	int &bufferSize, char* &buffer)
{
	if (mReadFromZip)
	{
		std::string packageName("Data");
		std::string fullPackageName = msResPath + packageName;

		return GetFileDataFromZip(fullPackageName, filename, bufferSize, buffer);
	}
	else
	{
#ifdef __ANDROID__
		std::string fullFilename = filename;
		fullFilename.insert(0, "assets/");
		return GetFileDataFromZip(msResPath, fullFilename, bufferSize, buffer);
#else
		if (!FileIO::Load(filename, true, bufferSize, buffer))
		{
			return false;
		}

		return true;
#endif
	}

	return false;
}
//----------------------------------------------------------------------------
Texture2D *ResourceManager::LoadTexFormOtherImagefile (std::string outExt,
	int bufferSize, const char*buffer)
{
	ILuint image;
	ilGenImages(1, &image);
	ilBindImage(image);

	bool revert = false;

	ILenum type = IL_TYPE_UNKNOWN;

	if ("jpg" == outExt || "JPG" == outExt)
	{
		type = IL_JPG;
		revert = true;
	}
	else if ("png" == outExt || "PNG" == outExt)
	{
		type = IL_PNG;
		revert = true;
	}
	else if ("dds" == outExt || "DDS" == outExt)
	{
		type = IL_DDS;
		revert = true;
	}
	else if ("tga" == outExt || "TGA" == outExt)
	{
		type = IL_TGA;
	}
	else if ("bmp" == outExt || "BMP" == outExt)
	{
		type = IL_BMP;
	}
	else
	{
		assertion(false, "format is not supported.");
		return 0;
	}

	ILboolean b = ilLoadL(type, buffer, bufferSize);
	if (!b)
	{
		assertion(false, "ilLoadL texture file error: %s", outExt.c_str());
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
	assertion(false, "current not do this.");

	return 0;

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
bool ResourceManager::GetFileDataFromZip (const std::string &packageName,
	const std::string &filename, int &bufferSize, char* &buffer)
{
	if (packageName.empty() || filename.empty())
		return 0;

	unzFile ufile = 0;

	ufile = unzOpen(packageName.c_str());
	if (!ufile)
		return false;

	if (UNZ_OK != unzLocateFile(ufile, filename.c_str(), 1))
	{
		assertion(false, "unzLocateFile failed.");

		unzClose(ufile);
		return false;
	}

	char filePathTemp[260];
	unz_file_info fileInfo;
	if (UNZ_OK != unzGetCurrentFileInfo(ufile, &fileInfo, filePathTemp,
		sizeof(filePathTemp), 0, 0, 0, 0))
	{
		assertion(false, "unzGetCurrentFileInfo failed.");

		unzClose(ufile);
		return false;
	}

	if (UNZ_OK != unzOpenCurrentFile(ufile))
	{
		assertion(false, "unzOpenCurrentFile failed.");

		unzClose(ufile);
		return false;
	}

	buffer = new1<char>(fileInfo.uncompressed_size);
	int readedSize = 0;
	readedSize = unzReadCurrentFile(ufile, buffer, fileInfo.uncompressed_size);

	if (0!=readedSize && (fileInfo.uncompressed_size!=readedSize))
	{
		assertion(false, "the file size is wrong.");

		unzClose(ufile);

		delete1<char>(buffer);
		buffer = 0;

		return false;
	}

	bufferSize = (int)fileInfo.uncompressed_size;

	unzCloseCurrentFile(ufile);
	unzClose(ufile);

	return true;
}
//----------------------------------------------------------------------------
void ResourceManager::Run ()
{
	RunLoadingThread();
}
//----------------------------------------------------------------------------