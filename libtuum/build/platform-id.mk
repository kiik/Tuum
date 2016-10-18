
# defines
# PLATFORM_NAME - a unique name for the platform, can be used to organise sources
#                 by platform
# PRODUCT_DESC  - text description of the product ID

ifneq (,$(PLATFORM))

ifeq ("$(PLATFORM)","phobos")
PLATFORM_ID = 1
endif

ifeq ("$(PLATFORM)","deimos")
PLATFORM_ID = 2
endif

ifeq ("$(PLATFORM)","tracdrone")
PLATFORM_ID = 10
endif

ifeq (,$(PLATFORM_ID))
$(error "Unknown platform: $(PLATFORM))
endif

endif

ifndef PLATFORM_ID
PLATFORM_ID=2
endif

ARCH=gcc

ifeq ("$(PLATFORM_ID)","1")
PLATFORM=phobos
PLATFORM_NAME=phobos
PRODUCT_DESC=Tuum Robotex 15' Robot platform
DEFAULT_PRODUCT_ID=1
endif

ifeq ("$(PLATFORM_ID)","2")
PLATFORM=deimos
PLATFORM_NAME=deimos
PRODUCT_DESC=Tuum Robotex 16' Robot platform
DEFAULT_PRODUCT_ID=2
endif

ifeq ("$(PLATFORM_ID)","10")
PLATFORM=tracdrone
PLATFORM_NAME=tracdrone
PRODUCT_DESC=TRACDRONE Robot
DEFAULT_PRODUCT_ID=10
endif
