str_test_srcs = [
  'str-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
str_test_include_dirs = [
  '.',
  inc,
]
str_test_deps = [
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
  str_dep,
]
str_test_c_args = [
]
str_test_link_args = [
]

str_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  str_test_exec = executable('str-test',
     str_test_srcs,
     dependencies: str_test_deps,
     include_directories: str_test_include_dirs,
     link_args: str_test_link_args,
     c_args: str_test_c_args,
     install: false,
  )
  test('str-test', 
    str_test_exec, args: ['-v','-a'],
    workdir: str_test_test_dir,
  )
endif
