{
  'variables': {
    'app': 'dev/melx',
  },
  'targets': [
    {
      'target_name': 'libuser',
      'type': 'static_library',
      'includes': [
        'applications/dev/melx/usr.gyp'
      ],

      'dependencies': [
        'libenv',
        'libhal',
        'liblpx',
        'libsystem',
        'librtxmath',
      ],

      'include_dirs': [
        'inc',
        'libraries'
      ],
      'sources': [
        'libraries/STM.cpp'
      ],

      'direct_dependent_settings': {
        'include_dirs': ['inc', 'libraries']
      },

      'link_settings': {
        'libraries': ['-lhal']
      },
    },
  ],
}
