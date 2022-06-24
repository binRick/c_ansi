term_utils_test_srcs = [
  'term-utils-test.c',
]
term_utils_include_dirs = [
  '../submodules/termpaint',
]
term_utils_test_deps = [
       term_utils_dep,
]

if get_option('enable-binaries')
  term_utils_test_exec = executable('term-utils-test',
     [
      term_utils_test_srcs,
     ],
     dependencies: term_utils_test_deps,
     include_directories: [
       #       term_utils_include_dirs,
     ],
  )
  if get_option('enable-binary-tests')
    test('term-utils-test', passh_program, args: [term_utils_test_exec, '--test'])
  endif
endif
