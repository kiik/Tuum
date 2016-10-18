{
  'targets': [
    {
      'target_name': 'libhtgui',
      'type': 'static_library',
      'defines': [

      ],
      'includes': [
        '../build/common.gypi'
      ],
      'cflags': [
        '--std=c++11',
      ],
      'variables': {
            'pkg-config': 'pkg-config'
      },
      'include_dirs': [
	'inc',

      ],
      'dependencies': [
        'libenv',
        'liblpx',
        'libhal',
      ],
      'sources': [
        'src/htgui.cpp',

        'src/tuum_scripting.cpp',
        'src/tuum_wsocs.cpp',
        'src/tuum_http.cpp',

        'src/WebSocketServer.cpp',
        'src/WSProtocol.cpp',
      ],

      'direct_dependent_settings': {
        'include_dirs': ['inc']
      },
    },
  ],
}
