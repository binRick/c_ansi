emojis_test_srcs = [
  'emojis-test.c',
]
emojis_include_dirs = [
  inc,
]
emojis_test_emojis = [
  emojis_dep,
  bench_dep,
  fort_dep,
  utf8_iterator_dep,
  djbhash_dep,
  c_vector_dep,
]
emojis_c_args = [
]
emojis_link_args = [
]

if get_option('enable-binaries')
  emojis_test_exec = executable('emojis-test',
     emojis_test_srcs,
     dependencies: emojis_test_emojis,
     include_directories: emojis_include_dirs,
     link_args: emojis_link_args,
     c_args: emojis_c_args,
     install: true,
  )
  if get_option('enable-binary-tests')
    test('emojis-test', 
      emojis_test_exec, args: ['-v','-a'],
      timeout: 20,
      is_parallel: true,
      workdir: meson.current_source_dir(),
      )
  endif
endif
