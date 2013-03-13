LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := PX2Effect

LOCAL_SRC_FILES := \
PX2EffectNode.cpp \
PX2EffectMaterial.cpp \
PX2EffectModule.cpp \
PX2EM_E_EmitRate.cpp \
PX2EM_E_EmitterTranslate.cpp \
PX2EM_P_Accelerate.cpp \
PX2EM_P_AccelerateDir.cpp \
PX2EM_P_AlphaByAge.cpp \
PX2EM_P_AlphaInit.cpp \
PX2EM_P_ColorByAge.cpp \
PX2EM_P_ColorInit.cpp \
PX2EM_P_FaceAxisInit.cpp \
PX2EM_P_LifeInit.cpp \
PX2EM_P_RotateDegreeInit.cpp \
PX2EM_P_RotateSpeedByAge.cpp \
PX2EM_P_RotateSpeedInit.cpp \
PX2EM_P_SizeByAge.cpp \
PX2EM_P_SizeInit.cpp \
PX2EM_P_SpeedDirInit.cpp \
PX2EM_P_SpeedInit.cpp \
PX2Particle.cpp \
PX2ParticleEmitter.cpp \
PX2ParticleEmitterControl.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
$(PX2_ROOT)/PX2SDK/Include/

include $(BUILD_STATIC_LIBRARY)
