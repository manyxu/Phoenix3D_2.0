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

#include "PX2CorePrerequisites.hpp"

namespace PX2
{

	/// 日志类型
	enum LogType
	{
		LT_CONFIG = 1,
		LT_INFO = 2,
		LT_WARNING = 4,
		LT_SEVERE = 8,
		LT_SEVEREMSG = 16,
		LT_DUMP = 32,
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

	PX2_CORE_ENTRY bool LogInitlize ();
	PX2_CORE_ENTRY void LogShutdown ();
	PX2_CORE_ENTRY int LogAddHandler (LogHandler *handler);
	PX2_CORE_ENTRY int LogAddFileHandler (const char *filename, int line, unsigned int levels);
	PX2_CORE_ENTRY void LogSetCurParam (const char *filename, int line, unsigned int levels);
	PX2_CORE_ENTRY void LogMessage (const char *format, ...);
};

#define PX2LOG_CONFIG		PX2::LogSetCurParam(__FILE__, __LINE__, PX2::LOGL_CONFIG),		PX2::LogMessage
#define PX2LOG_INFO			PX2::LogSetCurParam(__FILE__, __LINE__, PX2::LOGL_INFO),		PX2::LogMessage
#define PX2LOG_WARNING		PX2::LogSetCurParam(__FILE__, __LINE__, PX2::LOGL_WARNING),		PX2::LogMessage
#define PX2LOG_SEVERE		PX2::LogSetCurParam(__FILE__, __LINE__, PX2::LOGL_SEVERE),		PX2::LogMessage
#define PX2LOG_SEVEREMSG	PX2::LogSetCurParam(__FILE__, __LINE__, PX2::LOGL_SEVEREMSG),	PX2::LogMessage
#define PX2LOG_DUMP			PX2::LogSetCurParam(__FILE__, __LINE__, PX2::LOGL_DUMP),		PX2::LogMessage

#endif
