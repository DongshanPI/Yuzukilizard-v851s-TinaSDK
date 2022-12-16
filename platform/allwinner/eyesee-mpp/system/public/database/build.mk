#
# 1. Set the path and clear environment
# 	TARGET_PATH := $(call my-dir)
# 	include $(ENV_CLEAR)
#
# 2. Set the source files and headers files
#	TARGET_SRC := xxx_1.c xxx_2.c
#	TARGET_INc := xxx_1.h xxx_2.h
#
# 3. Set the output target
#	TARGET_MODULE := xxx
#
# 4. Include the main makefile
#	include $(BUILD_BIN)
#
# Before include the build makefile, you can set the compilaion
# flags, e.g. TARGET_ASFLAGS TARGET_CFLAGS TARGET_CPPFLAGS
#

TARGET_PATH :=$(call my-dir)

########################################
include $(ENV_CLEAR)
TARGET_SRC := \
	db_connector.cpp \
	db_ctrl.cpp

TARGET_INC :=

TARGET_CPPFLAGS += \
	-fPIC

TARGET_LDFLAGS += \
	-lsqlite3 \
	-llog

TARGET_MODULE := libdatabase
include $(BUILD_SHARED_LIB)

#########################################
include $(ENV_CLEAR)

TARGET_SRC := \
	db_connector.cpp \
	db_ctrl.cpp

TARGET_INC :=

TARGET_CPPFLAGS +=

TARGET_STATIC_LIB := \
	# libsqlite3

TARGET_SHARED_LIB := \
	liblog

TARGET_MODULE := libdatabase
include $(BUILD_STATIC_LIB)
