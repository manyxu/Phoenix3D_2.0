LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := PX2Core

LOCAL_SRC_FILES := \
PX2Assert.cpp \
PX2BufferIO.cpp \
PX2DayTime.cpp \
PX2Endian.cpp \
PX2Environment.cpp \
PX2FileIO.cpp \
PX2FString.cpp \
PX2InitTerm.cpp \
PX2InStream.cpp \
PX2Log.cpp \
PX2LogFileHandler.cpp \
PX2LogOutputWindowHandler.cpp \
PX2Memory.cpp \
PX2Mutex.cpp \
PX2Object.cpp \
PX2OutStream.cpp \
PX2Rtti.cpp \
PX2ScopedCS.cpp \
PX2SmartPointer.cpp \
PX2Stream.cpp \
PX2StringHelp.cpp \
PX2Condition.cpp \
PX2Thread.cpp \
PX2Time.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_EXPORT_LDLIBS := -llog

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_LDLIBS := -llog

# define the macro to compile Android            
LOCAL_CFLAGS := -D__ANDROID__

include $(BUILD_STATIC_LIBRARY)
