{
  'targets': [
    {
      'target_name': 'libhal',
      'type': 'static_library',

      'includes': [
	'src/phobos/hal.gypi'
      ],

      'include_dirs': [
	'inc'
      ],

      'all_dependent_settings': {
        'include_dirs': ['inc']
      },

      'link_settings': {
        'libraries': ['-lhal']
      },
    },
  ],
}
