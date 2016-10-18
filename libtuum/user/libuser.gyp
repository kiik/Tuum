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
      'include_dirs': [
	'inc'
      ],

      'dependencies': [
        'libenv',
        'libhal',
        'libsystem',
        'librtxmath',
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
