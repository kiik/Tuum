HAL_SRC_PHOBOS_PATH = src/phobos

CSRC += $(call target_files,$(HAL_SRC_PHOBOS_PATH)/src/,*.c)
CPPSRC += $(call target_files,$(HAL_SRC_PHOBOS_PATH)/src/,*.cpp)

ASRC +=

CPPFLAGS += -std=gnu++11
