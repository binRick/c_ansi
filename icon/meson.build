icon_srcs = [
  'icon.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

icon_include_dirs = [
  '.',
  inc,
]

icon_deps = [
  module_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  reproc_dep,xml2_dep,
  string_utils_dep,
]

icon_c_args = [
]

icon_link_args = [
]

icon_lib = static_library('icon',
  icon_srcs,
  install: false,
  dependencies: icon_deps,
  c_args: icon_c_args,
  include_directories: icon_include_dirs
)

icon_dep = declare_dependency(
  include_directories: icon_include_dirs,
  link_with: icon_lib,
  link_args: icon_link_args,
)
