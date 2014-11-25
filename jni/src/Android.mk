LOCAL_PATH := $(call my-dir)


#include $(CLEAR_VARS)

#LOCAL_MODULE            := fmodex
#LOCAL_SRC_FILES         := fmod/$(TARGET_ARCH_ABI)/libfmodex.so
#LOCAL_EXPORT_C_INCLUDES := fmod//inc

#include $(PREBUILT_SHARED_LIBRARY)



include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
LOCAL_SRC_FILES += ../SDL/src/main/android/SDL_android_main.c 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include


LOCAL_CPP_INCLUDES += \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/*.h) )
LOCAL_SRC_FILES += \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/*.cpp) )
	

LOCAL_CPP_INCLUDES    += Engine/ddraw.h
LOCAL_CPP_INCLUDES    += Engine/dinput.h
LOCAL_CPP_INCLUDES    += Engine/io.h
LOCAL_CPP_INCLUDES    += Engine/windows.h

LOCAL_SRC_FILES    += Engine/ddraw.cpp
LOCAL_SRC_FILES    += Engine/dinput.cpp
LOCAL_SRC_FILES    += Engine/io.cpp
LOCAL_SRC_FILES    += Engine/windows.cpp

#LOCAL_SRC_FILES += main.cpp
#LOCAL_SRC_FILES += caller.cpp
#LOCAL_CPP_INCLUDES += main.h
#LOCAL_CPP_INCLUDES += caller.h

	

LOCAL_SHARED_LIBRARIES := SDL2
LOCAL_SHARED_LIBRARIES += SDL2_mixer
#LOCAL_SHARED_LIBRARIES += fmodex

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog -landroid

include $(BUILD_SHARED_LIBRARY)
