QTGUI_MODULE_PATH ?= $(PROJECT_ROOT)/qtgui
include $(call rwildcard,$(QTGUI_MODULE_PATH)/,include.mk)

QTGUI_LIB_DIR = $(BUILD_PATH_BASE)/qtgui/$(BUILD_TARGET_PLATFORM)
QTGUI_LIB_DEP = $(QTGUI_LIB_DIR)/libqtgui.a
