LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := PX2Game

LOCAL_SRC_FILES := \
PX2Actor.cpp \
PX2AmbientRegionActor.cpp \
PX2CameraActor.cpp \
PX2EffectActor.cpp \
PX2SkyActor.cpp \
PX2TerrainActor.cpp \
PX2TriggerActor.cpp \
PX2ActorPicker.cpp \
PX2Netable.cpp \
PX2GameManager.cpp \
PX2Project.cpp \
PX2Scene.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
$(PX2_ROOT)/PX2SDK/Include/

include $(BUILD_STATIC_LIBRARY)
