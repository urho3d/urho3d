ROOT_PATH := $(call my-dir)/../..
APP_ABI := armeabi armeabi-v7a
APP_STL := gnustl_static
APP_CPPFLAGS += -fexceptions -frtti -Wno-invalid-offsetof -DUSE_OPENGL -DENABLE_PROFILING
