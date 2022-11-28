qr_test_srcs = [
  'qr-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
qr_test_include_dirs = [
  '.',
  inc,
]
qr_test_deps = [
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
  qr_dep,
  incbin_dep,
  tempdir_dep,
]
qr_test_c_args = [
]
qr_test_link_args = [
]

qr_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  qr_test_exec = executable('qr-test',
     qr_test_srcs,
     dependencies: qr_test_deps,
     include_directories: qr_test_include_dirs,
     link_args: qr_test_link_args,
     c_args: qr_test_c_args,
     install: false,
  )
  test('qr-test', 
    qr_test_exec, args: ['-v','-a'],
    workdir: qr_test_test_dir,
  )
endif
