ansi_rgb_utils_test_srcs = [
  'ansi-rgb-utils-test.c',
]
ansi_rgb_utils_test_incs = [
  inc,
]
ansi_rgb_utils_test_deps = [
  dbg_dep,
  log_dep,
  hsluv_c_dep,
  ansi_codes_dep,
  rgba_dep,
  module_dep,
  ansi_rgb_utils_dep,
  ansi_utils_dep,
]

if get_option('enable-binaries')
  ansi_rgb_utils_test_exec = executable('ansi-rgb-utils-test',
     ansi_rgb_utils_test_srcs,
     dependencies: ansi_rgb_utils_test_deps,
     include_directories: [ansi_rgb_utils_test_incs],
  )
  if get_option('enable-binary-tests')
    test('ansi-rgb-utils-test', ansi_rgb_utils_test_exec, args: ['--test'])
  endif
endif
