/*
* Phoenix 3D 引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Core.hpppp
*
* 版本		:	1.0 (2011/01/30)
*
* 作者		：	more
*
*/

#ifndef PX2CORE_HPP
#define PX2CORE_HPP

// Assert
#include "PX2Assert.hpp"

// DataTypes
#include "PX2Any.hpp"
#include "PX2Table.hpp"
#include "PX2Tuple.hpp"
#include "PX2DoubleChainList.hpp"
#include "PX2FString.hpp"

// Design
#include "PX2Noncopyable.hpp"

#if defined(_WIN32) || defined(WIN32)
#pragma warning(push) 
#pragma warning(disable : 4312)
#endif

#include "PX2Singleton.hpp"

#if defined(_WIN32) || defined(WIN32)
#pragma warning(pop)
#endif

// Help
#include "PX2Environment.hpp"
#include "PX2StringHelp.hpp"

// IO
#include "PX2BufferIO.hpp"
#include "PX2Endian.hpp"
#include "PX2Environment.hpp"
#include "PX2FileIO.hpp"

// Log
#include "PX2Log.hpp"
#include "PX2LogFileHandler.hpp"
#include "PX2LogOutputWindowHandler.hpp"

// Memory
#include "PX2CrashMiniDump.hpp"
#include "PX2FixMemoryPool.hpp"
#include "PX2Memory.hpp"
#include "PX2SmartPointer.hpp"

// Base
#include "PX2Ascii.hpp"

// Notifications
#include "PX2Notification.hpp"
#include "PX2TimedNotificationQueue.hpp"

// ObjectSystems
#include "PX2InitTerm.hpp"
#include "PX2InStream.hpp"
#include "PX2Names.hpp"
#include "PX2Object.hpp"
#include "PX2OutStream.hpp"
#include "PX2Rtti.hpp"
#include "PX2Stream.hpp"

// Thread
#include "PX2Condition.hpp"
#include "PX2ConditionType.hpp"
#include "PX2Eventt.hpp"
#include "PX2Mutex.hpp"
#include "PX2MutexType.hpp"
#include "PX2Runnable.hpp"
#include "PX2ScopedCS.hpp"
#include "PX2Semaphore.hpp"
#include "PX2Thread.hpp"
#include "PX2ThreadType.hpp"

// Time
#include "PX2DateTime.hpp"
#include "PX2Time.hpp"
#include "PX2Timespan.hpp"
#include "PX2Timestamp.hpp"

// Timer
#include "PX2Timer.hpp"
#include "PX2TimerTask.hpp"


#endif