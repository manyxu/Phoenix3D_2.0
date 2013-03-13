/*
* Phoenix 3D 引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Log.hpp
*
* 版本		:	1.0 (2011/01/30)
*
* 作者		：	more
*
*/

#ifndef PX2LOG_HPP
#define PX2LOG_HPP

#include "PX2CorePre.hpp"

namespace PX2
{

	/// 日志类型
	enum LogType
	{
		LT_INFO = 1,
		LT_ERROR = 2,
		LT_USER = 4,
		LT_SERVER_INFO = 8,
		LT_SERVER_ERROR = 16,
		LT_SERVER_USER = 32,
		LT_ALLLEVEL = 16-1
	};

	class LogHandler
	{
	public:
		LogHandler (unsigned int levels);
		virtual ~LogHandler ();
		virtual bool Handle (const char *filename, int line, unsigned int level, 
			const char *str) = 0;

		unsigned int GetLevels ();

	protected:
		unsigned int mLevelFlags;
	};

	 bool LogInitlize ();
	 void LogShutdown ();
	 int LogAddHandler (LogHandler *handler);
	 int LogAddFileHandler (const char *filename, int line, unsigned int levels);
	 int LoadAddOutputWindowHandler (int line, unsigned int levels);
	 void LogSetCurParam (const char *filename, int line, unsigned int levels);
	 void LogMessage (const char *format, ...);

};

#define PX2_LOG_INFO			PX2::LogSetCurParam(__FILE__, __LINE__, PX2::LT_INFO),			PX2::LogMessage
#define PX2_LOG_ERROR			PX2::LogSetCurParam(__FILE__, __LINE__, PX2::LT_ERROR),			PX2::LogMessage
#define PX2_LOG_USER			PX2::LogSetCurParam(__FILE__, __LINE__, PX2::LT_USER),			PX2::LogMessage
#define PX2_LOG_SERVER_INFO		PX2::LogSetCurParam(__FILE__, __LINE__, PX2::LT_SERVER_INFO),	PX2::LogMessage
#define PX2_LOG_SERVER_ERROR	PX2::LogSetCurParam(__FILE__, __LINE__, PX2::LT_SERVER_ERROR),	PX2::LogMessage
#define PX2_LOG_SERVER_USER		PX2::LogSetCurParam(__FILE__, __LINE__, PX2::LT_SERVER_USER),	PX2::LogMessage

#endif
