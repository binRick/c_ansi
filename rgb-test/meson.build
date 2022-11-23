rgb_test_srcs = [
  'rgb-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
rgb_test_include_dirs = [
  '.',
  inc,
]
rgb_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  ansi_rgb_utils_dep,
]
rgb_test_c_args = [
]
rgb_test_link_args = [
]

rgb_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  rgb_test_exec = executable('rgb-test',
     rgb_test_srcs,
     dependencies: rgb_test_deps,
     include_directories: rgb_test_include_dirs,
     link_args: rgb_test_link_args,
     c_args: rgb_test_c_args,
     install: false,
  )
  test('rgb-test', 
    rgb_test_exec, args: ['-v','-a'],
    workdir: rgb_test_test_dir,
  )
endif
