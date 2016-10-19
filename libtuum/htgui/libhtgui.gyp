{
  'targets': [
    {
      'target_name': 'libhtgui',
      'type': 'static_library',
      'defines': [

      ],
      'dependencies': [
        'libenv',
        'liblpx',
        'libhal',
      ],

      'includes': [
        '../build/common.gypi'
      ],
      'variables': {
        'pkg-config': 'pkg-config'
      },

      'cflags': [
        '--std=c++11',
      ],
      'include_dirs': [
	'inc',
      ],
     'sources': [
        'src/htgui.cpp',

        'src/tuum_scripting.cpp',
        'src/tuum_wsocs.cpp',
        'src/tuum_http.cpp',
        'src/tuum_wsproto.cpp',

        'src/WSContext.cpp',
        'src/WebSocketServer.cpp',
      ],

      'direct_dependent_settings': {
        'include_dirs': ['inc']
      },
    },
  ],
}
