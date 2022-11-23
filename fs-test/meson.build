fs_test_srcs = [
  'fs-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
fs_test_include_dirs = [
  '.',
  inc,
]
fs_test_deps = [
  fs_dep,
  str_dep,
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
  img_dep,
  str_dep,
  cache_dep,
]
fs_test_c_args = [
]
fs_test_link_args = [
]

fs_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  fs_test_exec = executable('fs-test',
     fs_test_srcs,
     dependencies: fs_test_deps,
     include_directories: fs_test_include_dirs,
     link_args: fs_test_link_args,
     c_args: fs_test_c_args,
     install: false,
  )
  #test('fs-test', 
  #  fs_test_exec, args: ['-v','-a'],
  #  workdir: fs_test_test_dir,
  #)
endif
