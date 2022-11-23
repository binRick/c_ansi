sdl_srcs = [
  'sdl.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

sdl_include_dirs = [
  '.',
  inc,
]

sdl_deps = [
  ansi_codes_dep,
  c_vector_dep,
  glib_dep,vips_dep,msf_gif_dep,
  c_fsio_dep,
  sdl2_dep,
  parson_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  module_dep,
]

sdl_c_args = [
]

sdl_link_args = [
]

sdl_lib = library('sdl',
  sdl_srcs,
  install: false,
  dependencies: sdl_deps,
  c_args: sdl_c_args,
  include_directories: sdl_include_dirs
)

sdl_dep = declare_dependency(
  include_directories: sdl_include_dirs,
  link_with: sdl_lib,
  link_args: sdl_link_args,
)
