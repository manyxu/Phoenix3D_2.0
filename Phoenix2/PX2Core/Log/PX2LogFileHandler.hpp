/*
* Phoenix 3D 引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2LogFileHandler.hpp
*
* 版本		:	1.0 (2011/01/30)
*
* 作者		：	more
*
*/

#ifndef PX2LOGFILEHANDLER_HPP
#define PX2LOGFILEHANDLER_HPP

#include "PX2Log.hpp"

namespace PX2
{

	/// 文件日志句柄
	class FileLogHandler : public LogHandler
	{
	public:
		FileLogHandler (unsigned int levels, const char *filename);
		virtual ~FileLogHandler ();
		virtual bool Handle (const char *filename, int line, 
			unsigned int level,	const char *str);

	private:
		FILE *mFile;
	};

}

#endif