HTGUI_MODULE_PATH ?= $(PROJECT_ROOT)/htgui
include $(call rwildcard,$(HTGUI_MODULE_PATH)/,include.mk)

HTGUI_LIB_DIR = $(BUILD_PATH_BASE)/htgui/$(BUILD_TARGET_PLATFORM)
HTGUI_LIB_DEP = $(HTGUI_LIB_DIR)/libhtgui.a
