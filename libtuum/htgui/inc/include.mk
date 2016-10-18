
# Add include to all objects built for this target
INCLUDE_DIRS += $(HTGUI_MODULE_PATH)/inc


INCLUDE_DIRS += /usr/include/gdkmm-3.0 #~/Qt/5.6/gcc_64/include #/usr/include/x86_64-linux-gnu/qt5
#CPPFLAGS += -DQT_NO_DEBUG_OUTPUT -DCONFIG_PC_PLATFORM -DQT_NO_DEBUG -DQT_QUICK_LIB -DQT_GUI_LIB -DQT_QML_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB
CPPFLAGS += -fPIC
