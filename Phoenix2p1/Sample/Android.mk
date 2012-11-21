LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Sample

LOCAL_SRC_FILES := SampleApp.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := PX2Core
LOCAL_WHOLE_STATIC_LIBRARIES += PX2Mathematics
LOCAL_WHOLE_STATIC_LIBRARIES += PX2Graphics
LOCAL_WHOLE_STATIC_LIBRARIES += PX2EventSystem
LOCAL_WHOLE_STATIC_LIBRARIES += PX2Unity
LOCAL_WHOLE_STATIC_LIBRARIES += PX2AppFrame

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..\
$(PX2_ROOT)/PX2SDK/Include/ \
$(PX2_ROOT)/ThirdPartiesLibs/OGLES/

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
            
include $(BUILD_STATIC_LIBRARY)

$(call import-module, PX2Core)
$(call import-module, PX2Mathematics)
$(call import-module, PX2Graphics)
$(call import-module, PX2EventSystem)
$(call import-module, PX2Unity)
$(call import-module, PX2AppFrame)
