jwt_test_srcs = [
  'jwt-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
jwt_test_include_dirs = [
  '.',
  inc,
]
jwt_test_deps = [
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
  libjwt_dep,
]
jwt_test_c_args = [
]
jwt_test_link_args = [
]

jwt_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  jwt_test_exec = executable('jwt-test',
     jwt_test_srcs,
     dependencies: jwt_test_deps,
     include_directories: jwt_test_include_dirs,
     link_args: jwt_test_link_args,
     c_args: jwt_test_c_args,
     install: false,
  )
  #test('jwt-test', 
  #  jwt_test_exec, args: ['-v','-a'],
  #  workdir: jwt_test_test_dir,
  #)
endif
