exec_srcs = [
  'exec.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

exec_include_dirs = [
  '.',
  inc,
]

exec_deps = [
  module_dep,
  reproc_dep,
  subprocess_dep,
  ansi_codes_dep,
  str_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]

exec_c_args = [
]

exec_link_args = [
]
exec_static_libs = [
  which_lib_static,
  ]

exec_lib = static_library('exec',
  exec_srcs,
  install: false,
  dependencies: exec_deps,
  c_args: exec_c_args,
  link_whole: exec_static_libs,
  include_directories: exec_include_dirs
)

exec_dep = declare_dependency(
  include_directories: exec_include_dirs,
  link_with: exec_lib,
  link_args: exec_link_args,
)
