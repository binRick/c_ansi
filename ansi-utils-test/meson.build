ansi_utils_test_srcs = [
  'ansi-utils-test.c',
]
ansi_utils_include_dirs = [
]
ansi_utils_test_deps = [
       ansi_utils_dep,
]

if get_option('enable-binaries')
  ansi_utils_test_exec = executable('ansi-utils-test',
     [
      ansi_utils_test_srcs,
     ],
     dependencies: ansi_utils_test_deps,
     include_directories: [
       ansi_utils_include_dirs,
     ],
  )
  if get_option('enable-binary-tests')
    test('ansi-utils-test', ansi_utils_test_exec, args: ['--test'])
  endif
endif
