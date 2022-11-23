async_srcs = [
  'async.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

async_include_dirs = [
  '.',
  inc,
]

async_deps = [
  c_workqueue_dep,
  chan_dep,interface99_dep,clamp_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  c_workqueue_dep,chan_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]

async_c_args = [
]

async_link_args = [
]

async_lib = library('async',
  async_srcs,
  install: false,
  dependencies: async_deps,
  c_args: async_c_args,
  include_directories: async_include_dirs
)

async_dep = declare_dependency(
  include_directories: async_include_dirs,
  link_with: async_lib,
  link_args: async_link_args,
)
