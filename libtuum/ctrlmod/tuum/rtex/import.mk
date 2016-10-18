RTEX_MODULE_VERSION ?= 0
RTEX_MODULE_PATH ?= $(PROJECT_ROOT)/modules/rtex
include $(call rwildcard,$(RTEX_MODULE_PATH)/,include.mk)
