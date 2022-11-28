async_srcs = [
  'async.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

async_include_dirs = [
  '.',
  inc,
]

async_deps = [
  module_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_workqueue_dep,
  clamp_dep,
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
  chan_dep,
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
