iface_test_srcs = [
  'iface-test.c',
  'frog.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
iface_test_include_dirs = [
  '.',
  inc,
]
iface_test_deps = [
  c_greatest_dep,
  metalang99_dep,
  c_vector_dep,
  c_fsio_dep,
  interface99_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  debug_memory_dep,
]
iface_test_c_args = [
]
iface_test_link_args = [
]

iface_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  iface_test_exec = executable('iface-test',
     iface_test_srcs,
     dependencies: iface_test_deps,
     include_directories: iface_test_include_dirs,
     link_args: iface_test_link_args,
     c_args: iface_test_c_args,
     install: false,
  )
  #test('iface-test', 
  #  iface_test_exec, args: ['-v','-a'],
  #  workdir: iface_test_test_dir,
  #)
endif
