chan_utils_srcs = [
  'chan-utils.c',
  'module.c'
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

chan_utils_include_dirs = [
  '.',
  inc,
]

chan_utils_deps = [
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,module_dep,
  c_workqueue_dep,
  chan_dep,
]

chan_utils_c_args = [
]

chan_utils_link_args = [
]

chan_utils_lib = library('chan_utils',
  chan_utils_srcs,
  install: false,
  dependencies: chan_utils_deps,
  c_args: chan_utils_c_args,
  include_directories: chan_utils_include_dirs
)

chan_utils_dep = declare_dependency(
  include_directories: chan_utils_include_dirs,
  link_with: chan_utils_lib,
  link_args: chan_utils_link_args,
)
