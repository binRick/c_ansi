ansi_rgb_utils_test_srcs = [
  'ansi-rgb-utils-test.c',
]
ansi_rgb_utils_test_deps = [
]

if get_option('enable-binaries')
  ansi_rgb_utils_test_exec = executable('ansi-rgb-utils-test',
     [
      ansi_rgb_utils_test_srcs,
     ],
     dependencies: ansi_rgb_utils_test_deps,
     include_directories: [],
  )
  if get_option('enable-binary-tests')
    test('ansi-rgb-utils-test', ansi_rgb_utils_test_exec, args: ['--test'])
  endif
endif
