hash_srcs = [
  'hash.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

hash_include_dirs = [
  '.',
  inc,
]

hash_deps = [
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

hash_c_args = [
]

hash_link_args = [
]

hash_lib = static_library('hash',
  hash_srcs,
  install: false,
  dependencies: hash_deps,
  c_args: hash_c_args,
  include_directories: hash_include_dirs
)

hash_dep = declare_dependency(
  include_directories: hash_include_dirs,
  link_with: hash_lib,
  link_args: hash_link_args,
)
