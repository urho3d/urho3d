# AngelScript library
LOCAL_PATH = $(ROOT_PATH)/ThirdParty/AngelScript

include $(CLEAR_VARS)

LOCAL_MODULE := AngelScript

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/source/*.cpp) \
    $(LOCAL_PATH)/source/as_callfunc_arm_gcc.S)

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/include

include $(BUILD_STATIC_LIBRARY)


# Bullet library
LOCAL_PATH = $(ROOT_PATH)/ThirdParty/Bullet

include $(CLEAR_VARS)

LOCAL_MODULE := Bullet

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/src/BulletCollision/BroadPhaseCollision/*.cpp) \
    $(wildcard $(LOCAL_PATH)/src/BulletCollision/CollisionDispatch/*.cpp) \
    $(wildcard $(LOCAL_PATH)/src/BulletCollision/CollisionShapes/*.cpp) \
    $(wildcard $(LOCAL_PATH)/src/BulletCollision/Gimpact/*.cpp) \
    $(wildcard $(LOCAL_PATH)/src/BulletCollision/NarrowPhaseCollision/*.cpp) \
    $(wildcard $(LOCAL_PATH)/src/BulletDynamics/Character/*.cpp) \
    $(wildcard $(LOCAL_PATH)/src/BulletDynamics/ConstraintSolver/*.cpp) \
    $(wildcard $(LOCAL_PATH)/src/BulletDynamics/Dynamics/*.cpp) \
    $(wildcard $(LOCAL_PATH)/src/BulletDynamics/Vehicle/*.cpp) \
    $(wildcard $(LOCAL_PATH)/src/BulletSoftBody/*.cpp) \
    $(wildcard $(LOCAL_PATH)/src/LinearMath/*.cpp))

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/src

include $(BUILD_STATIC_LIBRARY)


# FreeType library
LOCAL_PATH = $(ROOT_PATH)/ThirdParty/FreeType

include $(CLEAR_VARS)

LOCAL_MODULE := FreeType

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(LOCAL_PATH)/src/autofit/autofit.c \
    $(LOCAL_PATH)/src/base/ftbase.c \
    $(LOCAL_PATH)/src/base/ftbbox.c \
    $(LOCAL_PATH)/src/base/ftbitmap.c \
    $(LOCAL_PATH)/src/base/ftfstype.c \
    $(LOCAL_PATH)/src/base/ftgasp.c \
    $(LOCAL_PATH)/src/base/ftglyph.c \
    $(LOCAL_PATH)/src/base/ftgxval.c \
    $(LOCAL_PATH)/src/base/ftinit.c \
    $(LOCAL_PATH)/src/base/ftlcdfil.c \
    $(LOCAL_PATH)/src/base/ftmm.c \
    $(LOCAL_PATH)/src/base/ftotval.c \
    $(LOCAL_PATH)/src/base/ftpatent.c \
    $(LOCAL_PATH)/src/base/ftpfr.c \
    $(LOCAL_PATH)/src/base/ftstroke.c \
    $(LOCAL_PATH)/src/base/ftsynth.c \
    $(LOCAL_PATH)/src/base/ftsystem.c \
    $(LOCAL_PATH)/src/base/fttype1.c \
    $(LOCAL_PATH)/src/base/ftwinfnt.c \
    $(LOCAL_PATH)/src/bdf/bdf.c \
    $(LOCAL_PATH)/src/cache/ftccache.c \
    $(LOCAL_PATH)/src/cff/cff.c \
    $(LOCAL_PATH)/src/cid/type1cid.c \
    $(LOCAL_PATH)/src/gzip/ftgzip.c \
    $(LOCAL_PATH)/src/lzw/ftlzw.c \
    $(LOCAL_PATH)/src/pcf/pcf.c \
    $(LOCAL_PATH)/src/pfr/pfr.c \
    $(LOCAL_PATH)/src/psaux/psaux.c \
    $(LOCAL_PATH)/src/pshinter/pshinter.c \
    $(LOCAL_PATH)/src/psnames/psmodule.c \
    $(LOCAL_PATH)/src/raster/raster.c \
    $(LOCAL_PATH)/src/sfnt/sfnt.c \
    $(LOCAL_PATH)/src/smooth/smooth.c \
    $(LOCAL_PATH)/src/truetype/truetype.c \
    $(LOCAL_PATH)/src/type1/type1.c \
    $(LOCAL_PATH)/src/type42/type42.c \
    $(LOCAL_PATH)/src/winfonts/winfnt.c)

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/include

LOCAL_CFLAGS += -DFT2_BUILD_LIBRARY

include $(BUILD_STATIC_LIBRARY)


# kNet library
LOCAL_PATH = $(ROOT_PATH)/ThirdParty/kNet

include $(CLEAR_VARS)

LOCAL_MODULE := kNet

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/include

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/src/*.cpp) \
    $(wildcard $(LOCAL_PATH)/src/unix/*.cpp))

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

include $(BUILD_STATIC_LIBRARY)


# Squish library
LOCAL_PATH = $(ROOT_PATH)/ThirdParty/Squish

include $(CLEAR_VARS)

LOCAL_MODULE := Squish

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/*.cpp))

include $(BUILD_STATIC_LIBRARY)


# StanHull library
LOCAL_PATH = $(ROOT_PATH)/ThirdParty/StanHull

include $(CLEAR_VARS)

LOCAL_MODULE := StanHull

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
LOCAL_PATH = $(ROOT_PATH)

include $(CLEAR_VARS)

LOCAL_MODULE := Urho3D

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/Engine/Audio \
    $(LOCAL_PATH)/Engine/Container \
    $(LOCAL_PATH)/Engine/Core \
    $(LOCAL_PATH)/Engine/Engine \
    $(LOCAL_PATH)/Engine/Graphics \
    $(LOCAL_PATH)/Engine/Input \
    $(LOCAL_PATH)/Engine/IO \
    $(LOCAL_PATH)/Engine/Math \
    $(LOCAL_PATH)/Engine/Network \
    $(LOCAL_PATH)/Engine/Physics \
    $(LOCAL_PATH)/Engine/Resource \
    $(LOCAL_PATH)/Engine/Scene \
    $(LOCAL_PATH)/Engine/Script \
    $(LOCAL_PATH)/Engine/UI \
    $(LOCAL_PATH)/ThirdParty/AngelScript/include \
    $(LOCAL_PATH)/ThirdParty/Bullet/src \
    $(LOCAL_PATH)/ThirdParty/FreeType/include \
    $(LOCAL_PATH)/ThirdParty/kNet/include \
    $(LOCAL_PATH)/ThirdParty/PugiXml/src \
    $(LOCAL_PATH)/ThirdParty/SDL/include \
    $(LOCAL_PATH)/ThirdParty/Squish \
    $(LOCAL_PATH)/ThirdParty/StanHull \
    $(LOCAL_PATH)/ThirdParty/STB

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
    $(wildcard $(LOCAL_PATH)/Engine/Audio/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/Container/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/Core/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/Engine/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/Graphics/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/Graphics/OpenGL/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/Input/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/IO/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/Math/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/Network/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/Physics/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/Resource/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/Scene/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/Script/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Engine/UI/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Urho3D/*.cpp) \
    $(wildcard $(LOCAL_PATH)/ThirdParty/SDL/src/main/android/*.cpp))

LOCAL_STATIC_LIBRARIES := AngelScript Bullet FreeType kNet PugiXml SDL Squish StanHull STB

LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
