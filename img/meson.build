img_srcs = [
  'img.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

img_include_dirs = [
  '.',
  inc,
]

img_deps = [
  glib_dep,
  vips_dep,
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
img_static_libs = [
  timestamp_lib_static,
  ansicodes_lib_static,
  qoir_lib_static,
]
img_c_args = [
]

img_link_args = [
]

img_lib = static_library('img',
  img_srcs,
  install: false,
  dependencies: img_deps,
  c_args: img_c_args,
  link_whole: img_static_libs,
  include_directories: img_include_dirs
)

img_dep = declare_dependency(
  include_directories: img_include_dirs,
  link_with: img_lib,
  link_args: img_link_args,
)
