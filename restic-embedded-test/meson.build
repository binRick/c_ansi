restic_embedded_test_srcs = [
  'restic-embedded-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
restic_embedded_test_include_dirs = [
  '.',
  inc,
]
restic_embedded_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  incbin_dep,
  c_fsio_dep,
  c_stringfn_dep,
  subprocess_dep,
  logh_dep,
  uuid4_dep,
  tempdir_dep,
  ms_dep,
  bytes_dep,
  timestamp_dep,
  debug_memory_dep,
]
restic_embedded_test_c_args = [
]
restic_embedded_test_link_args = [
]

restic_embedded_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  restic_embedded_test_exec = executable('restic-embedded-test',
     restic_embedded_test_srcs,
     dependencies: restic_embedded_test_deps,
     include_directories: restic_embedded_test_include_dirs,
     link_args: restic_embedded_test_link_args,
     c_args: restic_embedded_test_c_args,
     install: false,
  )
  #test('restic-embedded-test', 
  #  restic_embedded_test_exec, args: ['-v','-a'],
  #  workdir: restic_embedded_test_test_dir,
  #)
endif
