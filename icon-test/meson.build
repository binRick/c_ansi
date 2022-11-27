icon_test_srcs = [
  'icon-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
icon_test_include_dirs = [
  '.',
  inc,
]
icon_test_deps = [
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
]
icon_test_c_args = [
]
icon_test_link_args = [
]

icon_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  icon_test_exec = executable('icon-test',
     icon_test_srcs,
     dependencies: icon_test_deps,
     include_directories: icon_test_include_dirs,
     link_args: icon_test_link_args,
     c_args: icon_test_c_args,
     install: false,
  )
  test('icon-test', 
    icon_test_exec, args: ['-v','-a'],
    workdir: icon_test_test_dir,
  )
endif
