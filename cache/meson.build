cache_srcs = [
  'cache.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

cache_include_dirs = [
  '.',
  inc,
]

cache_deps = [
  module_dep,
  iowow_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  fs_dep,
  bytes_dep,
]

cache_c_args = [
]

cache_link_args = [
]

cache_lib = static_library('cache',
  cache_srcs,
  install: false,
  dependencies: cache_deps,
  c_args: cache_c_args,
  include_directories: cache_include_dirs
)

cache_dep = declare_dependency(
  include_directories: cache_include_dirs,
  link_with: cache_lib,
  link_args: cache_link_args,
)
