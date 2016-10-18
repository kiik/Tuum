
TARGET_SRC_PATH = src

CSRC +=
CPPSRC += $(call target_files,src/,*.cpp)
ASRC +=

CPPFLAGS += -std=gnu++11
CPPFLAGS += $(shell pkg-config --cflags glib-2.0) $(shell pkg-config --cflags gdkmm-3.0) $(shell pkg-config --cflags gtkmm-3.0)
#$(shell pkg-config --libs glib-2.0)

BUILTINS_EXCLUDE =
CFLAGS += $(addprefix -fno-builtin-,$(BUILTINS_EXCLUDE))
