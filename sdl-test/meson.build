sdl_test_srcs = [
  'sdl-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
sdl_test_include_dirs = [
  '.',
  inc,
]
sdl_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  lodepng_dep,
  bytes_dep,
  sdl_dep,
]
sdl_test_c_args = [
]
sdl_test_link_args = [
]

sdl_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  sdl_test_exec = executable('sdl-test',
     sdl_test_srcs,
     dependencies: sdl_test_deps,
     include_directories: sdl_test_include_dirs,
     link_args: sdl_test_link_args,
     c_args: sdl_test_c_args,
     install: false,
  )
  test('sdl-test', 
    sdl_test_exec, args: ['-v','-a'],
    workdir: sdl_test_test_dir,
  )
endif
