vt100_utils_test_srcs = [
  'vt100-utils-test.c',
]
vt100_utils_include_dirs = [
  '.',
  inc,
]
vt100_utils_test_deps = [
  vt100_utils_dep,
]

if get_option('enable-binaries')
  vt100_utils_test_exec = executable('vt100-utils-test',
     [
      vt100_utils_test_srcs,
     ],
     dependencies: vt100_utils_test_deps,
     include_directories: [
       vt100_utils_include_dirs,
     ],
  )
  if get_option('enable-binary-tests')
    #    test('vt100-utils-test', passh_program, args: [vt100_utils_test_exec, '--test'])
  endif
endif
