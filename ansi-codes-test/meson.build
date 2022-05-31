ansi_codes_test_srcs = [
  'ansi-codes-test.c',
]
ansi_codes_test_deps = [
  incbin_dep,
  http_get_dep,
  curl_dep,
]

if get_option('enable-binaries')
  ansi_codes_test_exec = executable('ansi-codes-test',
     [
      ansi_codes_test_srcs,
     ],
     dependencies: ansi_codes_test_deps,
     include_directories: [],
  )
  if get_option('enable-binary-tests')
    test('ansi-codes-test', ansi_codes_test_exec, args: ['--test'])
  endif
endif
