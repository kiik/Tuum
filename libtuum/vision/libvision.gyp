{
  'targets': [
    {
      'target_name': 'libvision',
      'type': 'static_library',

      'dependencies': [
        'libenv',
        'libhal',
        'libgeometry',
        'librtxmath',
        'libentities',
      ],

      'cflags': [
        '--std=c++11'
      ],
      'include_dirs': [
	'inc'
      ],
      'sources': [
        'src/Vision.cpp',
        'src/Perspective.cpp',
        'src/Feature.cpp',
        'src/Color.cpp',
        'src/Blob.cpp',
      ],


      'direct_dependent_settings': {
        'include_dirs': ['inc']
      },

      'link_settings': {
        'libraries': ['-lvision']
      },
    },
  ],
}
