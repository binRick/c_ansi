chan_utils_test_test_srcs = [
  'chan-utils-test-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
chan_utils_test_test_include_dirs = [
  '.',
  inc,
]
chan_utils_test_test_deps = [
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
  chan_dep,c_workqueue_dep,
  chan_utils_dep,
]
chan_utils_test_test_c_args = [
]
chan_utils_test_test_link_args = [
]

chan_utils_test_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  chan_utils_test_test_exec = executable('chan-utils-test-test',
     chan_utils_test_test_srcs,
     dependencies: chan_utils_test_test_deps,
     include_directories: chan_utils_test_test_include_dirs,
     link_args: chan_utils_test_test_link_args,
     c_args: chan_utils_test_test_c_args,
     install: false,
  )
  test('chan-utils-test-test', 
    chan_utils_test_test_exec, args: ['-v','-a'],
    workdir: chan_utils_test_test_test_dir,
  )
endif
