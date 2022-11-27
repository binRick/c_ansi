ts_test_srcs = [
  'ts-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
ts_test_include_dirs = [
  '.',
  inc,
]
ts_test_deps = [
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
  ts_dep,
]
ts_test_c_args = [
]
ts_test_link_args = [
]

ts_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  ts_test_exec = executable('ts-test',
     ts_test_srcs,
     dependencies: ts_test_deps,
     include_directories: ts_test_include_dirs,
     link_args: ts_test_link_args,
     c_args: ts_test_c_args,
     install: false,
  )
  test('ts-test', 
    ts_test_exec, args: ['-v','-a'],
    workdir: ts_test_test_dir,
  )
endif
