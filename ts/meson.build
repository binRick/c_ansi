ts_srcs = [
  'ts.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

ts_include_dirs = [
  '.',
  inc,
]

ts_deps = [
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

ts_c_args = [
]

ts_link_whole = [
  uptime_lib_static,
]
ts_link_args = [
]

ts_lib = static_library('ts',
  ts_srcs,
  install: false,
  dependencies: ts_deps,
  c_args: ts_c_args,
  include_directories: ts_include_dirs,
  link_whole: ts_link_whole,

)

ts_dep = declare_dependency(
  include_directories: ts_include_dirs,
  link_with: ts_lib,
  link_args: ts_link_args,
)
