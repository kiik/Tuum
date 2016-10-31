{
  'targets': [
    {
      'target_name': 'libvision',
      'type': 'static_library',

      'dependencies': [
        'libenv',
        'libhal',
        'liblpx',
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
        'src/tuum_vision.cpp',

        'src/Perspective.cpp',
        'src/Feature.cpp',
        'src/Color.cpp',
        'src/Blob.cpp',

        'src/ppl/PipeBase.cpp',
        'src/ppl/FormatPipe.cpp',
        'src/ppl/GeometryPipe.cpp',
        'src/ppl/BlobPipe.cpp',

        'src/geom/vision_blobs.cpp',
        'src/geom/vision_lines.cpp',
        'src/geom/vision_corners.cpp',

        'src/feat/vision_balls.cpp',
        'src/feat/vision_goals.cpp',
        'src/feat/vision_robots.cpp',
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
