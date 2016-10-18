
MODULE=main
MAIN_MODULE_PATH=.

include ../build/platform-id.mk

# Directory configuration
PROJECT_ROOT = ..

COMMON_BUILD=$(PROJECT_ROOT)/build
BUILD_PATH_BASE=$(COMMON_BUILD)/target

$(info Building for platform: $(PLATFORM))

ifeq (,$(MMODULE))
MAIN_MODULE = ctrlmod/tuum/rtex
else
MAIN_MODULE = ctrlmod/tuum/$(MMODULE)
endif

MAKE_DEPENDENCIES = $(MAIN_MODULE)

all: make_deps

include $(COMMON_BUILD)/common-tools.mk
include $(COMMON_BUILD)/recurse.mk
include $(COMMON_BUILD)/verbose.mk


clean:
	$(VERBOSE)$(RMDIR) $(BUILD_PATH_BASE)

.PHONY: clean
