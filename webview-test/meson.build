webview_test_srcs = [
  'webview-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
webview_test_include_dirs = [
  '.',
  inc,
]
webview_test_deps = [
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
  webview_dep,
]
webview_test_c_args = [
]
webview_test_link_args = [
]

webview_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  webview_test_exec = executable('webview-test',
     webview_test_srcs,
     dependencies: webview_test_deps,
     include_directories: webview_test_include_dirs,
     link_args: webview_test_link_args,
     c_args: webview_test_c_args,
     install: false,
  )
  test('webview-test', 
    webview_test_exec, args: ['-v','-a'],
    workdir: webview_test_test_dir,
  )
endif
