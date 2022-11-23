ansi_image_utils_test_srcs = [
  'ansi-image-utils-test.c',
]
ansi_image_utils_include_dirs = [
  '.',
  '../ansi-image-utils',
  inc,
]
ansi_image_utils_test_deps = [
  ansi_image_utils_dep,
  list_dep,
  ansi_codes_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  c_greatest_dep,
  log_dep,
  debug_memory_dep,
  tinydir_dep,
]

if get_option('enable-binaries')
  ansi_image_utils_test_exec = executable('ansi-image-utils-test',
     ansi_image_utils_test_srcs,
     dependencies: ansi_image_utils_test_deps,
     include_directories: ansi_image_utils_include_dirs,
  )
  if get_option('enable-binary-tests')
    test('ansi-image-utils-test', passh_program, args: [ansi_image_utils_test_exec, '--test'])
  endif
endif
