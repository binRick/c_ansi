tray_srcs = [
  'tray.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

tray_include_dirs = [
  '.',
  inc,
]

tray_deps = [
  module_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  incbin_dep,
  tempdir_dep,
  which_dep,
  chan_dep,
  c_eventemitter_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  c_tray_dep,
]

tray_c_args = [
]

tray_link_args = [
]

tray_lib = static_library('tray',
  tray_srcs,
  install: false,
  dependencies: tray_deps,
  c_args: tray_c_args,
  include_directories: tray_include_dirs
)

tray_dep = declare_dependency(
  include_directories: tray_include_dirs,
  link_with: tray_lib,
  link_args: tray_link_args,
)
