HAL_SRC_DEIMOS_PATH = src/deimos

CSRC += $(call target_files,$(HAL_SRC_DEIMOS_PATH)/src/,*.c)
CPPSRC += $(call target_files,$(HAL_SRC_DEIMOS_PATH)/src/,*.cpp)

ASRC +=

CPPFLAGS += -std=gnu++11
