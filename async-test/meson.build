async_test_srcs = [
  'async-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
async_test_include_dirs = [
  '.',
  inc,
]
async_test_deps = [
  async_dep,
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
async_test_c_args = [
]
async_test_link_args = [
]

async_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  async_test_exec = executable('async-test',
     async_test_srcs,
     dependencies: async_test_deps,
     include_directories: async_test_include_dirs,
     link_args: async_test_link_args,
     c_args: async_test_c_args,
     install: false,
  )
  test('async-test', 
    async_test_exec, args: ['-v','-a'],
    workdir: async_test_test_dir,
  )
endif
