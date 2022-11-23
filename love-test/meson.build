love_test_srcs = [
  'love-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
love_test_include_dirs = [
  '.',
  inc,
]
love_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  incbin_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  glib_dep,
  vips_dep,
  love_dep,
]
love_test_c_args = [
  '-DINCBIN_SILENCE_BITCODE_WARNING',
]
love_test_link_args = [
]

love_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  love_test_exec = executable('love-test',
     love_test_srcs,
     dependencies: love_test_deps,
     include_directories: love_test_include_dirs,
     link_args: love_test_link_args,
     c_args: love_test_c_args,
     install: false,
  )
  #test('love-test', 
  #  love_test_exec, args: ['-v','-a'],
  #  workdir: love_test_test_dir,
  #)
endif
