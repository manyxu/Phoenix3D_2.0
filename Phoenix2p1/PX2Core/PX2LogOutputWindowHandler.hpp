/*
*
* 文件名称	：	PX2LogOutputWindowHandler.hpp
*
*/

#ifndef PX2LOGOUTPUTWINDOWHANDLER_HPP
#define PX2LOGOUTPUTWINDOWHANDLER_HPP

#include "PX2Log.hpp"

namespace PX2
{

	/// 输出到调试窗口句柄
	class OutputWindowHandler : public LogHandler
	{
	public:
		OutputWindowHandler (unsigned int levels);
		virtual ~OutputWindowHandler ();

		virtual bool Handle (const char *filename, int line,
			unsigned int level,	const char *str);
	};

}

#endif