qoir_test_srcs = [
  'qoir-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
qoir_test_include_dirs = [
  '.',
  inc,
]
qoir_test_deps = [
  c_greatest_dep,
  incbin_dep,
  tempdir_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  qoir_module_dep,
]
qoir_test_c_args = [
]
qoir_test_link_args = [
]

qoir_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  qoir_test_exec = executable('qoir-test',
     qoir_test_srcs,
     dependencies: qoir_test_deps,
     include_directories: qoir_test_include_dirs,
     link_args: qoir_test_link_args,
     c_args: qoir_test_c_args,
     install: false,
  )
  test('qoir-test', 
    qoir_test_exec, args: ['-v','-a'],
    workdir: qoir_test_test_dir,
  )
endif
