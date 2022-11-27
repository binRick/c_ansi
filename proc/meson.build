proc_srcs = [
  'proc.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

proc_include_dirs = [
  '.',
  inc,
]

proc_deps = [
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

proc_c_args = [
]

proc_link_args = [
  osx_ldflags,
]

proc_lib = static_library('proc',
  proc_srcs,
  install: false,
  dependencies: proc_deps,
  c_args: proc_c_args,
  include_directories: proc_include_dirs
)

proc_dep = declare_dependency(
  include_directories: proc_include_dirs,
  link_with: proc_lib,
  link_args: proc_link_args,
)
