/*
*
* ÎÄ¼þÃû³Æ	£º	PX2StringHelp.cpp
*
*/

#include "PX2StringHelp.hpp"
#include "PX2Assert.hpp"
using namespace PX2;

#ifdef WIN32
	#include <Windows.h>
#endif

//----------------------------------------------------------------------------
std::string StringHelp::StandardisePath (const std::string &path)
{
	std::string strPath = path;
	
	std::replace(strPath.begin(), strPath.end(), '\\', '/');

	if (strPath[strPath.length() - 1] != '/')
		strPath += '/';

	return strPath;
}
//----------------------------------------------------------------------------
void StringHelp::SplitFilename (const std::string &fullName,
						   std::string &outPath, std::string &outBaseFileName)
{
	std::string path = fullName;

	// Replace \ with / first
	std::replace(path.begin(), path.end(), '\\', '/');
	// split based on final /

	size_t i = path.find_last_of('/');

	if (i == std::string::npos)
	{
		outPath.clear();
		outBaseFileName = fullName;
	}
	else
	{
		outPath = path.substr(0, i+1);
		outBaseFileName = path.substr(i+1, path.size()-i-1);
	}
}
//----------------------------------------------------------------------------
void StringHelp::SplitFullFilename (const std::string &fullName,
							   std::string &outPath,
							   std::string &outBaseName,
							   std::string &outExtention)
{
	std::string outName;
	SplitFilename(fullName, outPath, outName);
	SplitBaseFilename(outName, outBaseName, outExtention);
}
//----------------------------------------------------------------------------
void StringHelp::SplitBaseFilename (const std::string &baseFileName,
							   std::string &outBaseName,
							   std::string &outExtention)
{
	size_t i = baseFileName.find_last_of(".");

	if (i == std::string::npos)
	{
		outExtention.clear();
		outBaseName = baseFileName;
	}
	else
	{
		outExtention = baseFileName.substr(i+1);
		outBaseName = baseFileName.substr(0, i);
	}
}
//----------------------------------------------------------------------------
const size_t MAX_CONVERT = 4096*2;
static char s_DBCSBuffer[MAX_CONVERT];
static wchar_t s_UnicodeBuffer[MAX_CONVERT];
//----------------------------------------------------------------------------
int StringHelp::UnicodeToAnsi (char *dest, int maxChar, const wchar_t *src,
						  int srcChar)
{
#ifdef WIN32

	int nchar;
#ifdef _DEBUG
	nchar = WideCharToMultiByte(CP_ACP, WC_SEPCHARS|WC_COMPOSITECHECK, src, 
		srcChar, dest, 0, NULL, NULL );
	assertion(nchar<maxChar, "");
#endif
	nchar = WideCharToMultiByte(
		CP_ACP,
		WC_SEPCHARS | WC_COMPOSITECHECK,
		src,
		srcChar,
		dest,
		maxChar,
		NULL,
		NULL);
	assertion (nchar>0, "");
	return nchar;
#else

	assertion(false, "Not supported on other platform.");

	return 0;

#endif
}
//----------------------------------------------------------------------------
int StringHelp::AnsiToUnicode (wchar_t *dest, int maxChar, const char *src, 
						  int srcChar)
{
	#ifdef WIN32

	int nchar;
#ifdef _DEBUG
	nchar = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, src, srcChar, dest, 0);
	assertion(nchar<=maxChar, "");
#endif
	nchar = MultiByteToWideChar(
		CP_ACP,
		MB_PRECOMPOSED,
		src,
		srcChar,
		dest,
		maxChar);
	assertion (nchar>0, "");
	return nchar;

#else

	assertion(false, "Not supported on other platform.");

	return 0;

#endif
}
//----------------------------------------------------------------------------
const char *StringHelp::UnicodeToAnsi (const wchar_t *src, int srcChar)
{
	StringHelp::UnicodeToAnsi(s_DBCSBuffer, MAX_CONVERT, src, srcChar);
	return s_DBCSBuffer;
}
//----------------------------------------------------------------------------
wchar_t *StringHelp::AnsiToUnicode (const char *src, int srcChar)
{
	StringHelp::AnsiToUnicode(s_UnicodeBuffer, MAX_CONVERT, src, srcChar);
	return s_UnicodeBuffer;
}
//----------------------------------------------------------------------------