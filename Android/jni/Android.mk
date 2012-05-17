# Container library
LOCAL_PATH = $(ROOT_PATH)/Engine/Container

include $(CLEAR_VARS)

LOCAL_MODULE := Container

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/*.cpp))

include $(BUILD_STATIC_LIBRARY)


# Math library
LOCAL_PATH = $(ROOT_PATH)/Engine/Math

include $(CLEAR_VARS)

LOCAL_MODULE := Math

LOCAL_C_INCLUDES := \
    $(ROOT_PATH)/Engine/Container

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/*.cpp))

include $(BUILD_STATIC_LIBRARY)


# Core library
LOCAL_PATH = $(ROOT_PATH)/Engine/Core

include $(CLEAR_VARS)

LOCAL_MODULE := Core

LOCAL_C_INCLUDES := \
    $(ROOT_PATH)/Engine/Container \
    $(ROOT_PATH)/Engine/Math \
    
LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/*.cpp))

include $(BUILD_STATIC_LIBRARY)


# Graphics library
LOCAL_PATH = $(ROOT_PATH)/Engine/Graphics

include $(CLEAR_VARS)

LOCAL_MODULE := Graphics

LOCAL_C_INCLUDES := \
    $(ROOT_PATH)/Engine/Container \
    $(ROOT_PATH)/Engine/Core \
    $(ROOT_PATH)/Engine/IO \
    $(ROOT_PATH)/Engine/Math \
    $(ROOT_PATH)/Engine/Resource \
    $(ROOT_PATH)/Engine/Scene \
    $(ROOT_PATH)/ThirdParty/GLee \
    $(ROOT_PATH)/ThirdParty/SDL/include \

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/*.cpp) \
    $(wildcard $(LOCAL_PATH)/OpenGL/*.cpp))

LOCAL_CFLAGS += -Wno-invalid-offsetof

include $(BUILD_STATIC_LIBRARY)


# IO library
LOCAL_PATH = $(ROOT_PATH)/Engine/IO

include $(CLEAR_VARS)

LOCAL_MODULE := IO

LOCAL_C_INCLUDES := \
    $(ROOT_PATH)/Engine/Container \
    $(ROOT_PATH)/Engine/Core \
    $(ROOT_PATH)/Engine/Math \

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/*.cpp))

include $(BUILD_STATIC_LIBRARY)


# Resource library
LOCAL_PATH = $(ROOT_PATH)/Engine/Resource

include $(CLEAR_VARS)

LOCAL_MODULE := Resource

LOCAL_C_INCLUDES := \
    $(ROOT_PATH)/Engine/Container \
    $(ROOT_PATH)/Engine/Core \
    $(ROOT_PATH)/Engine/IO \
    $(ROOT_PATH)/Engine/Math \
    $(ROOT_PATH)/ThirdParty/STB \
    $(ROOT_PATH)/ThirdParty/PugiXml/src \
    $(ROOT_PATH)/ThirdParty/Squish

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/*.cpp))

include $(BUILD_STATIC_LIBRARY)


# Scene library
LOCAL_PATH = $(ROOT_PATH)/Engine/Scene

include $(CLEAR_VARS)

LOCAL_MODULE := Scene

LOCAL_C_INCLUDES := \
    $(ROOT_PATH)/Engine/Container \
    $(ROOT_PATH)/Engine/Core \
    $(ROOT_PATH)/Engine/IO \
    $(ROOT_PATH)/Engine/Math \
    $(ROOT_PATH)/Engine/Resource

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/*.cpp))

LOCAL_CFLAGS += -Wno-invalid-offsetof

include $(BUILD_STATIC_LIBRARY)


# PugiXml library
LOCAL_PATH = $(ROOT_PATH)/ThirdParty/PugiXml

include $(CLEAR_VARS)

LOCAL_MODULE := PugiXml

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/src/*.cpp))

include $(BUILD_STATIC_LIBRARY)


# SDL library
LOCAL_PATH = $(ROOT_PATH)/ThirdParty/SDL

include $(CLEAR_VARS)

LOCAL_MODULE := SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/src/*.c) \
	$(wildcard $(LOCAL_PATH)/src/audio/*.c) \
	$(wildcard $(LOCAL_PATH)/src/audio/android/*.c) \
	$(wildcard $(LOCAL_PATH)/src/audio/dummy/*.c) \
	$(LOCAL_PATH)/src/atomic/SDL_atomic.c \
	$(LOCAL_PATH)/src/atomic/SDL_spinlock.c.arm \
	$(wildcard $(LOCAL_PATH)/src/core/android/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/cpuinfo/*.c) \
	$(wildcard $(LOCAL_PATH)/src/events/*.c) \
	$(wildcard $(LOCAL_PATH)/src/file/*.c) \
	$(wildcard $(LOCAL_PATH)/src/haptic/*.c) \
	$(wildcard $(LOCAL_PATH)/src/haptic/dummy/*.c) \
	$(wildcard $(LOCAL_PATH)/src/joystick/*.c) \
	$(wildcard $(LOCAL_PATH)/src/joystick/android/*.c) \
	$(wildcard $(LOCAL_PATH)/src/loadso/dlopen/*.c) \
	$(wildcard $(LOCAL_PATH)/src/stdlib/*.c) \
	$(wildcard $(LOCAL_PATH)/src/thread/*.c) \
	$(wildcard $(LOCAL_PATH)/src/thread/pthread/*.c) \
	$(wildcard $(LOCAL_PATH)/src/timer/*.c) \
	$(wildcard $(LOCAL_PATH)/src/timer/unix/*.c) \
	$(wildcard $(LOCAL_PATH)/src/video/*.c) \
	$(wildcard $(LOCAL_PATH)/src/video/android/*.c))

LOCAL_CFLAGS += -DGL_GLEXT_PROTOTYPES
LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog


# Squish library
LOCAL_PATH = $(ROOT_PATH)/ThirdParty/Squish

include $(CLEAR_VARS)

LOCAL_MODULE := Squish

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/*.cpp))

include $(BUILD_STATIC_LIBRARY)


# STB library
LOCAL_PATH = $(ROOT_PATH)/ThirdParty/STB

include $(CLEAR_VARS)

LOCAL_MODULE := STB

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/*.c))

include $(BUILD_STATIC_LIBRARY)


# Urho3D executable
LOCAL_PATH = $(ROOT_PATH)/Urho3D

include $(CLEAR_VARS)

LOCAL_MODULE := Urho3D

LOCAL_C_INCLUDES := $(ROOT_PATH)/Engine/Container \
    $(ROOT_PATH)/Engine/Core \
    $(ROOT_PATH)/Engine/Engine \
    $(ROOT_PATH)/Engine/IO \
    $(ROOT_PATH)/Engine/Math \
    $(ROOT_PATH)/Engine/Resource \
    $(ROOT_PATH)/Engine/Scene \
    $(ROOT_PATH)/Engine/Script

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/*.cpp))

# Note: libraries have to be listed in reverse order of dependency
LOCAL_STATIC_LIBRARIES := Graphics SDL Scene Resource PugiXml Squish STB IO Core Math Container

LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
