{
  'targets': [
    {
      'target_name': 'liblpx',
      'type': 'static_library',

      'dependencies': [
        'libenv',
        'libhal',
      ],

      'cflags': [
        '--std=c++11',
        '<!@(pkg-config --cflags gdkmm-3.0)',
        '<!@(pkg-config --cflags gtkmm-3.0)',
        '<!@(pkg-config --cflags sigc++-2.0)',
      ],
      'include_dirs': [
	'inc'
      ],
      'sources': [
        'src/tuum_lpx.cpp',
        'src/lpx_iformat.cpp',
      ],


      'direct_dependent_settings': {
        'include_dirs': ['inc'],
        'cflags': [
          '--std=c++11',
          '<!@(pkg-config --cflags gdkmm-3.0)',
          '<!@(pkg-config --cflags gtkmm-3.0)',
          '<!@(pkg-config --cflags sigc++-2.0)',
        ],
      },

      'link_settings': {
        'libraries': [
          '-llpx',
          '<!@(pkg-config --libs gdkmm-3.0)',
          '<!@(pkg-config --libs gtkmm-3.0)',
          '<!@(pkg-config --libs sigc++-2.0)',
        ],
      },
    },
  ],
}
