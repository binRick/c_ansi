tp_test_srcs = [
  'tp-test.c',
]
tp_test_inc = [
  inc,
]
tp_test_deps = [
  tp_dep,
  termpaint_dep,
]

if get_option('enable-binaries')
  tp_test_exec = executable('tp-test',
     [
      tp_test_srcs,
     ],
     dependencies: tp_test_deps,
     include_directories: [
       tp_test_inc,
     ],
  )
  if get_option('enable-binary-tests')
    #    test('tp-test', tp_test_exec, args: ['--test'])
  endif
endif
