{
  'targets': [
    {
      'target_name': 'libentities',
      'type': 'static_library',

      'includes': [
        '../vision/vision-iface.gypi'
      ],
      'dependencies': [
        'libenv',
        'librtxmath',
        'libgeometry',
      ],

      'cflags': [
        '--std=c++11'
      ],
      'include_dirs': [
	'inc'
      ],
      'sources': [
        'src/Entity.cpp',
        'src/Ball.cpp',
        'src/Field.cpp',
        'src/Goal.cpp',
        'src/Robot.cpp',
      ],


      'all_dependent_settings': {
        'include_dirs': ['inc'],
	'includes': [
	  '../vision/vision-iface.gypi'
	],
      },

      'link_settings': {
        'libraries': ['-lentities']
      },
    },
  ],
}
