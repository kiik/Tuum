
TARGET_NAME ?= tuum-agent

ARCHS = x64 arm arm64
MODES = debug release


MK=ninja
GYP= gyp


ARCH ?= native
MODE ?= release


all: native.release


native:
	$(GYP) --toplevel-dir=. --depth=. -f $(MK)

native.debug: native
	$(MK) -C out/native.debug

native.release: native
	$(MK) -C out/native.release

run: native.release
	./out/native.release/$(TARGET_NAME)

dbg: native.debug
	./out/native.debug/$(TARGET_NAME)

gdb: native.debug
	gdb ./out/native.debug/$(TARGET_NAME)
