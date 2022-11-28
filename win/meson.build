win_srcs = [
  'win.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

win_include_dirs = [
  '.',
  inc,
]

win_deps = [
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

win_c_args = [
]

win_link_args = [
]

win_lib = static_library('win',
  win_srcs,
  install: false,
  dependencies: win_deps,
  c_args: win_c_args,
  include_directories: win_include_dirs
)

win_dep = declare_dependency(
  include_directories: win_include_dirs,
  link_with: win_lib,
  link_args: win_link_args,
)
