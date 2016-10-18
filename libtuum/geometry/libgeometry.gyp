{
  'targets': [
    {
      'target_name': 'libgeometry',
      'type': 'static_library',

      'dependencies': [

      ],

      'cflags': [
        '--std=c++11'
      ],
      'include_dirs': [
	'inc'
      ],
      'sources': [
        'src/Circle.cpp',
        'src/Line2D.cpp',
        'src/Point2D.cpp',
        'src/Rectangle.cpp',
      ],


      'all_dependent_settings': {
        'include_dirs': ['inc']
      },

      'link_settings': {
        'libraries': ['-lgeometry']
      },
    },
  ],
}
