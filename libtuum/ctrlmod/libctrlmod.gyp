{
  'targets': [
    {
      'target_name': 'tuum',
      'type': 'executable',

      'includes': [
        '../build/common.gypi',
        'tuum/rtex/ctrlmod.gypi'
      ],

      'libraries': [
        '-Lobj',
        '-lpthread',
        '-lboost_system',
        '-lboost_thread',
        '-lboost_program_options',
        '-lboost_coroutine',
        '-lboost_context',
        '-lboost_filesystem',
        '-lglut',
        '-lwebsockets',
      ],
    },
  ],
}
