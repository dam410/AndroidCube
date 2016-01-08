LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := sfml-example

LOCAL_SRC_FILES += src/logger/Log.cpp
LOCAL_SRC_FILES += src/Cube.cpp

LOCAL_SRC_FILES += src/main.cpp

LOCAL_SHARED_LIBRARIES := sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network

LOCAL_LDLIBS := -llog -lGLESv1_CM

LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main

LOCAL_C_INCLUDES += jni/include
LOCAL_C_INCLUDES += jni/glues/source

include $(BUILD_SHARED_LIBRARY)

$(call import-module,sfml)
