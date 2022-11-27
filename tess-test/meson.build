tess_test_srcs = [
  'tess-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
tess_test_include_dirs = [
  '.',
  inc,
]
tess_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  tess_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  tess_dep,
  bytes_dep,
]
tess_test_c_args = [
]
tess_test_link_args = [
]

tess_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  tess_test_exec = executable('tess-test',
     tess_test_srcs,
     dependencies: tess_test_deps,
     include_directories: tess_test_include_dirs,
     link_args: tess_test_link_args,
     c_args: tess_test_c_args,
     install: false,
  )
  test('tess-test', 
    tess_test_exec, args: ['-v','-a'],
    workdir: tess_test_test_dir,
  )
endif
