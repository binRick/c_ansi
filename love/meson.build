love_srcs = [
  'love.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

love_include_dirs = [
  '.',
  inc,
]

love_deps = [
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  libansilove_dep,
  module_dep,
  tempdir_dep,
  reproc_dep,
  glib_dep,
  vips_dep,
  c_bat_dep,
  #  c_hl_dep,
]

love_c_args = [
]

love_link_args = [
]

love_lib = library('love',
  love_srcs,
  install: false,
  dependencies: love_deps,
  c_args: love_c_args,
  include_directories: love_include_dirs
)

love_dep = declare_dependency(
  include_directories: love_include_dirs,
  link_with: love_lib,
  link_args: love_link_args,
)
