LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := PX2AppFrame

LOCAL_SRC_FILES := PX2ApplicationBase.cpp \
PX2Application.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
$(PX2_ROOT)/PX2SDK/Include/ \
$(PX2_ROOT)/ThirdPartiesLibs/OGLES/

include $(BUILD_STATIC_LIBRARY)
