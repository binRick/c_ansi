exec_test_srcs = [
  'exec-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
exec_test_include_dirs = [
  '.',
  inc,
]
exec_test_deps = [
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
  exec_dep,
]
exec_test_c_args = [
]
exec_test_link_args = [
]

exec_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  exec_test_exec = executable('exec-test',
     exec_test_srcs,
     dependencies: exec_test_deps,
     include_directories: exec_test_include_dirs,
     link_args: exec_test_link_args,
     c_args: exec_test_c_args,
     install: false,
  )
  #test('exec-test', 
  #  exec_test_exec, args: ['-v','-a'],
  #  workdir: exec_test_test_dir,
  #)
endif
