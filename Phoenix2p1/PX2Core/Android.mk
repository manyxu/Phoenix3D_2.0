LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Phoenix3d_static

LOCAL_MODULE_FILENAME := libPhoenix3d

LOCAL_SRC_FILES := \
PX2Any.cpp \
PX2Assert.cpp \
PX2BufferIO.cpp \
PX2DayTime.cpp \
PX2Endian.cpp \
PX2Environment.cpp \
PX2FileIO.cpp \
PX2Help.cpp \
PX2InitTerm.cpp \
PX2InStream.cpp \
PX2Log.cpp \
PX2LogFileHandler.cpp \
PX2Memory.cpp \
PX2MinHeap.cpp \
PX2Mutex.cpp \
PX2Object.cpp \
PX2OutStream.cpp \
PX2Rtti.cpp \
PX2ScopedCS.cpp \
PX2SmartPointer.cpp \
PX2Stream.cpp \
PX2Thread.cpp \
PX2Time.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_EXPORT_LDLIBS := -llog\
                       -lz \
                       -lGLESv2

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_LDLIBS := -lGLESv2 \
                -lEGL \
                -llog \
                -lz 

# define the macro to compile through support/zip_support/ioapi.c                
LOCAL_CFLAGS := -DUSE_FILE32API

include $(BUILD_STATIC_LIBRARY)
