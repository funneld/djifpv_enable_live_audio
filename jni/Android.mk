LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -fPIC -std=c99
LOCAL_LDFLAGS += -fPIC 
LOCAL_LDLIBS := -llog

LOCAL_MODULE    := enable_live_audio
LOCAL_SRC_FILES := enable_live_audio.c

include $(BUILD_SHARED_LIBRARY)
