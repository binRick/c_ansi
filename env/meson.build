env_srcs = [
  'env.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

env_include_dirs = [
  '.',
  inc,
]

env_deps = [
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

env_c_args = [
]

env_link_args = [
]

env_lib = static_library('env',
  env_srcs,
  install: false,
  dependencies: env_deps,
  c_args: env_c_args,
  include_directories: env_include_dirs
)

env_dep = declare_dependency(
  include_directories: env_include_dirs,
  link_with: env_lib,
  link_args: env_link_args,
)
