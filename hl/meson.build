hl_srcs = [
  'hl.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

hl_include_dirs = [
  '.',
  inc,
]

hl_deps = [
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  module_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]

hl_c_args = [
]

hl_link_args = [
]

hl_lib = library('hl',
  hl_srcs,
  install: false,
  dependencies: hl_deps,
  c_args: hl_c_args,
  include_directories: hl_include_dirs
)

hl_dep = declare_dependency(
  include_directories: hl_include_dirs,
  link_with: hl_lib,
  link_args: hl_link_args,
)
