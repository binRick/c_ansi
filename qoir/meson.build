qoir_srcs = [
  'qoir.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

qoir_include_dirs = [
  '.',
  inc,
]

qoir_deps = [
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
  qoir_dep,
]

qoir_c_args = [
  '-DQOIR_IMPLEMENTATION',
]

qoir_link_args = [
]

qoir_lib = static_library('qoir',
  qoir_srcs,
  install: false,
  dependencies: qoir_deps,
  c_args: qoir_c_args,
  include_directories: qoir_include_dirs
)

qoir_module_dep = declare_dependency(
  include_directories: qoir_include_dirs,
  link_with: qoir_lib,
  link_args: qoir_link_args,
)
