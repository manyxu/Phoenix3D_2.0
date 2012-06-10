/*
*
* ÎÄ¼þÃû³Æ	£º	TdPackageFile.cpp
*
*/

#include "TdPackageFile.hpp"
using namespace Td;

const int PACKAGE_VERSION = 100;

static bool NewPackageFile(const std::string filename)
{
	FileIO outFile;
	outFile.Open(filename, FileIO::FM_DEFAULT_WRITE);

	if (!outFile)
	{
		assertion(false, "Failed to open file %s\n", filename.c_str());
		return false;
	}

	unsigned int id = 0x56789abc;
	int version = PACKAGE_VERSION;
	int numFiles = 0;
	int keyOffset = (int)sizeof(PackageHeader);
	int keyLength = 0;
	int dataOffset = (int)sizeof(PackageHeader);
	int dataLength = 0;
	
	outFile.Write(sizeof(unsigned int), &id);
	outFile.Write(sizeof(int), &version);
	outFile.Write(sizeof(int), &numFiles);
	outFile.Write(sizeof(int), &keyOffset);
	outFile.Write(sizeof(int), &keyLength);
	outFile.Write(sizeof(int), &dataOffset);
	outFile.Write(sizeof(int), &dataLength);

	outFile.Close();

	return true;
}


FilePackage::FilePackage ()
{

}
//----------------------------------------------------------------------------
bool FilePackage::Open (const std::string &filename, bool readOnly)
{
	mReadOnly = readOnly;

	mFileIO.Open(filename, 
		readOnly? FileIO::FM_DEFAULT_READ : FileIO::FM_DEFAULT_WRITE);
	
	if (!mFileIO)
	{
		mFileIO.Close();

		if (readOnly)
		{
			assertion(false, "Failed to open file %s\n", filename.c_str());
			return false;
		}
		else
		{
			if (!NewPackageFile(filename))
				return false;
			
			mFileIO.Open(filename, FileIO::FM_DEFAULT_READ);
			if (!mFileIO)
				return false;
		}
	}

	unsigned int id;;
	int version;
	int numFiles;
	int keyOffset;
	int keyLength;
	int dataOffset;
	int dataLength;

	mFileIO.Read(sizeof(unsigned int), &id);
	mFileIO.Read(sizeof(int), &version);
	mFileIO.Read(sizeof(int), &numFiles);
	mFileIO.Read(sizeof(int), &keyOffset);
	mFileIO.Read(sizeof(int), &keyLength);
	mFileIO.Read(sizeof(int), &dataOffset);
	mFileIO.Read(sizeof(int), &dataLength);
	mPackageHeader.id = id;
	mPackageHeader.version = version;
	mPackageHeader.numFiles = numFiles;
	mPackageHeader.keyOffset = keyOffset;
	mPackageHeader.keyLength = keyLength;
	mPackageHeader.dataOffset = dataOffset;
	mPackageHeader.dataLength = dataLength;

	mFileTable.resize(numFiles);

	if (numFiles >= 0)
	{
		//¡£¡£¡£

		for (int i=0; i<numFiles; i++)
		{
			PackageFileInfo pfi;
			bool ok = mFileIO.Read(sizeof(unsigned int), 6, &pfi);
			
			if (!ok)
			{
				assertion(false, "mFileIO read mFileTable failed!");
				return false;
			}

			mFileTable[i] = pfi;
		}
	}

	return true;
}
//----------------------------------------------------------------------------
void FilePackage::Close ()
{

}
//----------------------------------------------------------------------------
int FilePackage::GetFilesNum ()
{

}
//----------------------------------------------------------------------------
const PackageFileInfo &FilePackage::GetPackageFileInfo (int i)
{

}
//----------------------------------------------------------------------------
DataStream *FilePackage::OpenFile (int fileNum)
{

}
//----------------------------------------------------------------------------
unsigned int FilePackage::ReadFile (void *buffer, unsigned int offset,
									unsigned int len)
{

}
//----------------------------------------------------------------------------
bool FilePackage::AppendOrReplaceFile (unsigned int key0, unsigned int key1,
						  const void *data, unsigned int originSize,
						  unsigned int packageSize)
{

}
//----------------------------------------------------------------------------
bool FilePackage::AppendOrReplaceFile (const char *fileName, bool doCompress)
{

}
//----------------------------------------------------------------------------