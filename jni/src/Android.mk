LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/../SDL/include \
	$(LOCAL_PATH)/../SDL_mixer/include

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, $(wildcard $(LOCAL_PATH)/*.cpp)) \
	Engine/ddraw.cpp \
	Engine/dinput.cpp \
	Engine/io.cpp \
	Engine/windows.cpp

# 2001-era C++ code: keep it on C++14 and tolerate the old idioms it relies on.
LOCAL_CPPFLAGS := -std=gnu++14 -fpermissive -Wno-register -Wno-c++11-narrowing \
	-Wno-write-strings -Wno-deprecated-declarations
# Several Win32/FMOD stubs have no return statement; do not let clang turn
# "falling off the end" into a trap or into undefined control flow.
LOCAL_CPPFLAGS += -fno-strict-return

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog -landroid

include $(BUILD_SHARED_LIBRARY)
