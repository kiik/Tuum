{
  'targets': [
    {
      'target_name': 'libloc',
      'type': 'static_library',

      'dependencies': [
        'librtxmath'
      ],

      'cflags': [
        '--std=c++11'
      ],
      'include_dirs': [
	'inc'
      ],
      'sources': [
        'src/loc_core.cpp',
        'src/particlef.cpp',
      ],


      'all_dependent_settings': {
        'include_dirs': ['inc']
      },

      'link_settings': {
        'libraries': ['-lloc']
      },
    },
  ],
}
