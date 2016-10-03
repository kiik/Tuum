MODULE=rtex

PROJECT_ROOT=../../..
RTEX_MODULE_PATH=.

BUILD_PATH_EXT = $(BUILD_TARGET_PLATFORM)
HAL_LINK :=

DEPENDENCIES = user hal system vision loc entities geometry rtxmath platform htgui
MAKE_DEPENDENCIES = user hal system vision loc entities geometry rtxmath platform htgui

include ../modular.mk
include $(PROJECT_ROOT)/build/platform-id.mk

# BOOST
LIBS += $(MAKE_DEPENDENCIES) pthread boost_system boost_thread boost_program_options boost_coroutine boost_context boost_filesystem

# GUI
LIBS += Qt5Quick Qt5Widgets Qt5Gui Qt5Qml Qt5Network Qt5Core glut GL GLU GLEW assimp websockets

# VISION
# FIXME: Libraries added due to gtkmm usage; should be LDLIBS += `pkg-config gtkmm-3.0 --libs`
LIBS += gtkmm-3.0 atkmm-1.6 gdkmm-3.0 giomm-2.4 pangomm-1.4 glibmm-2.4 gtk-3 gdk-3 pangocairo-1.0 pango-1.0 atk-1.0 cairo-gobject gio-2.0 cairomm-1.0 cairo sigc-2.0 gdk_pixbuf-2.0 gobject-2.0 glib-2.0

LIB_DEPS += $(USER_LIB_DEP) $(VISION_LIB_DEP) $(SYSTEM_LIB_DEP) $(HAL_LIB_DEP) $(LOC_LIB_DEP) $(ENTITIES_LIB_DEP) $(GEOMETRY_LIB_DEP) $(RTXMATH_LIB_DEP) $(PLATFORM_LIB_DEP) $(HTGUI_LIB_DEP)

LIB_DIRS += $(dir $(LIB_DEPS))

LDFLAGS += -Wl,-O1
CPPFlags += -pipe -O2 -Wall -W -D_REENTRANT -I/usr/include

TARGET=out elf

CPPFLAGS += -g -DQT_NO_DEBUG_OUTPUT -DCONFIG_PC_PLATFORM -DQT_NO_DEBUG -DQT_QUICK_LIB -DQT_GUI_LIB -DQT_QML_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB

include $(PROJECT_ROOT)/build/tlm.mk

#$(call check_modular)
