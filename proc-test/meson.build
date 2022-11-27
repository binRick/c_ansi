proc_test_srcs = [
  'proc-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
proc_test_include_dirs = [
  '.',
  inc,
]
proc_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  module_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  proc_dep,
]
proc_test_c_args = [
]
proc_test_link_args = [
]

proc_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  proc_test_exec = executable('proc-test',
     proc_test_srcs,
     dependencies: proc_test_deps,
     include_directories: proc_test_include_dirs,
     link_args: proc_test_link_args,
     c_args: proc_test_c_args,
     install: false,
  )
  test('proc-test', 
    proc_test_exec, args: ['-v','-a'],
    workdir: proc_test_test_dir,
  )
endif
