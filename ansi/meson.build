ansi_srcs = [
  'ansi.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

ansi_include_dirs = [
  '.',
  inc,
]

ansi_deps = [
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  module_dep,
]

ansi_c_args = [
]

ansi_link_args = [
]

ansi_lib = library('ansi',
  ansi_srcs,
  install: false,
  dependencies: ansi_deps,
  c_args: ansi_c_args,
  include_directories: ansi_include_dirs
)

ansi_dep = declare_dependency(
  include_directories: ansi_include_dirs,
  link_with: ansi_lib,
  link_args: ansi_link_args,
)
