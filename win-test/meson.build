win_test_srcs = [
  'win-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
win_test_include_dirs = [
  '.',
  inc,
]
win_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  win_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]
win_test_c_args = [
]
win_test_link_args = [
]

win_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  win_test_exec = executable('win-test',
     win_test_srcs,
     dependencies: win_test_deps,
     include_directories: win_test_include_dirs,
     link_args: win_test_link_args,
     c_args: win_test_c_args,
     install: false,
  )
  test('win-test', 
    win_test_exec, args: ['-v','-a'],
    workdir: win_test_test_dir,
  )
endif
