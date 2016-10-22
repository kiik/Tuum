{
  'targets': [
    {
      'target_name': 'libtdb',
      'type': 'static_library',

      'dependencies': [
        'libenv',
      ],

      'cflags': [
        '--std=c++11',
      ],
      'include_dirs': [
        'inc',
      ],
      'sources': [
        'src/tuum_db.cpp',
        'src/tuum_orm.cpp',

        'src/tdb_query.cpp',
      ],


      'direct_dependent_settings': {
        'include_dirs': [
          'inc',
        ],
      },

      'link_settings': {
        'libraries': [
          '-ltdb',
        ],
      },
    },
  ],
}
