time_srcs = [
  'time.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

time_include_dirs = [
  '.',
  inc,
]

time_deps = [
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
]

time_c_args = [
]

time_link_args = [
]

time_lib = static_library('time',
  time_srcs,
  install: false,
  dependencies: time_deps,
  c_args: time_c_args,
  include_directories: time_include_dirs
)

time_dep = declare_dependency(
  include_directories: time_include_dirs,
  link_with: time_lib,
  link_args: time_link_args,
)
