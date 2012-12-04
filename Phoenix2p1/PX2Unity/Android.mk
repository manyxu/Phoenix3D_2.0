LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := PX2Unity

LOCAL_SRC_FILES := \
PX2CSVParser.cpp \
PX2LanguageManager.cpp \
ZLib/adler32.c \
ZLib/compress.c \
ZLib/crc32.c \
ZLib/deflate.c \
ZLib/gzclose.c \
ZLib/gzlib.c \
ZLib/gzread.c \
ZLib/gzwrite.c \
ZLib/infback.c \
ZLib/inffast.c \
ZLib/inflate.c \
ZLib/inftrees.c \
ZLib/trees.c \
ZLib/uncompr.c \
ZLib/zutil.c \
ZLib/minzip/ioapi.c \
ZLib/minzip/unzip.c \
DevIL/PNG/png.c \
DevIL/PNG/pngerror.c \
DevIL/PNG/pngget.c \
DevIL/PNG/pngmem.c \
DevIL/PNG/pngpread.c \
DevIL/PNG/pngread.c \
DevIL/PNG/pngrio.c \
DevIL/PNG/pngrtran.c \
DevIL/PNG/pngrutil.c \
DevIL/PNG/pngset.c \
DevIL/PNG/pngtrans.c \
DevIL/PNG/pngwio.c \
DevIL/PNG/pngwrite.c \
DevIL/PNG/pngwtran.c \
DevIL/PNG/pngwutil.c \
DevIL/altivec_common.c \
DevIL/altivec_typeconversion.c \
DevIL/il_alloc.c \
DevIL/il_bits.c \
DevIL/il_convbuff.c \
DevIL/il_convert.c \
DevIL/il_devil.c \
DevIL/il_error.c \
DevIL/il_files.c \
DevIL/il_fastconv.c \
DevIL/il_internal.c \
DevIL/il_io.c \
DevIL/il_manip.c \
DevIL/il_neuquant.c \
DevIL/il_pal.c \
DevIL/il_quantizer.c \
DevIL/il_register.c \
DevIL/il_size.c \
DevIL/il_stack.c \
DevIL/il_states.c \
DevIL/il_utility.c \
DevIL/il_bmp.c \
DevIL/il_wbmp.c \
DevIL/il_png.c \
PX2JNI.cpp \
PX2ResourceManager.cpp \
TinyXML/tinystr.cpp \
TinyXML/tinyxml.cpp \
TinyXML/tinyxmlerror.cpp \
TinyXML/tinyxmlparser.cpp \
PX2XMLData.cpp \
PX2XMLNode.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
$(LOCAL_PATH)/DevIL/IL/ \
$(LOCAL_PATH)/DevIL/PNG/ \
$(LOCAL_PATH)/ZLib/ \
$(LOCAL_PATH)/ZLib/minzip/ \
$(LOCAL_PATH)/DevIL/ \
$(LOCAL_PATH)/TinyXML/ \
$(PX2_ROOT)/PX2SDK/Include/ \

# define the macros          
LOCAL_CFLAGS := -D__ANDROID__
LOCAL_CFLAGS += -DIL_STATIC_LIB
LOCAL_CFLAGS += -DIOAPI_NO_64

include $(BUILD_STATIC_LIBRARY)
