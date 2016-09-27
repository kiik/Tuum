
# defines
# PLATFORM_NAME - a unique name for the platform, can be used to organise sources
#                 by platform
# PRODUCT_DESC  - text description of the product ID

ifneq (,$(PLATFORM))

ifeq ("$(PLATFORM)","tracdrone")
PLATFORM_ID = 0
endif

ifeq (,$(PLATFORM_ID))
$(error "Unknown platform: $(PLATFORM))
endif

endif

ifndef PLATFORM_ID
PLATFORM_ID=0
endif

ARCH=gcc

ifeq ("$(PLATFORM_ID)","0")
PLATFORM=tracdrone
PLATFORM_NAME=tracdrone
PRODUCT_DESC=TRACDRONE Robot
DEFAULT_PRODUCT_ID=0
endif
