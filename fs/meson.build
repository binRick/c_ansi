fs_srcs = [
  'fs.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

fs_include_dirs = [
  '.',
  inc,
]

fs_deps = [
  module_dep,
  ansi_codes_dep,
  c_vector_dep,
  path_normalize_c_dep,
  microtar_dep,
  c_stringfn_dep,
  tinydir_dep,
  whereami_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  qoi_dep,
  str_dep,
  wildcardcmp_dep,
  cache_dep,
]

fs_c_args = [
]

fs_link_args = [
]
fs_static_libs = [
  which_lib_static,
  string_utils_lib_static,
  qoir_lib_static,
  ansicodes_lib_static,
  bytes_lib_static,
  c_fsio_lib_static,
  tempdir_lib_static,

  ]

fs_lib = static_library('fs',
  fs_srcs,
  install: false,
  dependencies: fs_deps,
  c_args: fs_c_args,
  link_whole: fs_static_libs,
  include_directories: fs_include_dirs
)

fs_dep = declare_dependency(
  include_directories: fs_include_dirs,
  link_with: fs_lib,
  link_args: fs_link_args,
)
