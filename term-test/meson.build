term_test_srcs = [
  'term_test.c',
]

term_test_deps = [
     ms_dep,
     bytes_dep,
     c_embed_dep,
     generic_print_dep,
     debug_print_h_dep,
     djbhash_dep,
     c_string_buffer_dep,
     timestamp_dep,
     parson_shared_dep,
     cstringfn_dep,
     fs_dep,
     rgba_dep, 
     cargs_dep,
     c_timer_dep,
     c_fsio_dep,
     termpaint_dep,
     ansi_codes_dep,
     ansi_utils_dep,
     ansi_rgb_utils_dep,
     term_utils_dep,
]

if get_option('enable-binaries')
  term_test_exec = executable('term-test',
     [
      term_test_srcs,
     ],
     dependencies: term_test_deps,
     include_directories: [],
  )
  if get_option('enable-binary-tests')
    test('term-test', term_test_exec, args: ['--test'])
  endif
endif
