{
  'dependencies': [
    'libenv',
    'liblpx',
    'libhal',

    'libsystem',
    'libhtgui',

    'libuser',
  ],

 'cflags': [
    '--std=c++11'
  ],
  'include_dirs': [
    'inc'
  ],
  'sources': [
    'src/rtx_ctl.cpp',
    'src/rtx_fb.cpp',
    'src/rtx_tfb.cpp',
    'src/rtx_cmds.cpp',

    'src/rtex_init.cpp',

    'src/LogicManager.cpp',
    'src/RobotexUIServer.cpp',

    'src/protocol/rtex_DriveProtocol.cpp',
  ],

}
