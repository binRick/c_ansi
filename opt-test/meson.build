opt_test_srcs = [
  'opt-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
opt_test_include_dirs = [
  '.',
  inc,
]
opt_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  incbin_dep,
  tempdir_dep,
  which_dep,
  chan_dep,
  c_eventemitter_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  opt_dep,
]
opt_test_c_args = [
]
opt_test_link_args = [
]

opt_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  opt_test_exec = executable('opt-test',
     opt_test_srcs,
     dependencies: opt_test_deps,
     include_directories: opt_test_include_dirs,
     link_args: opt_test_link_args,
     c_args: opt_test_c_args,
     install: false,
  )
  test('opt-test', 
    opt_test_exec, args: ['-v','-a'],
    workdir: opt_test_test_dir,
  )
endif
