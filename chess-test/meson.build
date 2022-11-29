chess_test_srcs = [
  'chess-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
chess_test_include_dirs = [
  '.',
  inc,
]
chess_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  incbin_dep,
  librnd_dep,
  tempdir_dep,
  timestamp_dep,
  str_dep,
  async_dep,
  string_utils_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  chess_dep,
]
chess_test_c_args = [
]
chess_test_link_args = [
]

chess_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  chess_test_exec = executable('chess-test',
     chess_test_srcs,
     dependencies: chess_test_deps,
     include_directories: chess_test_include_dirs,
     link_args: chess_test_link_args,
     c_args: chess_test_c_args,
     install: false,
  )
  test('chess-test', 
    chess_test_exec, args: ['-v','-a'],
    workdir: chess_test_test_dir,
  )
endif
