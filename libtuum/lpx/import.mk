LPX_MODULE_PATH ?= $(PROJECT_ROOT)/lpx
include $(call rwildcard,$(LPX_MODULE_PATH)/,include.mk)

LPX_LIB_DIR = $(BUILD_PATH_BASE)/lpx/$(BUILD_TARGET_PLATFORM)
LPX_LIB_DEP = $(LPX_LIB_DIR)/liblpx.a
