view_srcs = [
  'view.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

view_include_dirs = [
  '.',
  inc,
]

view_deps = [
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

view_c_args = [
]

view_link_args = [
]

view_lib = library('view',
  view_srcs,
  install: false,
  dependencies: view_deps,
  c_args: view_c_args,
  include_directories: view_include_dirs
)

view_dep = declare_dependency(
  include_directories: view_include_dirs,
  link_with: view_lib,
  link_args: view_link_args,
)
