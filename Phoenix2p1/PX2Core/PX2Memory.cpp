/*
*
* 文件名称	：	PX2Memory.cpp
*
*/

#include "PX2Memory.hpp"

#ifdef PX2_USE_MEMORY

using namespace PX2;

Memory::MemoryMap* Memory::msMap = 0;
Mutex Memory::msMutex;
Memory::Allocator Memory::msAllocator = &Memory::DefaultAllocator;
Memory::Deallocator Memory::msDeallocator = &Memory::DefaultDeallocator;
unsigned int Memory::Information::msUniqueID = 0;
//----------------------------------------------------------------------------
void Memory::Initialize (Allocator allocator, Deallocator deallocator)
{
	msMutex.Enter();

	msAllocator = allocator;
	msDeallocator = deallocator;

	// 这里你必须使用'new'而不是'new0'，否则你会导致无限的循环。
	msMap = new MemoryMap();

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void Memory::Terminate (const std::string& filename, bool alwaysReportFile)
{
	msMutex.Enter();

	assertion(msMap != 0, "Memory::Terminate should only be called once.\n");
	if (!msMap)
	{
		return;
	}

	FILE* outFile = 0;
	if (!alwaysReportFile && msMap->empty())
	{
		// do not need report file
	}
	else
	{
		outFile = fopen(filename.c_str(), "wt");
		if (!outFile)
		{
			msMutex.Leave();
			return;
		}
	}

	// Create a sorted map from the memory map based on unique ID.
	SortedMap sorted;
	MemoryMap::const_iterator mapIter = msMap->begin();
	MemoryMap::const_iterator mapEnd = msMap->end();
	for (/**/; mapIter != mapEnd; ++mapIter)
	{
		sorted[mapIter->second.mUniqueID] =
			std::make_pair(mapIter->first, mapIter->second);
	}

	// Create the format for the output.
	std::string format = "uid = %8u , ";
	format += "addr = %p , ";
	format += "numbytes = %13d , ";
	format += "numdims = %d , ";
	format += "%s (%4d)\n";

	// Save the sorted map to disk.
	SortedMap::const_iterator sortedIter = sorted.begin();
	SortedMap::const_iterator sortedEnd = sorted.end();
	for (/**/; sortedIter != sortedEnd; ++sortedIter)
	{
		unsigned int uniqueID = sortedIter->first;
		void* address = sortedIter->second.first;
		Information info = sortedIter->second.second;

		if (outFile)
		{
			fprintf(outFile, format.c_str(), uniqueID, address, info.mNumBytes,
				info.mNumDimensions, info.mFile, info.mLine);
		}
	}

	if (outFile)
	{
		fclose(outFile);
	}

	// 这里你必须使用'delete'而不是'delete0'，否则你会导致无限的循环。
	delete msMap;
	msMap = 0;

	msMutex.Leave();
}
//----------------------------------------------------------------------------
void* Memory::CreateBlock (size_t numBytes, int numDimensions) const
{
	msMutex.Enter();

	void* memBlock = msAllocator((int)numBytes, mFile, mLine);
	(*msMap)[memBlock] = Information((int)numBytes, numDimensions, mFile, mLine);

	msMutex.Leave();
	return memBlock;
}
//----------------------------------------------------------------------------
void* Memory::DefaultAllocator (size_t numBytes, const char*, int)
{
	return malloc(numBytes);
}
//----------------------------------------------------------------------------
void Memory::DefaultDeallocator (void* memBlock, const char*, int)
{
	free(memBlock);
}
//----------------------------------------------------------------------------

#endif
