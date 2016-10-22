{
  'targets': [
    {
      'target_name': 'liblpx',
      'type': 'static_library',

      'dependencies': [
        'libenv',
        'libhal',
        'libtdb',
      ],

      'cflags': [
        '--std=c++11',
        '<!@(pkg-config --cflags gdkmm-3.0)',
        '<!@(pkg-config --cflags gtkmm-3.0)',
        '<!@(pkg-config --cflags sigc++-2.0)',
      ],
      'include_dirs': [
        'inc',
        '/usr/local/include/glip-lib',
      ],
      'sources': [
        'src/tuum_lpx.cpp',
        'src/tuum_ogl.cpp',

        'src/lpx_iformat.cpp',

        'src/tuum_file.cpp',
        'src/tuum_dbfile.cpp',
        'src/tuum_fs.cpp',
      ],


      'direct_dependent_settings': {
        'include_dirs': [
          'inc',
        ],
        'cflags': [
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
          '-lglip',
          '<!@(pkg-config --libs gl)',
          '<!@(pkg-config --libs glfw3)',
          '<!@(pkg-config --libs glew)',
          '<!@(pkg-config --libs sqlite3)',
        ],
      },
    },
  ],
}
