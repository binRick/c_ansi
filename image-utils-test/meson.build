image_utils_test_srcs = [
  'image-utils-test.c',
]
image_utils_include_dirs = [
  '.',
  '../image-utils',
  inc,
]
image_utils_test_deps = [
  image_utils_dep,
  list_dep,
  ansi_codes_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  greatest_dep,
  logh_dep,
  debug_memory_dep,
  tinydir_dep,
]

if get_option('enable-binaries')
  image_utils_test_exec = executable('image-utils-test',
      image_utils_test_srcs,
     dependencies: image_utils_test_deps,
     include_directories: image_utils_include_dirs,
  )
  if get_option('enable-binary-tests')
    test('image-utils-test', image_utils_test_exec, args: ['--test'])
  endif
endif
