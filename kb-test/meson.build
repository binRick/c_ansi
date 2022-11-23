kb_test_srcs = [
  'kb-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
kb_test_include_dirs = [
  '.',
  inc,
]
kb_test_deps = [
  c_greatest_dep,
  kb_dep,
  ansi_codes_dep,
  glib_dep,vips_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]
kb_test_c_args = [
]
kb_test_link_args = [
]

kb_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  kb_test_exec = executable('kb-test',
     kb_test_srcs,
     dependencies: kb_test_deps,
     include_directories: kb_test_include_dirs,
     link_args: kb_test_link_args,
     c_args: kb_test_c_args,
     install: false,
  )
  #test('kb-test', 
  #  kb_test_exec, args: ['-v','-a'],
  #  workdir: kb_test_test_dir,
  #)
endif
