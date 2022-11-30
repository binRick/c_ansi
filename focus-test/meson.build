focus_test_srcs = [
  'focus-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
focus_test_include_dirs = [
  '.',
  inc,
]
focus_test_deps = [
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
  focus_dep,
  parson_dep,
]
focus_test_c_args = [
]
focus_test_link_args = [
]

focus_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  focus_test_exec = executable('focus-test',
     focus_test_srcs,
     dependencies: focus_test_deps,
     include_directories: focus_test_include_dirs,
     link_args: focus_test_link_args,
     c_args: focus_test_c_args,
     install: false,
  )
  test('focus-test', 
    focus_test_exec, args: ['-v','-a'],
    workdir: focus_test_test_dir,
  )
endif
