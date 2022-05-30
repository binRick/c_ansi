term_termpaint_test_srcs = [
  'term-termpaint-test.c',
]
term_termpaint_test_include_dirs = [
  '../submodules/termpaint',
]
term_termpaint_test_deps = [
  term_termpaint_dep,
]

if get_option('enable-binaries')
  term_termpaint_test_exec = executable('term-termpaint-test',
     [
      term_termpaint_test_srcs,
     ],
     dependencies: term_termpaint_test_deps,
     include_directories: [
       term_termpaint_test_include_dirs,
     ],
  )
  if get_option('enable-binary-tests')
    test('term-termpaint-test', term_termpaint_test_exec, args: ['--test'])
  endif
endif
